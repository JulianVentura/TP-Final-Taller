#include "QuadTree.h"
#define MAX_OBJETOS 4
#define MAX_NIVELES 10

/*
QuadTree migrado desde java.
Version original: https://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374
*/

template class QuadTree<Colisionable*>; // Por lo visto, por cada
                                        // clases que vayas a usar 
                                        // hay que definir esto
                                        // porque jode el linker, raro.

template<typename T>
QuadTree<T>::QuadTree() : nivel(0), limites(Rectangulo(0, 0, 10, 10)){}

template<typename T>
QuadTree<T>::QuadTree(unsigned int nivel, Rectangulo tamanio) : limites(std::move(tamanio)){
    for (unsigned int i=0; i<CANTIDAD_NODOS; i++){
        nodos[i] = nullptr;
    }
    nivel = nivel;
}

template<typename T>
QuadTree<T>::QuadTree(Rectangulo tamanio) : limites(std::move(tamanio)){
    for (unsigned int i=0; i<CANTIDAD_NODOS; i++){
        nodos[i] = nullptr;
    }
    nivel = 0;
}

template<typename T>
int QuadTree<T>::obtenerIndice(Rectangulo &rectangulo){
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

template<typename T>
void QuadTree<T>::dividir(){
    int subAncho = (int)(limites.obtenerAncho() / 2);
    int subAlto  = (int)(limites.obtenerAlto()  / 2);
    int x = (int)limites.obtenerX();
    int y = (int)limites.obtenerY();
    
    nodos[0] = std::unique_ptr<QuadTree>(new QuadTree(nivel+1, Rectangulo(x + subAncho, y, subAncho, subAlto)));
    nodos[1] = std::unique_ptr<QuadTree>(new QuadTree(nivel+1, Rectangulo(x, y, subAncho, subAlto)));
    nodos[2] = std::unique_ptr<QuadTree>(new QuadTree(nivel+1, Rectangulo(x, y + subAlto, subAncho, subAlto)));
    nodos[3] = std::unique_ptr<QuadTree>(new QuadTree(nivel+1, Rectangulo(x + subAncho, y + subAlto, subAncho, subAlto)));
}

template<typename T>
void QuadTree<T>::limpiar(){
    for (unsigned int i=0; i<CANTIDAD_NODOS; i++){
        if (nodos[i] != nullptr){
            nodos[i]->limpiar();
            nodos[i] = nullptr;
        }
    }
}

template<typename T>
void QuadTree<T>::insertar(T data){
    if (nodos[0] != nullptr){
        int indice = obtenerIndice(data->obtenerArea());
        if (indice != -1){
            nodos[indice]->insertar(data);
            return;
        }
    }
    objetos.push_back(data);
    if (objetos.size() > MAX_OBJETOS && nivel < MAX_NIVELES){
        if (nodos[0] == nullptr) dividir();
    
        typename std::list<T>::iterator it = objetos.begin();
        while (it != objetos.end()){
            int indice = obtenerIndice((*it)->obtenerArea());
            if (indice != -1){
                nodos[indice]->insertar((*it));
                it = objetos.erase(it);
            }else{
                ++it;
            }
        }
    }
}

template<typename T>
void QuadTree<T>::_obtener(std::list<T> &listaResultado, 
                        Rectangulo &rectangulo){
    int indice = obtenerIndice(rectangulo);
    if (indice != -1 && nodos[0] != nullptr){
        nodos[indice]->_obtener(listaResultado, rectangulo);
    }
    listaResultado.insert(listaResultado.end(), objetos.begin(), objetos.end());
}

template<typename T>
std::list<T> QuadTree<T>::obtener(Rectangulo &rectangulo){
    std::list<T> listaResultado;
    _obtener(listaResultado, rectangulo);
    return listaResultado;
}

template<typename T>
std::list<T> QuadTree<T>::obtener(T& colisionable){
    return obtener(colisionable->obtenerArea());
}

template<typename T>
bool QuadTree<T>::remover(T colisionable){
    bool objetoEncontrado = false;
    _remover(colisionable, objetoEncontrado);
    return objetoEncontrado;
}

template<typename T>
void QuadTree<T>::_remover(T colisionable, bool &objetoEncontrado){
    int indice = obtenerIndice(colisionable->obtenerArea());
    if (indice != -1 && nodos[0] != nullptr){
        nodos[indice]->_remover(colisionable, objetoEncontrado);
    }
    if (objetoEncontrado) return;
    typename std::list<T>::iterator it = objetos.begin();
    while (it != objetos.end()){
        if ((*it) == colisionable) {
            it = objetos.erase(it);
            objetoEncontrado = true;
        } else {
            ++it;
        }
    }
}
