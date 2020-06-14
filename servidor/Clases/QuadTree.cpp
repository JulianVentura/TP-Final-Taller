#include "QuadTree.h"
#define MAX_OBJETOS 10
#define MAX_NIVELES 5

QuadTree::QuadTree(unsigned int nivel, Rectangulo tamanio) : limites(std::move(tamanio)){
    for (unsigned int i=0; i<CANTIDAD_NODOS; i++){
        nodos[i] = nullptr;
    }
    nivel = nivel;
}

QuadTree::QuadTree(Rectangulo tamanio) : limites(std::move(tamanio)){
    for (unsigned int i=0; i<CANTIDAD_NODOS; i++){
        nodos[i] = nullptr;
    }
    nivel = 0;
}

int QuadTree::obtenerIndice(Rectangulo &rectangulo){
    int indice = -1;
    Rectangulo cuadranteIzquierdo(limites.obtenerX(), 
                                  limites.obtenerY(), 
                                  limites.obtenerX() + limites.obtenerAncho() / 2, 
                                  limites.obtenerY() + limites.obtenerAlto());

    Rectangulo cuadranteSuperior( limites.obtenerX(), 
                                  limites.obtenerY(), 
                                  limites.obtenerX() + limites.obtenerAncho(), 
                                  limites.obtenerY() + limites.obtenerAlto() / 2);
    //Hay que ver que se hace si el rectangulo se superpone con los limites.
    bool perteneceCuadranteSuperior = cuadranteSuperior.contieneA(rectangulo);
    bool perteneceCuadranteIzquierdo = cuadranteIzquierdo.contieneA(rectangulo);
    if (perteneceCuadranteIzquierdo){
        if (perteneceCuadranteSuperior){
            indice = 1;
        }else{
            indice = 2;
        }
    }else{
        if (perteneceCuadranteSuperior){
            indice = 0;
        }else{
            indice = 3;
        }
    }
    return indice;
}

void QuadTree::dividir(){
    int subAncho = (int)(limites.obtenerAncho() / 2);
    int subAlto  = (int)(limites.obtenerAlto()  / 2);
    int x = (int)limites.obtenerX();
    int y = (int)limites.obtenerY();

    nodos[0] = std::unique_ptr<QuadTree>(new QuadTree(nivel+1, Rectangulo(x + subAncho, y, subAncho, subAlto)));
    nodos[1] = std::unique_ptr<QuadTree>(new QuadTree(nivel+1, Rectangulo(x, y, subAncho, subAlto)));
    nodos[2] = std::unique_ptr<QuadTree>(new QuadTree(nivel+1, Rectangulo(x, y + subAlto, subAncho, subAlto)));
    nodos[3] = std::unique_ptr<QuadTree>(new QuadTree(nivel+1, Rectangulo(x + subAncho, y + subAlto, subAncho, subAlto)));
}


void QuadTree::limpiar(){
    for (unsigned int i=0; i<CANTIDAD_NODOS; i++){
        if (nodos[i].get() != nullptr){
            nodos[i].get()->limpiar();
            nodos[i] = nullptr;
        }
    }
}


void QuadTree::insertar(Colisionable* colisionable){
    if (nodos[0] != nullptr){
        int indice = obtenerIndice(colisionable->obtenerArea());
        if (indice != -1){
            nodos[indice].get()->insertar(colisionable);
            return;
        }
    }
    objetos.push_back(colisionable);
    if (objetos.size() > MAX_OBJETOS && nivel < MAX_NIVELES){
        if (nodos[0] == nullptr) dividir();
    }

    std::list<Colisionable*>::iterator it = objetos.begin();
    while (it != objetos.end()){
        int indice = obtenerIndice((*it)->obtenerArea());
        if (indice != -1){
            nodos[indice].get()->insertar((*it));
            it = objetos.erase(it);
        }else{
            ++it;
        }
    }
}

void QuadTree::_obtener(std::list<Colisionable*> &listaResultado, 
                        Rectangulo &rectangulo){
    int indice = obtenerIndice(rectangulo);
    if (indice != -1 && nodos[0] != nullptr){
        nodos[indice].get()->_obtener(listaResultado, rectangulo);
    }
    
    listaResultado.insert(listaResultado.end(), objetos.begin(), objetos.end());

}

std::list<Colisionable*> QuadTree::obtener(Rectangulo &rectangulo){
    std::list<Colisionable*> listaResultado;
    _obtener(listaResultado, rectangulo);
    return listaResultado;
}


std::list<Colisionable*> QuadTree::obtener(Colisionable& colisionable){
    return obtener(colisionable.obtenerArea());
}