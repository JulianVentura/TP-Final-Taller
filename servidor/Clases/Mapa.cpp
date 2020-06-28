#include "Mapa.h"
#include "ErrorServidor.h"
#include "Box.h"
//#include "../nlohmann_json/include/nlohmann/json.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <utility>
#include <sstream>
#include <cmath>
#include <cstring> //Para memcpy
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
    contenido_archivo = std::string((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());
    alto  = archivoJson.at("height").get<unsigned int>();
    ancho = archivoJson.at("width").get<unsigned int>();
    frontera = inicializarFrontera(archivoJson, alto, ancho);
    quadTreeEstatico.setFrontera(frontera);
    quadTreeDinamico.setFrontera(frontera);
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

std::string Mapa::posicionesACadena(){
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

std::vector<struct PosicionEncapsulada> Mapa::recolectarPosiciones(){
    std::vector<struct PosicionEncapsulada> resultado;
    for (std::map<std::string, Criatura*>::iterator it = criaturas.begin();
         it != criaturas.end();
         ++it){
        struct PosicionEncapsulada pos = {{0}, it->second->obtenerX(), it->second->obtenerX()};
        //Copio dejando espacio para el `\0`
        memcpy(pos.id, it->first.c_str(), TAM_ID - 1);
        resultado.push_back(std::move(pos));
    }
    for (std::map<std::string, Personaje*>::iterator it = personajes.begin();
         it != personajes.end();
         ++it){
        struct PosicionEncapsulada pos = {{0}, it->second->obtenerX(), it->second->obtenerX()};
        //Copio dejando espacio para el `\0`
        memcpy(pos.id, it->first.c_str(), TAM_ID - 1);
        resultado.push_back(std::move(pos));
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
    if (!frontera.contains(area)) return false;
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
        criatura.second->actualizarEstado(tiempo, this);
    }
    for (auto& personaje: personajes) {
        personaje.second->actualizarEstado(tiempo, this);
    }
}

const std::vector<char> Mapa::obtenerInformacionMapa(){
    const std::vector<char> vector(contenido_archivo.begin(), contenido_archivo.end());
    return vector;
}
// DEBUG
#define ANCHO_TILE 32.0f // Esto dice en mapa.json
//Indica la cantidad de celdas que hay en una coordenada de cada tile, tal que NUM_CELDAS_POR_ANCHO_TILE**2 = NUM_CELDAS_POR_TILE
#define NUM_CELDAS_POR_ANCHO_TILE 2
#define ANCHO_CELDA (ANCHO_TILE / NUM_CELDAS_POR_ANCHO_TILE)
#define DEFINICION 10.0f // Pixeles equivalentes por caracter
#define ID_COLISION 16


static void poblarCadena(Entidad* entidad, unsigned int ancho, char c, 
                                                    std::string& resultado) {
    int x = std::floor(entidad->obtenerPosicion().obtenerX()/ANCHO_CELDA);
    int y = std::floor(entidad->obtenerPosicion().obtenerY()/ANCHO_CELDA);
    int index = y * ancho + x;
    resultado[index] = c;
}

static void poblarColisiones(std::vector<char> &tiles, 
                             std::string &resultado, unsigned int alto, unsigned int ancho){
    unsigned int indice = 0;
    unsigned int ancho_celda = ancho * NUM_CELDAS_POR_ANCHO_TILE;
    unsigned int x = 0;
    unsigned int y = 0;
    for (auto& tile : tiles){
        if (tile == ID_COLISION){
            x = indice % ancho;
            y = indice / ancho;
            y *= NUM_CELDAS_POR_ANCHO_TILE;
            x *= NUM_CELDAS_POR_ANCHO_TILE;
            for (int j=0; j<NUM_CELDAS_POR_ANCHO_TILE; j++){
                for (int i=0; i<NUM_CELDAS_POR_ANCHO_TILE; i++){
                    resultado[(y+j) * ancho_celda + x + i] = '#';
                }
            }
        }
        indice++;
    }
}

std::string Mapa::aCadena() {
    std::stringstream tablero;
    unsigned int ancho_celdas = ancho * NUM_CELDAS_POR_ANCHO_TILE;
    unsigned int alto_celdas = alto * NUM_CELDAS_POR_ANCHO_TILE;
    for (unsigned int j = 0; j < alto_celdas; ++j) {
        for (unsigned int i = 0; i < ancho_celdas; ++i){
            tablero <<  ".";
        }
    }
    std::string resultado = tablero.str();
    poblarColisiones(tiles, resultado, alto, ancho);
    for (auto& criatura: criaturas) {
        poblarCadena(criatura.second, ancho_celdas, 'C', resultado);
    }
    for (auto& personaje: personajes) {
        poblarCadena(personaje.second, ancho_celdas, 'J', resultado);
    }
    //Como se va a imprimir
    std::stringstream mapa_resultado;
    unsigned int indice = 0;
    for (unsigned int j = 0; j < alto_celdas; ++j) {
        for (unsigned int i = 0; i < ancho_celdas; ++i){
            indice = j * ancho_celdas + i;
            mapa_resultado << " " << resultado[indice];
        }
        mapa_resultado << "\n";
    }
    return mapa_resultado.str();
}
