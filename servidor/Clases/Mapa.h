#ifndef __MAPA_H__
#define __MAPA_H__
#include "Quadtree.h"
#include "ObtenerCaja.h"
#include "Posicion.h"
#include "ObjetoColisionable.h"
#include "Posicionable.h"
#include "Personaje.h"
#include "Criatura.h"
#include "Box.h"
#include "PosicionEncapsulada.h"
#include <vector>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "FabricaCriaturas.h"
#include <random>
#include <ctime>

class Entidad;
class Mapa{
    private:
    std::vector<char> tiles; //Esto solo nos sirve para imprimir el ascii art
    std::string contenido_archivo;
    unsigned int ancho;
    unsigned int alto;
    quadtree::Box<float> frontera;
    ObtenerCaja obtenerCaja;
    quadtree::Quadtree<Colisionable*, ObtenerCaja> quadTreeEstatico;
    quadtree::Quadtree<Colisionable*, ObtenerCaja> quadTreeDinamico;
    std::vector<ObjetoColisionable> objetosEstaticos;
    std::vector<quadtree::Box<float>> zonasRespawn;
    unsigned int limiteCriaturas;
    std::map<std::string, Personaje*> personajes; 
    std::map<std::string, std::unique_ptr<Criatura>> criaturas;
    FabricaCriaturas fabricaCriaturas;
    std::mt19937 motorAleatorio;
    /*
    Devuelve true si la nueva posicion o el area no colisiona con
    algun Colisionable ya presente en el mapa.
    */
    bool posicionValida(Entidad *entidad, const Posicion &nuevaPosicion);
    bool posicionValida(Entidad *entidad, const quadtree::Box<float> &area);
    /*
    Busca la posicion valida mas cercana a la posicion actual.
    */
    Posicion buscarPosicionValida(const Posicion &posicion);
    public:
    Mapa(std::string nombreArchivo);
    Mapa(Mapa &otroMapa) = delete;
    Mapa(Mapa &&otroMapa) = delete;
    /*
    Intenta actualizar la posicion del colisionable a nuevaPosicion.
    En caso de exito se actualiza la posicion en el mapa y se devuelve true.
    En caso de fallo no se actualiza nada y se devuelve false.
    */
    void actualizarPosicion(Entidad *entidad, Posicion &&nuevaPosicion);
    /*
    Devuelve un vector de chars con las posiciones de cada entidad dinamica del mapa.
    El vector estara compuesto de la siguiente forma:
    <id>/<posicionX>/<posicionY>$<id>/<posicionX>/<posicionY>
    */
    std::string posicionesACadena();
    /*
    Devuelve un vector de struct PosicionEncapsulada aka posicion_t
    */
    std::vector<struct PosicionEncapsulada> recolectarPosiciones();

    //Para indicarle a los clientes el tamanio del mapa necesito ancho y alto
    unsigned int obtenerAncho();
    unsigned int obtenerAlto();
    //Para indicarle a los clientes la info de cada Tile del mapa.
    const std::vector<char> obtenerInformacionMapa();
    /*
    Obtiene una entidad del mapa dado su id.
    */
    Entidad* obtener(const char* id);

    /*
    Carga un personaje al mapa y lo almacena segun su id
    */
    void cargarPersonaje(Personaje *personaje);

    /*
    Actualiza los estados de todas las entidades que se encuentren en el mapa
    segun tiempo.
    */
    void entidadesActualizarEstados(double tiempo);
    /*
    Elimina la entidad del mapa
    */
    void eliminarEntidad(Entidad *entidad);
    void eliminarEntidad(const std::string &id);
    void cargarEntidad(Entidad *entidad);
    void cargarCriatura();
    
    // DEBUG
    std::string aCadena();
};

#endif
