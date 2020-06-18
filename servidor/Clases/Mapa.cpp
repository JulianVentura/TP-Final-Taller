#include "Mapa.h"
#include "ErrorServidor.h"
#include "Rectangulo.h"
//#include "../nlohmann_json/include/nlohmann/json.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <utility>
#include <sstream>
// Por conveniencia
using json = nlohmann::json;


static void from_json(const json& j, Rectangulo& rectangulo) {
    float ancho;
    float alto;
    float x;
    float y;
    j.at("height").get_to(alto);
    j.at("width").get_to(ancho);
    j.at("x").get_to(x);
    j.at("y").get_to(y);
    rectangulo.set(x, y, ancho, alto);
}

static Rectangulo inicializarFrontera(json& archivoJson, unsigned int ancho, 
                                                            unsigned int alto) {
    unsigned int anchoTile;
    archivoJson["tilewidth"].get_to(anchoTile);
    unsigned int altoTile;
    archivoJson["tileheight"].get_to(altoTile);
    return std::move(Rectangulo(0, 0, ancho * anchoTile, alto * altoTile));
}

Mapa::Mapa(const char* nombreArchivo) : tiles(),
                                        ancho(0),
                                        alto(0),
                                        quadTreeEstatico(),
                                        quadTreeDinamico(),
                                        cantidadDeCriaturas(0),
                                        personajes(),
                                        criaturas(){
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()){
        throw ErrorServidor("No se pudo abrir el archivo %s\n", nombreArchivo); 
    }
    json archivoJson;
    archivo >> archivoJson;
    alto  = archivoJson.at("height").get<unsigned int>();
    ancho = archivoJson.at("width").get<unsigned int>();
    frontera = inicializarFrontera(archivoJson, alto, ancho);
    tiles = archivoJson.at("layers")[0].at("data").get<std::vector<char>>();
    std::vector<Rectangulo> objetos = archivoJson.at("layers")[1].at("objects").get<std::vector<Rectangulo>>();
    // TODO: Acá los rectangulos están iniciando en {0, 0} con ancho {0, 0}.
    for (std::size_t i=0; i<objetos.size(); i++){
        objetosEstaticos.push_back(std::move(objetos[i]));
    }
    for (std::size_t i=0; i<objetosEstaticos.size(); i++){
        quadTreeEstatico.insertar(&(objetosEstaticos[i]));
    } 
}
void Mapa::actualizarPosicion(Entidad *entidad, Posicion &&nuevaPosicion){
    if (!posicionValida(nuevaPosicion)) return;
    quadTreeDinamico.remover(entidad);
    entidad->actualizarPosicion(std::move(nuevaPosicion));
    quadTreeDinamico.insertar(entidad);

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
            // Cambiar por una propia
            // throw std::exception();
            // TODO: No sé si te convence esta exception
        }else{
            return Pit->second;
        }
    }else{
        return Cit->second;
    }
}


void Mapa::cargarPersonaje(Personaje *personaje){
    personajes[personaje->obtenerId()] = personaje;
    //Antes de insertar hay que chequear que no colisione con algo FALTA HACER ESO
    quadTreeDinamico.insertar(personaje);
}


bool Mapa::posicionValida(Posicion &nuevaPosicion){
    if (!frontera.contieneA(nuevaPosicion.obtenerAreaQueOcupa())) return false;
    std::list<Colisionable*> resultado = quadTreeEstatico.obtener(nuevaPosicion.obtenerAreaQueOcupa());
    for (std::list<Colisionable*>::iterator it = resultado.begin();
         it != resultado.end();
         ++it){
        if ((*it)->colisionaCon(nuevaPosicion.obtenerAreaQueOcupa())) return false;
    }
    resultado = quadTreeDinamico.obtener(nuevaPosicion.obtenerAreaQueOcupa());
    for (std::list<Colisionable*>::iterator it = resultado.begin();
         it != resultado.end();
         ++it){
        if ((*it)->colisionaCon(nuevaPosicion.obtenerAreaQueOcupa())) return false;
    }
    return true;
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


void Mapa::entidadesActualizarEstados(double tiempo){
    for (auto& criatura: criaturas) {
        criatura.second->actualizarEstado(tiempo);
    }
    for (auto& personaje: personajes) {
        personaje.second->actualizarEstado(tiempo);
    }
}
