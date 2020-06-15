#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#define CANTIDAD_NODOS 4
#include <vector>
#include <list>
#include <memory>
#include "Rectangulo.h"
#include "Colisionable.h"

class QuadTreeOriginal {
    private:
    unsigned int nivel;
    std::list<Colisionable*> objetos;
    Rectangulo limites;
    std::unique_ptr<QuadTreeOriginal> nodos[CANTIDAD_NODOS];
    /*
    Constructor privado para usar internamente.
    */
    QuadTreeOriginal(unsigned int nivel, Rectangulo tamanio);
    /*

    */
    int obtenerIndice(Rectangulo &rectangulo);

    /*
    Divide el QuadTree en 4 QuadTree hijos, los cuales seran almacenados en
    el atributo nodos.
    */
    void dividir();

    /*
    Auxiliar de obtener()
    */
    void _obtener(std::list<Colisionable*> &listaResultado, Rectangulo &rectangulo);
    /*
    Auxiliar de remover())
    */
    void _remover(Colisionable* colisionable, bool &objetoEncontrado);

    public:
    /*
    Crea un QuadTree de tamanio 10, 10.
    */
    QuadTreeOriginal();
    /*
    Crea un QuadTree en el area especificada por el rectangulo tamanio.
    */
    QuadTreeOriginal(Rectangulo tamanio);
    /*
    Elimina todos los colisionables del QuadTree, dejandolo vacio.
    */
    void limpiar();

    /*
    Inserta un colisionable en el QuadTree.
    */
    void insertar(Colisionable* colisionable);
    /*
    Remueve un colisionable del QuadTree.
    */
    bool remover(Colisionable* colisionable);
    /*
    Devuelve una lista con todos los colisionables que se encuentran
    en el area definida por Rectangulo.
    */
    std::list<Colisionable*> obtener(Rectangulo &rectangulo);

    /*
    Devuelve una lista con todos los colisionables que estan colisionando
    con colisionable.
    */
    std::list<Colisionable*> obtener(Colisionable& colisionable);

};

#endif
