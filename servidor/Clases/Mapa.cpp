#include "Mapa.h"
#include "Rectangulo.h"
//#include "../nlohmann_json/include/nlohmann/json.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <utility>
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
        //Cambiar por excepcion propia
        throw std::exception();
    }
    json archivoJson;
    archivo >> archivoJson;
    alto  = archivoJson.at("height").get<unsigned int>();
    ancho = archivoJson.at("width").get<unsigned int>();
    tiles = archivoJson.at("layers")[0].at("data").get<std::vector<char>>();
    std::vector<Rectangulo> objetos = archivoJson.at("layers")[1].at("objects").get<std::vector<Rectangulo>>();
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
    for (std::map<std::string, Criatura>::iterator it = criaturas.begin();
         it != criaturas.end();
         ++it){
        resultado + it->first + '/' + it->second.imprimirPosicion() + '$';
    }
    for (std::map<std::string, Personaje*>::iterator it = personajes.begin();
         it != personajes.end();
         ++it){
        resultado + it->first + '/' + it->second->imprimirPosicion() + '$';
    }
    return resultado;
}

Entidad* Mapa::obtener(const char* id){
    std::map<std::string, Criatura>::iterator Cit = criaturas.find(id);
    std::map<std::string, Personaje*>::iterator Pit = personajes.find(id);
    if (Cit == criaturas.end()){
        if (Pit == personajes.end()){
            throw std::exception(); //Cambiar por una propia
        }else{
            return Pit->second;
        }
    }else{
        return &Cit->second;
    }
}


void Mapa::cargarPersonaje(Personaje *personaje){
    personajes[personaje->obtenerId()] = personaje;
    //Antes de insertar hay que chequear que no colisione con algo FALTA HACER ESO
    quadTreeDinamico.insertar(personaje);
}


bool Mapa::posicionValida(Posicion &nuevaPosicion){
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
