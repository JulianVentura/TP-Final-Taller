#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#define CANTIDAD_NODOS 4
#include <vector>
#include <list>
#include <memory>
#include "Rectangulo.h"
#include "Colisionable.h"

class QuadTree{
    private:
    unsigned int nivel;
    std::list<Colisionable*> objetos;
    Rectangulo limites;
    std::unique_ptr<QuadTree> nodos[CANTIDAD_NODOS];
    /*
    Constructor privado para usar internamente.
    */
    QuadTree(unsigned int nivel, Rectangulo tamanio);
    /*

    */
    int obtenerIndice(Rectangulo &rectangulo);

    /*

    */
    void dividir();

    /*
    Auxiliar de obtener()
    */
    void _obtener(std::list<Colisionable*> &listaResultado, Rectangulo &rectangulo);
    public:
    /*
    Crea un QuadTree en el area especificada por el rectangulo tamanio.
    */
    QuadTree(Rectangulo tamanio);
    /*
    Elimina todos los colisionables del QuadTree, dejandolo vacio.
    */
    void limpiar();

    /*
    Inserta un colisionable en el QuadTree.
    */
    void insertar(Colisionable* colisionable);

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
