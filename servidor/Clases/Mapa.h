#ifndef __MAPA__
#define __MAPA__
#include "QuadTree.h"
#include "Posicion.h"
#include "ObjetoColisionable.h"
#include "Posicionable.h"
#include "Entidad.h"
#include "Personaje.h"
#include "Criatura.h"
#include <vector>
#include <string>
#include <map>

class Mapa{
    private:
    std::vector<char> tiles;
    unsigned int ancho;
    unsigned int alto;
    QuadTree<Colisionable*> quadTreeEstatico;
    QuadTree<Colisionable*> quadTreeDinamico;
    std::vector<ObjetoColisionable> objetosEstaticos;
    unsigned int cantidadDeCriaturas;
    std::map<std::string, Personaje*> personajes; 
    std::map<std::string, Criatura*> criaturas; // Con punteros funciona
                                                // Por lo que estuve viendo
                                                // Una de las clases de las que
                                                // hereda, tiene deleteado
                                                // un constructor que se ve que
                                                // `pair` del map necesita.

    bool posicionValida(Posicion &nuevaPosicion);

    public:
    Mapa(const char* nombreArchivo);
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
    std::string recolectarPosiciones();
    //Colisionable& obtener(const char* id);

    //Para indicarle a los clientes el tamanio del mapa necesito ancho y alto
    unsigned int obtenerAncho();
    unsigned int obtenerAlto();
    //Para indicarle a los clientes la info de cada Tile del mapa.
    std::vector<char> obtenerInformacionMapa();
    /*
    Obtiene una entidad del mapa dado su id.
    */
    Entidad* obtener(const char* id);

    /*
    Carga un personaje al mapa y lo almacena segun su id
    */
    void cargarPersonaje(Personaje *personaje);

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