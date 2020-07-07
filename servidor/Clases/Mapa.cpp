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
                                        tiles(),
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
    
    //MAPA VIEJO
    // TODO: esto en el mapa nuevo, es más complicado de armar
    
    //tiles = archivoJson.at("layers")[0].at("data").get<std::vector<char>>();
    //std::vector<quadtree::Box<float>> objetos = archivoJson.at("layers")[2].at("objects").get<std::vector<quadtree::Box<float>>>();
    //zonasRespawn = archivoJson.at("layers")[1].at("objects").get<std::vector<quadtree::Box<float>>>();
    
    //MAPA NUEVO
    
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
    //La idea es que el mapa sepa las posiciones del Sacerdote, Banquero y Comericante.
    std::unique_ptr<Interactuable> sacerdote(new Sacerdote(20, 20));
    std::unique_ptr<Interactuable> banquero(new Banquero(50, 50));
    std::unique_ptr<Interactuable> comerciante(new Comerciante(50, 50));
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

std::string Mapa::posicionesACadena(){
    std::string resultado;

    for (std::map<std::string, std::unique_ptr<Criatura>>::iterator it = criaturas.begin();
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
    return resultado;
}
Entidad* Mapa::obtener(const char* id){
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
        poblarCadena(criatura.second.get(), ancho_celdas, 'C', resultado);
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
