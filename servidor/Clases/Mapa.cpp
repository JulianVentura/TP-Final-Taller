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
                                        ancho(0),
                                        alto(0),
                                        frontera(0, 0, 0, 0),
                                        quadTreeEstatico(frontera, obtenerCaja),
                                        quadTreeDinamico(frontera, obtenerCaja),
                                        limiteCriaturas(0),
                                        personajes(),
                                        criaturas(),
                                        fabricaCriaturas(criaturas),
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
    alto  = archivoJson.at("height").get<unsigned int>();
    ancho = archivoJson.at("width").get<unsigned int>();
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
    std::unique_ptr<Interactuable> sacerdote(new Sacerdote(300, 90));
    std::unique_ptr<Interactuable> banquero(new Banquero(120, 110));
    std::unique_ptr<Interactuable> comerciante(new Comerciante(120, 200));
    quadTreeEstatico.add(sacerdote.get());
    quadTreeEstatico.add(banquero.get());
    quadTreeEstatico.add(comerciante.get());
    ciudadanos[sacerdote->obtenerId()] = std::move(sacerdote);
    ciudadanos[banquero->obtenerId()] = std::move(banquero);
    ciudadanos[comerciante->obtenerId()] = std::move(comerciante);
}
void Mapa::actualizarPosicion(Entidad *entidad, Posicion &&nuevaPosicion){
    if (!posicionValida(entidad, nuevaPosicion)) return;
    quadTreeDinamico.remove(entidad);
    entidad->actualizarPosicion(std::move(nuevaPosicion));
    quadTreeDinamico.add(entidad);
}

std::vector<struct PosicionEncapsulada> Mapa::recolectarPosiciones(){
    std::vector<struct PosicionEncapsulada> resultado;
    struct PosicionEncapsulada pos = {{0}, 0, 0};
    for (std::map<std::string, std::unique_ptr<Criatura>>::iterator it = criaturas.begin();
         it != criaturas.end();
         ++it){
        pos = {{0}, it->second->obtenerX(), it->second->obtenerY()};
        strncpy(pos.id, it->first.c_str(), TAM_ID);
        pos.id[TAM_ID - 1] = 0;
        resultado.push_back(std::move(pos));
    }
    for (std::map<std::string, Personaje*>::iterator it = personajes.begin();
         it != personajes.end();
         ++it){
        pos = {{0}, it->second->obtenerX(), it->second->obtenerY()};
        strncpy(pos.id, it->first.c_str(), TAM_ID);
        pos.id[TAM_ID - 1] = 0;
        resultado.push_back(std::move(pos));
    }
    for (std::map<std::string, std::unique_ptr<Interactuable>>::iterator it = ciudadanos.begin();
         it != ciudadanos.end();
         ++it){
        ;
        pos = {{0}, it->second->obtenerPosicion().obtenerX(), it->second->obtenerPosicion().obtenerY()};
        strncpy(pos.id, it->first.c_str(), TAM_ID);
        pos.id[TAM_ID - 1] = 0;
        resultado.push_back(std::move(pos));
    }
    return resultado;
}
Entidad* Mapa::obtener(std::string &id){
    std::map<std::string, std::unique_ptr<Criatura>>::iterator Cit = criaturas.find(id);
    std::map<std::string, Personaje*>::iterator Pit = personajes.find(id);
    if (Cit == criaturas.end()){
        if (Pit == personajes.end()){
            throw ErrorServidor("No se encontró id %s\n", id); 
        }else{
            return Pit->second;
        }
    }else{
        return Cit->second.get();
    }
}

void Mapa::cargarEntidad(Entidad *entidad){
    entidad->indicarMapaAlQuePertenece(this);
    if (!posicionValida(entidad, entidad->obtenerAreaQueOcupa())){
        Posicion nuevaPosicion = buscarPosicionValida(entidad->obtenerPosicion());
        entidad->actualizarPosicion(std::move(nuevaPosicion));
    }
    quadTreeDinamico.add(entidad);
}

void Mapa::cargarPersonaje(Personaje *personaje){
    personajes[personaje->obtenerId()] = personaje;
    cargarEntidad(personaje);
}

void Mapa::cargarDrop(std::unique_ptr<BolsaDeItems> bolsa){
    std::string id = bolsa->obtenerId();
    std::map<std::string, std::unique_ptr<BolsaDeItems>>::iterator it = drops.find(id);
    if (it != drops.end()){
        throw ErrorServidor("Se ha solicitado almacenar un drop con un id ya utilizado");
    }
    drops[bolsa->obtenerId()] = std::move(bolsa);
}

void Mapa::limpiarDrops(){
    std::map<std::string, std::unique_ptr<BolsaDeItems>>::iterator it = drops.begin();
    while (it != drops.end()){
        if (it->second->estaVacia()){
            it = drops.erase(it);
        }else{
            ++it;
        }
    }
}

Interactuable *Mapa::obtenerInteractuable(std::string &id){
    std::map<std::string, std::unique_ptr<BolsaDeItems>>::iterator Dit = drops.find(id);
    std::map<std::string, std::unique_ptr<Interactuable>>::iterator Cit = ciudadanos.find(id);
    if (Cit == ciudadanos.end()){
        if (Dit == drops.end()){
            throw ErrorServidor("No se encontró id %s\n", id); 
        }else{
            return Dit->second.get();
        }
    }else{
        return Cit->second.get();
    }
}


void Mapa::cargarCriatura(){
    if (criaturas.size() >= limiteCriaturas) return;
    // Obtengo un punto de respawn de la lista
    std::vector<quadtree::Box<float>>::iterator zona = zonasRespawn.begin();
    std::uniform_int_distribution<> dis(0, std::distance(zona, zonasRespawn.end()) - 1);
    std::advance(zona, dis(motorAleatorio));
    
    //TODO: Cambiar los atributos de publicos a privados.
    float x = (*zona).getCenter().x;
    float y = (*zona).getCenter().y;

    std::unique_ptr<Criatura> criaturaEncapsulada = 
    std::move(fabricaCriaturas.obtenerCriaturaAleatoria(x, y, nombreMapa));

    Criatura *criatura = criaturaEncapsulada.get();
    criaturas[criatura->obtenerId()] = std::move(criaturaEncapsulada);
    cargarEntidad(criatura);
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
    float radio = 2.1*posicion.longitudMaximaDeColision();
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
    std::map<std::string, std::unique_ptr<Criatura>>::iterator Cit = criaturas.find(id);
    std::map<std::string, Personaje*>::iterator Pit = personajes.find(id);
    if (Cit == criaturas.end()){
        if (Pit == personajes.end()){
            throw ErrorServidor("No se encontró id %s\n", id.c_str()); 
        }else{
            //Se elimina el personaje
            quadTreeDinamico.remove(Pit->second);
            personajes.erase(Pit);
        }
    }else{
        //Se elimina la criatura
        quadTreeDinamico.remove(Cit->second.get());
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


