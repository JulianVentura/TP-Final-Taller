#ifndef __MAPA_H__
#define __MAPA_H__
#include "Quadtree.h"
#include "ObtenerCaja.h"
#include "Posicion.h"
#include "ObjetoColisionable.h"
#include "Personaje.h"
#include "Criatura.h"
#include "Interactuable.h"
#include "BolsaDeItems.h"
#include "ColaDeEntidades.h"
#include "Box.h"
#include <mutex>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>
#include <memory>
#include <atomic>
#include "FabricaDeNPC.h"
#include <random>
#include <ctime>


class Entidad;
class Mapa{
    private:
    std::string nombreMapa;
    std::mutex mutex;
    std::string contenido_archivo;
    quadtree::Box<float> frontera;
    ObtenerCaja obtenerCaja;
    quadtree::Quadtree<Colisionable*, ObtenerCaja> quadTreeEstatico;
    quadtree::Quadtree<Entidad*, ObtenerCaja> quadTreeDinamico;
    std::vector<ObjetoColisionable> objetosEstaticos;
    ColaDeEntidades colaDeCarga;
    std::vector<quadtree::Box<float>> zonasRespawn;
    unsigned int limiteCriaturas;
    std::atomic<unsigned int> cantidadCriaturas;
    double tiempoRespawn;
    double tiempoTranscurrido;
    std::unordered_map<std::string, Entidad*> entidades;
    std::list<std::unique_ptr<Entidad>> npcs;

    FabricaDeNPC fabricaNPC;
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

    /*
    Buscara spawnear una nueva Criatura aleatoria en alguna de las zonas de respawn.
    */
    void cargarCriatura();

    void cargar(Entidad *entidad);

    public:
    Mapa(std::string nombre);
    Mapa(Mapa &otroMapa) = delete;
    Mapa(Mapa &&otroMapa) = delete;
    /*
    Intenta actualizar la posicion del colisionable a nuevaPosicion.
    En caso de exito se actualiza la posicion en el mapa y se devuelve true.
    En caso de fallo no se actualiza nada y se devuelve false.
    */
    void actualizarPosicion(Entidad *entidad, Posicion &&nuevaPosicion);
    /*
    Devuelve un vector de struct PosicionEncapsulada aka posicion_t
    */
    std::vector<struct PosicionEncapsulada> recolectarPosiciones();
    
    //Para indicarle a los clientes la info de cada Tile del mapa.
    const std::vector<char> obtenerInformacionMapa();
    /*
    Obtiene una entidad del mapa dado su id.
    */
    Entidad* obtener(std::string &id);

    std::vector<Entidad*> obtenerEntidades(quadtree::Box<float> &&area);
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
    void eliminarEntidadNoColisionable(Entidad *entidad);
    /*
    Disminuye el contador de criaturas.
    */
    void eliminarCriatura();
    /*
    Carga una nueva entidad al mapa
    */
    void cargarEntidad(Entidad *entidad);
    void cargarEntidad(std::unique_ptr<Entidad> entidad);
    void cargarEntidadNoColisionable(Entidad *entidad);
    void cargarEntidadNoColisionable(std::unique_ptr<Entidad> entidad);

};

#endif
