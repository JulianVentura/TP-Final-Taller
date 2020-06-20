#include "Mapa.h"
#include "ErrorServidor.h"
#include "Box.h"
//#include "../nlohmann_json/include/nlohmann/json.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <utility>
#include <sstream>
#include <cmath>
//pi/4
#define PI_4 0.7853982
// Por conveniencia
using json = nlohmann::json;

static quadtree::Box<float> inicializarFrontera(json& archivoJson, 
                                                unsigned int ancho, 
                                                unsigned int alto) {
    unsigned int anchoTile;
    archivoJson["tilewidth"].get_to(anchoTile);
    unsigned int altoTile;
    archivoJson["tileheight"].get_to(altoTile);
    return std::move(quadtree::Box<float>(0, 0, ancho * anchoTile, alto * altoTile));
}
namespace quadtree{
    static void from_json(const json& j, quadtree::Box<float>& caja) {
        float ancho;
        float alto;
        float x;
        float y;
        j.at("height").get_to(alto);
        j.at("width").get_to(ancho);
        j.at("x").get_to(x);
        j.at("y").get_to(y);
        caja.set(x, y, ancho, alto);
    }
}

Mapa::Mapa(std::string nombreArchivo) : tiles(),
                                        ancho(0),
                                        alto(0),
                                        frontera(0, 0, 0, 0),
                                        quadTreeEstatico(frontera, obtenerCaja),
                                        quadTreeDinamico(frontera, obtenerCaja),
                                        cantidadDeCriaturas(0),
                                        personajes(),
                                        criaturas(){
    std::ifstream archivo(nombreArchivo.c_str());
    if (!archivo.is_open()){
        throw ErrorServidor("No se pudo abrir el archivo %s\n", nombreArchivo); 
    }
    json archivoJson;
    archivo >> archivoJson;
    alto  = archivoJson.at("height").get<unsigned int>();
    ancho = archivoJson.at("width").get<unsigned int>();
    frontera = inicializarFrontera(archivoJson, alto, ancho);
    tiles = archivoJson.at("layers")[0].at("data").get<std::vector<char>>();
    std::vector<quadtree::Box<float>> objetos = archivoJson.at("layers")[1].at("objects").get<std::vector<quadtree::Box<float>>>();
    // TODO: Acá los rectangulos están iniciando en {0, 0} con ancho {0, 0}.
    for (std::size_t i=0; i<objetos.size(); i++){
        objetosEstaticos.push_back(std::move(objetos[i]));
    }
    for (std::size_t i=0; i<objetosEstaticos.size(); i++){
        quadTreeEstatico.add(&(objetosEstaticos[i]));
    } 
}
void Mapa::actualizarPosicion(Entidad *entidad, Posicion &&nuevaPosicion){
    if (!posicionValida(nuevaPosicion)) return;
    quadTreeDinamico.remove(entidad);
    entidad->actualizarPosicion(std::move(nuevaPosicion));
    quadTreeDinamico.add(entidad);
}

std::string Mapa::recolectarPosiciones(){
    std::string resultado;

    for (std::map<std::string, Criatura*>::iterator it = criaturas.begin();
         it != criaturas.end();
         ++it){
        resultado += it->first + '/' + it->second->imprimirPosicion() + '$';
    }

    for (std::map<std::string, Personaje*>::iterator it = personajes.begin();
         it != personajes.end();
         ++it){
        resultado += it->first + '/' + it->second->imprimirPosicion() + '$';
    }
    return resultado;
}

Entidad* Mapa::obtener(const char* id){
    std::map<std::string, Criatura*>::iterator Cit = criaturas.find(id);
    std::map<std::string, Personaje*>::iterator Pit = personajes.find(id);
    if (Cit == criaturas.end()){
        if (Pit == personajes.end()){
            throw ErrorServidor("No se encontró id %s\n", id); 
        }else{
            return Pit->second;
        }
    }else{
        return Cit->second;
    }
}

void Mapa::cargarEntidad(Entidad *entidad){
    if (!posicionValida(entidad->obtenerAreaQueOcupa())){
        Posicion nuevaPosicion = buscarPosicionValida(entidad->obtenerPosicion());
        entidad->actualizarPosicion(std::move(nuevaPosicion));
    }
    quadTreeDinamico.add(entidad);
}

void Mapa::cargarPersonaje(Personaje *personaje){
    personajes[personaje->obtenerId()] = personaje;
    cargarEntidad(personaje);
}


void Mapa::cargarCriatura(Criatura *criatura){
    criaturas[criatura->obtenerId()] = criatura;
    cargarEntidad(criatura);
}

bool Mapa::posicionValida(const quadtree::Box<float> &area){
    std::vector<Colisionable*> resultado = quadTreeEstatico.query(area);
    for (std::vector<Colisionable*>::iterator it = resultado.begin();
         it != resultado.end();
         ++it){
        if ((*it)->colisionaCon(area)) return false;
    }
    resultado = quadTreeDinamico.query(area);
    for (std::vector<Colisionable*>::iterator it = resultado.begin();
         it != resultado.end();
         ++it){
        if ((*it)->colisionaCon(area)) return false;
    }
    return true;
}

bool Mapa::posicionValida(const Posicion &nuevaPosicion){
    //if (!frontera.contains(nuevaPosicion.obtenerAreaQueOcupa())) return false;
    return posicionValida(nuevaPosicion.obtenerAreaQueOcupa());
}

Posicion Mapa::buscarPosicionValida(const Posicion &posicion){
    //Le doy una distancia mayor para asegurarme que no colisionen
    float radio = 2.1*posicion.longitudMaximaDeColision();
    unsigned int i = 0;
    bool continuar = true;
    Posicion nuevaPosicion;
    while (continuar){
        nuevaPosicion = posicion.nuevaPosicionDesplazada(radio*cos(i*PI_4), radio*sin(i*PI_4));
        if (posicionValida(nuevaPosicion)) continuar = false;
        if (i >= 8){
            //Vuelve a empezar, pero duplico la distancia
            i = 0;
            radio *= 2;
        }else{
            i++;
        }
    }
    return nuevaPosicion;
}


void Mapa::eliminarEntidad(Entidad *entidad){
    eliminarEntidad(entidad->obtenerId());
}

void Mapa::eliminarEntidad(const std::string &id){
    std::map<std::string, Criatura*>::iterator Cit = criaturas.find(id);
    std::map<std::string, Personaje*>::iterator Pit = personajes.find(id);
    if (Cit == criaturas.end()){
        if (Pit == personajes.end()){
            throw ErrorServidor("No se encontró id %s\n", id); 
        }else{
            //Se elimina el personaje
            quadTreeDinamico.remove(Pit->second);
            personajes.erase(Pit);
        }
    }else{
        //Se elimina la criatura
        quadTreeDinamico.remove(Cit->second);
        criaturas.erase(Cit);
    }
}

void Mapa::entidadesActualizarEstados(double tiempo){
    for (auto& criatura: criaturas) {
        criatura.second->actualizarEstado(tiempo);
    }
    for (auto& personaje: personajes) {
        personaje.second->actualizarEstado(tiempo);
    }
}


// DEBUG
#define ANCHO_TILE 32.0f // Esto dice en mapa.json
#define DEFINICION 10.0f // Pixeles equivalentes por caracter
static void poblarCadena(Entidad* entidad, unsigned int ancho, char c, 
                                                    std::string& resultado) {
    float x = entidad->obtenerAreaQueOcupa().obtenerX() / DEFINICION;
    float y = entidad->obtenerAreaQueOcupa().obtenerY() / DEFINICION;
    int index = y * ((float) ancho * ANCHO_TILE / DEFINICION + 1) + x;
    resultado[index] = c;
}
std::string Mapa::aCadena() {
    std::stringstream buffer;
    for (unsigned int i = 0; i < ancho * ANCHO_TILE / DEFINICION; ++i) {
        for (unsigned int j = 0; j < alto * ANCHO_TILE / DEFINICION; ++j)
            buffer << ".";
        buffer << "\n";
    }
    std::string resultado = buffer.str();
    for (auto& criatura: criaturas) {
        poblarCadena(criatura.second, ancho, '?', resultado);
    }
    for (auto& personaje: personajes) {
        poblarCadena(personaje.second, ancho, '#', resultado);
    }
    return resultado;
}

