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
                                        tiempoRespawn(0),
                                        tiempoTranscurrido(0),
                                        fabricaNPC(entidades),
                                        motorAleatorio(std::time(0)){

    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string rutaArchivo = config->obtenerMapaRuta(nombreMapa);
    limiteCriaturas = config->obtenerMapaLimiteCriaturas(nombreMapa);
    tiempoRespawn = config->obtenerMapaTiempoRespawn(nombreMapa);
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
    
    for (auto& capa: archivoJson["layers"]) {
        if (capa["type"] != "objectgroup" || 
            capa["name"] != "respawn") continue;
        capa["objects"].get_to(zonasRespawn);        
        break;
    }
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

    //Spawneo de npcs pasivos (ciudadanos y portales)    
    quadtree::Box<float> spawnActual;
    std::string idActual;
    float x = 0;
    float y = 0;
    for (auto& capa: archivoJson["layers"]) {
        if (capa["type"] != "objectgroup" || 
            capa["name"] != "spawnPasivos") continue;
        for (auto &spawn : capa["objects"]){
            spawn.get_to(spawnActual);
            x = spawnActual.getCenter().obtenerX();
            y = spawnActual.getCenter().obtenerY();
            spawn["name"].get_to(idActual);
            cargarEntidad(fabricaNPC.obtenerNPCPasivo(x, y, idActual, nombreMapa));
        }
        break;
    }
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
    if (it == entidades.end()) throw ErrorServidor("Error en Mapa: No se encontró el id %s\n", id.c_str()); 
    return it->second;
}

std::vector<Entidad*> Mapa::obtenerEntidades(quadtree::Box<float> &&area){
    return quadTreeDinamico.query(area);
}

void Mapa::cargarEntidadNoColisionable(Entidad *entidad){
    std::string id = entidad->obtenerId();
    std::unordered_map<std::string, Entidad*>::iterator it = entidades.find(id);
    if (it != entidades.end()){
        throw ErrorServidor("La entidad de id %s ya se encuentra cargada en el Mapa\n", id.c_str());
    }
    entidad->indicarMapaAlQuePertenece(this);
    colaDeCarga.push(entidad);
}

void Mapa::cargarEntidadNoColisionable(std::unique_ptr<Entidad> entidad){
    cargarEntidadNoColisionable(entidad.get());
    /*
    No hay riesgo de carga sobre npcs ya que se hace siempre secuencialmente en una
    operacion del gameloop o en la actualizacion de estado de una entidad.
    */
    npcs.push_back(std::move(entidad));
}

void Mapa::cargarEntidad(Entidad *entidad){
    std::string id = entidad->obtenerId();
    std::unordered_map<std::string, Entidad*>::iterator it = entidades.find(id);
    if (it != entidades.end()){
        throw ErrorServidor("La entidad de id %s ya se encuentra cargada en el Mapa\n", id.c_str());
    }
    entidad->indicarMapaAlQuePertenece(this);
    if (!posicionValida(entidad, entidad->obtenerArea())){
        Posicion nuevaPosicion = buscarPosicionValida(entidad->obtenerPosicion());
        entidad->actualizarPosicion(std::move(nuevaPosicion));
    }
    //El quadtree es seguro (protegido con mutex).
    quadTreeDinamico.add(entidad);
    colaDeCarga.push(entidad);
}

void Mapa::cargarEntidad(std::unique_ptr<Entidad> entidad){
    cargarEntidad(entidad.get());
    npcs.push_back(std::move(entidad));
}

void Mapa::cargarCriatura(){
    if (cantidadCriaturas >= limiteCriaturas) return;
    // Obtengo un punto de respawn de la lista
    std::vector<quadtree::Box<float>>::iterator zona = zonasRespawn.begin();
    if(zona == zonasRespawn.end()) return;
    std::uniform_int_distribution<> dis(0, std::distance(zona, zonasRespawn.end()) - 1);
    std::advance(zona, dis(motorAleatorio));
    //Obtengo un punto aleatorio sobre la zona de respawn
    float x1 = (*zona).getTopLeft().obtenerX();
    float x2 = x1 + (*zona).getRight();
    float y1 = (*zona).getTopLeft().obtenerY();
    float y2 = y1 + (*zona).getBottom();
    std::uniform_int_distribution<> dis_x(x1, x2);
    std::uniform_int_distribution<> dis_y(y1, y2);
    float x = dis_x(motorAleatorio);
    float y = dis_y(motorAleatorio);
    cargarEntidad(std::move(fabricaNPC.obtenerCriaturaAleatoria(x, y, nombreMapa)));
    cantidadCriaturas++;
}


void Mapa::cargar(Entidad *entidad){
    std::string id = entidad->obtenerId();
    std::unordered_map<std::string, Entidad*>::iterator it = entidades.find(id);
    //Esto solo puede fallar si se intenta cargar una entidad en operaciones consecutivas.
    if (it != entidades.end()) return;
    entidades[id] = entidad;
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

void Mapa::eliminarCriatura(){
    cantidadCriaturas--;
}

void Mapa::eliminarEntidad(Entidad *entidad){
    eliminarEntidad(entidad->obtenerId());
}

void Mapa::eliminarEntidad(const std::string &id){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::unordered_map<std::string, Entidad*>::iterator it = entidades.find(id);
    if (it == entidades.end()){
        throw ErrorServidor("No se encontró id %s\n", id.c_str());
    }
    quadTreeDinamico.remove(it->second);
    entidades.erase(it);
}

void Mapa::eliminarEntidadNoColisionable(Entidad *entidad){
    std::unique_lock<std::mutex> lock(this->mutex);
    std::string id = entidad->obtenerId();
    std::unordered_map<std::string, Entidad*>::iterator it = entidades.find(id);
    if (it == entidades.end()){
        throw ErrorServidor("No se encontró id %s\n", id.c_str());
    } 
    entidades.erase(it);
}

void Mapa::entidadesActualizarEstados(double tiempo){
    tiempoTranscurrido += tiempo;
    if (tiempoTranscurrido >= tiempoRespawn){
        tiempoTranscurrido = 0;
        this->cargarCriatura();
    }
    //Atomizo la actualizacion de estados de las entidades.
    mutex.lock();
    for (auto& entidad: entidades){
        entidad.second->actualizarEstado(tiempo);
    }
    mutex.unlock();
    //Limpio completados
    std::list<std::unique_ptr<Entidad>>::iterator it = npcs.begin();
    while (it != npcs.end()){
        if ((*it)->haFinalizado()){
            it = npcs.erase(it);
        }else{
            ++it;
        }
    }
    //Cargo las entidades.
    bool seguirIterando = true;
    Entidad *entidadActual = nullptr;
    while (seguirIterando){
        entidadActual = colaDeCarga.pop();
        if (entidadActual){
            cargar(entidadActual);  //Es un metodo privado del mapa.
        }else{
            seguirIterando = false;
        }
    }
}

const std::vector<char> Mapa::obtenerInformacionMapa(){
    const std::vector<char> vector(contenido_archivo.begin(), contenido_archivo.end());
    return vector;
}



/*
Ideas para la inicializacion de npcs en cada Mapa.

Cada archivo con la informacion de los tiles del mapa podria tener distintas zonas con un nombre especifico en donde
se aclare el spawn de cierto NPC.
Entonces se pueden crear zonas con los siguientes ids:


* RespawnNPC:

- Sacerdote
- Banquero
- Comerciante
- Portal#1
- Portal#2


Luego en el configuraciones.json se escribira el nombre de los npcs que el mapa debe spawnear y su nombre debera
coincidir con el de las zonas, de forma tal que:

Mapa: {
    "mapa": {
        "SpawnPortales": {
            "Portal#1": "mapa2", 
            "Portal#2": "mapa3"
            }
    }
}

Si algun npc figura pero su zona de spawn no esta en el mapa simplemente no se lo spawnea, lo mismo en caso contrario.

En algun lugar se debera realizar el parseo entre el nombre del NPC y la entidad en si, quizas en la FabricaDeNPC.

De esta forma el mapa simplemente parsea la zona, la busca dentro del json.




*/


/*
Como manejar la carga/descarga de entidades y jugadores en el mapa.

Requisitos:

- Una entidad/jugador no puede ser cargado ni descargado mientras se actualizan los estados de las demas entidades.
- Una actualizacion de estado de una entidad puede producir la carga de una nueva entidad.

Si el mapa tiene dos colas de carga.

Mapa::cargarEntidad(std::unique_ptr<Entidad> entidad){
    this->cargarEntidad(entidad.get());
    npcs.push(entidad);
}

Mapa::cargarEntidad(Entidad *entidad){
    colaEntidades.push(entidad);                    //Es una cola segura, no bloqueante.
}

Mapa::cargarEntidadNoColisionable(std::unique_ptr<Entidad> entidad){
    colaEntidadesNoColisiobables.push(entidad);     //Es una cola segura, no bloqueante.
    npcs.push(entidad);
}

Mapa::eliminarEntidad(Entidad *entidad){
    std::unique_lock<std::mutex> lock(this->mutex);
    //Eliminar de quadTree
    //Eliminar de hash de entidades.
}

Mapa::eliminarEntidadNoColisionable(Entidad *entidad){
    std::unique_lock<std::mutex> lock(this->mutex);
    //Eliminar de hash de entidades.
}


Mapa::entidadesActualizarEstados(tiempo){
    tiempoTransc += tiempo;
    if (tiempoTransc >= tiempoRespawn){
        tiempoTransc = 0;
        spawnearCriatura();
    }
    mutex->lock();
    for (auto &entidad : entidades){
        entidad->actualizarEstado(tiempo)
    }
    mutex->unlock();
    //Descargo entidades finalizadas
    for (auto &npc : npcs){
        if (npc->haFinalizado()){
            npc.erase();
        }
    }
    bool seguir_iterando = true;
    Entidad *entidadActual = nullptr;
    while (seguirIterando){
        entidadActual = colaEntidades.pop();
        if (entidadActual){
            cargarColisionable(entidadActual)   //Es un metodo privado de mapa
        }else{
            seguirIterando = false;
        }
    }
    seguirIterando = true;
    while (seguirIterando){
        entidadActual = colaEntidadesNoColisionables.pop();
        if (entidadActual){
            cargarNoColisionable(entidadActual)   //Es un metodo privado de mapa
        }else{
            seguirIterando = false;
        }
    }
}




*/