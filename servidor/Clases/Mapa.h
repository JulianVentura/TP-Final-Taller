#ifndef __MAPA__
#define __MAPA__
#include "Quadtree.h"
#include "ObtenerCaja.h"
#include "Posicion.h"
#include "ObjetoColisionable.h"
#include "Posicionable.h"
#include "Entidad.h"
#include "Personaje.h"
#include "Criatura.h"
#include "Box.h"
#include "PosicionEncapsulada.h"
#include <vector>
#include <string>
#include <map>
#include <vector>

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
    unsigned int cantidadDeCriaturas;
    std::map<std::string, Personaje*> personajes; 
    std::map<std::string, Criatura*> criaturas;

    /*
    Devuelve true si la nueva posicion o el area no colisiona con
    algun Colisionable ya presente en el mapa.
    */
    bool posicionValida(const Posicion &nuevaPosicion);
    bool posicionValida(const quadtree::Box<float> &area);
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
    Elimina la identidad del mapa
    */
    void eliminarEntidad(Entidad *entidad);
    void eliminarEntidad(const std::string &id);
    void cargarEntidad(Entidad *entidad);
    void cargarCriatura(Criatura *criatura);
    
    // DEBUG
    std::string aCadena();
};

#endif

/*
Cosas para hacer en mapa

Levantar un JSON en el constructor que tendra los datos de todos los tiles (almacenar en un vector)
y los datos de todos los colisionables estaticos (Almacenar en el QuadTree).

Levantar del JSON a los comerciantes (mas adelante)

metodo para actualizarPosicion que reciba un Colisionable y un objeto posicion con la nueva posicion.

metodo para recolectar la posicion de todos los colisionables dinamicos.

metodo para obtener 


*/