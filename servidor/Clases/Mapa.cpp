#include "Mapa.h"
#include "Entidad.h"
#include "Sacerdote.h"
#include "Banquero.h"
#include "Comerciante.h"
#include "ErrorServidor.h"
#include "Box.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <utility>
#include <sstream>
#include <cmath>
#include <cstring> //Para memcpy
#include <iostream> //DEBUG
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
    return std::move(quadtree::Box<float>(0, 0, alto * altoTile, ancho * anchoTile));
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

Mapa::Mapa(std::string nombre) :        nombreMapa(nombre),
                                        frontera(0, 0, 0, 0),
                                        quadTreeEstatico(frontera, obtenerCaja),
                                        quadTreeDinamico(frontera, obtenerCaja),
                                        limiteCriaturas(0),
                                        cantidadCriaturas(0),
                                        fabricaCriaturas(entidades),
                                        motorAleatorio(std::time(0)){

    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string rutaArchivo = config->obtenerMapaRuta(nombreMapa);
    limiteCriaturas = config->obtenerMapaLimiteCriaturas(nombreMapa);
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()){
        throw ErrorServidor("Error: No se ha podido abrir el archivo de nombre %s", nombreMapa.c_str()); 
    }
    json archivoJson;
    contenido_archivo = std::string((std::istreambuf_iterator<char>(archivo)), std::istreambuf_iterator<char>());
    archivo.clear();
    archivo.seekg(0);
    archivo >> archivoJson;
    unsigned int alto  = archivoJson.at("height").get<unsigned int>();
    unsigned int ancho = archivoJson.at("width").get<unsigned int>();
    frontera = inicializarFrontera(archivoJson, alto, ancho);
    quadTreeEstatico.setFrontera(frontera);
    quadTreeDinamico.setFrontera(frontera);

    //No estan implementadas en el mapa actual
    //zonasRespawn = archivoJson.at("layers")[1].at("objects").get<std::vector<quadtree::Box<float>>>();

     std::vector<quadtree::Box<float>> objetos; 
     for (auto& capa: archivoJson["layers"]) {
         if (capa["type"] != "objectgroup" || 
             capa["name"] != "colisionables") continue;
         capa["objects"].get_to(objetos);        
         break;
    }
    
    for (std::size_t i=0; i<objetos.size(); i++){
        objetosEstaticos.push_back(std::move(objetos[i]));
    }

    for (std::size_t i=0; i<objetosEstaticos.size(); i++){
        quadTreeEstatico.add(&(objetosEstaticos[i]));
    }
    //Esto que esta completamente hardcodeado deberia levantarse del configuraciones.json
    //La idea es que el mapa sepa las posiciones del Sacerdote, Banquero y Comerciante.
    std::unique_ptr<Entidad> sacerdote(new Sacerdote(500, 500));
    std::unique_ptr<Entidad> banquero(new Banquero(300, 350));
    std::unique_ptr<Entidad> comerciante(new Comerciante(200, 200));
    cargarEntidad(sacerdote.get());
    cargarEntidad(banquero.get());
    cargarEntidad(comerciante.get());
    npcs.push_back(std::move(sacerdote));
    npcs.push_back(std::move(banquero));
    npcs.push_back(std::move(comerciante));
}
void Mapa::actualizarPosicion(Entidad *entidad, Posicion &&nuevaPosicion){
    if (!posicionValida(entidad, nuevaPosicion)) return;
    quadTreeDinamico.remove(entidad);
    entidad->actualizarPosicion(std::move(nuevaPosicion));
    quadTreeDinamico.add(entidad);
}

std::vector<struct PosicionEncapsulada> Mapa::recolectarPosiciones(){
    std::vector<struct PosicionEncapsulada> resultado;
    for (std::unordered_map<std::string, Entidad*>::iterator it = entidades.begin();
         it != entidades.end();
         ++it){
        resultado.push_back(std::move(it->second->serializarPosicion()));
    }
    return resultado;
}

Entidad* Mapa::obtener(std::string &id){
    std::unordered_map<std::string, Entidad*>::iterator it = entidades.find(id);
    if (it == entidades.end()) throw ErrorServidor("No se encontró id %s\n", id); 
    return it->second;
}

std::vector<Entidad*> Mapa::obtenerEntidades(quadtree::Box<float> &&area){
    return quadTreeDinamico.query(area);
}

void Mapa::cargarEntidadNoColisionable(Entidad *entidad){
    std::string id = entidad->obtenerId();
    std::unordered_map<std::string, Entidad*>::iterator it = entidades.find(id);
    if (it != entidades.end()){
        throw ErrorServidor("La entidad de id %s ya se encuentra cargada en el Mapa\n", id);
    }
    entidad->indicarMapaAlQuePertenece(this);
    entidades[id] = entidad;
}

void Mapa::cargarEntidadNoColisionable(std::unique_ptr<Entidad> entidad){
    cargarEntidadNoColisionable(entidad.get());
    npcs.push_back(std::move(entidad));
    std::list<std::unique_ptr<Entidad>>::iterator it = npcs.begin();
    while (it != npcs.end()){
        if ((*it)->haFinalizado()){
            it = npcs.erase(it);
        }else{
            ++it;
        }
    }
}

void Mapa::cargarEntidad(Entidad *entidad){
    std::string id = entidad->obtenerId();
    std::unordered_map<std::string, Entidad*>::iterator it = entidades.find(id);
    if (it != entidades.end()){
        throw ErrorServidor("La entidad de id %s ya se encuentra cargada en el Mapa\n", id);
    }
    entidad->indicarMapaAlQuePertenece(this);
    if (!posicionValida(entidad, entidad->obtenerArea())){
        Posicion nuevaPosicion = buscarPosicionValida(entidad->obtenerPosicion());
        entidad->actualizarPosicion(std::move(nuevaPosicion));
    }
    quadTreeDinamico.add(entidad);
    entidades[id] = entidad;
}

void Mapa::cargarEntidad(std::unique_ptr<Entidad> entidad){
    cargarEntidad(entidad.get());
    npcs.push_back(std::move(entidad));
    std::list<std::unique_ptr<Entidad>>::iterator it = npcs.begin();
    while (it != npcs.end()){
        if ((*it)->haFinalizado()){
            it = npcs.erase(it);
        }else{
            ++it;
        }
    }
}

void Mapa::cargarCriatura(){
    if (cantidadCriaturas >= limiteCriaturas) return;
    // Obtengo un punto de respawn de la lista
    std::vector<quadtree::Box<float>>::iterator zona = zonasRespawn.begin();
    std::uniform_int_distribution<> dis(0, std::distance(zona, zonasRespawn.end()) - 1);
    std::advance(zona, dis(motorAleatorio));
    
    //TODO: Cambiar los atributos de publicos a privados.
    float x = (*zona).getCenter().x;
    float y = (*zona).getCenter().y;
    
    cargarEntidad(std::move(fabricaCriaturas.obtenerCriaturaAleatoria(x, y, nombreMapa)));
}


bool Mapa::posicionValida(Entidad *entidad, const quadtree::Box<float> &area){
    if (!frontera.contains(area)) return false;
    std::vector<Colisionable*> resultado = quadTreeEstatico.query(area);
    for (std::vector<Colisionable*>::iterator it = resultado.begin();
         it != resultado.end();
         ++it){
        if ((*it)->colisionaCon(area)) return false;
    }
    std::vector<Entidad*> resultadoDinamico;
    resultadoDinamico = quadTreeDinamico.query(area);
    for (std::vector<Entidad*>::iterator it = resultadoDinamico.begin();
         it != resultadoDinamico.end();
         ++it){
        if ((*it)->colisionaCon(area)){
            //No puedo chocar conmigo mismo, es mi posicion anterior.
            if ((*it) == entidad)
                continue;
            else return false;
        }
    }
    return true;
}

bool Mapa::posicionValida(Entidad *entidad, const Posicion &nuevaPosicion){
    return posicionValida(entidad, nuevaPosicion.obtenerAreaQueOcupa());
}

Posicion Mapa::buscarPosicionValida(const Posicion &posicion){
    //Le doy una distancia mayor para asegurarme que no colisionen
    float radio = 2.01*posicion.longitudMaximaDeColision();
    unsigned int i = 0;
    bool continuar = true;
    Posicion nuevaPosicion;
    while (continuar){
        nuevaPosicion = posicion.nuevaPosicionDesplazada(radio*cos(i*PI_4), radio*sin(i*PI_4));
        if (posicionValida(nullptr, nuevaPosicion)) continuar = false;
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
    std::unordered_map<std::string, Entidad*>::iterator it = entidades.find(id);
    if (it == entidades.end()) throw ErrorServidor("No se encontró id %s\n", id.c_str());
    quadTreeDinamico.remove(it->second);
    entidades.erase(it);
}

void Mapa::eliminarEntidadNoColisionable(Entidad *entidad){
    std::string id = entidad->obtenerId();
    std::unordered_map<std::string, Entidad*>::iterator it = entidades.find(id);
    if (it == entidades.end()) throw ErrorServidor("No se encontró id %s\n", id.c_str());
    entidades.erase(it);
}

void Mapa::entidadesActualizarEstados(double tiempo){
    for (auto& entidad: entidades) {
        entidad.second->actualizarEstado(tiempo);
    }
}

const std::vector<char> Mapa::obtenerInformacionMapa(){
    const std::vector<char> vector(contenido_archivo.begin(), contenido_archivo.end());
    return vector;
}


