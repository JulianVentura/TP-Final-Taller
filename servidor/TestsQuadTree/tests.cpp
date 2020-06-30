#include "Colisionable.h"
#include "Personaje.h"
#include "Entidad.h"
#include "Quadtree.h"
#include "Box.h"
#include "ObtenerCaja.h"
#include <iostream>


void testColisiones(quadtree::Quadtree<Colisionable*, ObtenerCaja> &quadtree, 
                    quadtree::Box<float> &zona, unsigned int numColisiones, unsigned int num){
    std::vector<Colisionable*> resultado = quadtree.query(zona);
    unsigned int i = resultado.size();
    if (i < numColisiones || i > numColisiones){
        std::cout << "Fallo el test numero " << num << std::endl;
    }else{
        std::cout << "Test numero " << num << " exitoso"<< std::endl;
    }
}


void pruebaQuadTree(){
    try{
        ObtenerCaja obtenerCaja;
        quadtree::Box<float> caja(0, 0, 100, 100);
        quadtree::Quadtree<Colisionable*, ObtenerCaja> quadtree(caja, obtenerCaja);
        Personaje personaje1(10, 5, "jugador1");
        Personaje personaje2(20, 5, "jugador2");
        Personaje personaje3(30, 6, "jugador3");
        Personaje personaje4(4, 30, "jugador4");
        Personaje personaje5(80, 80, "jugador5");
        Personaje personaje6(80, 5, "jugador6");
        Personaje personaje7(5, 80, "jugador7");
        quadtree.add(&personaje1);
        quadtree.add(&personaje2);
        quadtree.add(&personaje3);
        quadtree.add(&personaje4);
        quadtree.add(&personaje5);
        quadtree.add(&personaje6);
        quadtree.add(&personaje7);
        //Test
        quadtree::Box<float> caja_test0(0, 0, 100, 100); //7
        quadtree::Box<float> caja_test1(0, 0, 31, 31); //4
        quadtree::Box<float> caja_test2(50, 50, 50, 50); //1
        quadtree::Box<float> caja_test3(50, 0, 50, 50); //1
        quadtree::Box<float> caja_test4(0, 50, 50, 50); //1

        testColisiones(quadtree, caja_test0, 7, 0);
        testColisiones(quadtree, caja_test1, 4, 1);
        testColisiones(quadtree, caja_test2, 1, 2);
        testColisiones(quadtree, caja_test3, 1, 3);
        testColisiones(quadtree, caja_test4, 1, 4);
        std::cout << "Prueba eliminar nodos" << std::endl;
        //Remover nodos
        //Removemos uno solo
        std::cout << "Removemos un nodo..." << std::endl;
        quadtree.remove(&personaje1);
        testColisiones(quadtree, caja_test0, 6, 0);
        testColisiones(quadtree, caja_test1, 3, 1);
        testColisiones(quadtree, caja_test2, 1, 2);
        testColisiones(quadtree, caja_test3, 1, 3);
        testColisiones(quadtree, caja_test4, 1, 4);
        std::cout << "Lo reinsertamos..." << std::endl;
        //Reinsertamos el nodo
        quadtree.add(&personaje1);
        testColisiones(quadtree, caja_test0, 7, 0);
        testColisiones(quadtree, caja_test1, 4, 1);
        testColisiones(quadtree, caja_test2, 1, 2);
        testColisiones(quadtree, caja_test3, 1, 3);
        testColisiones(quadtree, caja_test4, 1, 4);
        //Removemos 3 nodos
        std::cout << "Removemos 3 nodos..." << std::endl;
        quadtree.remove(&personaje1);
        quadtree.remove(&personaje6);
        quadtree.remove(&personaje7);
        testColisiones(quadtree, caja_test0, 4, 0);
        testColisiones(quadtree, caja_test1, 3, 1);
        testColisiones(quadtree, caja_test2, 1, 2);
        testColisiones(quadtree, caja_test3, 0, 3);
        testColisiones(quadtree, caja_test4, 0, 4);
        //Reinsertamos los 3 nodos
        std::cout << "Los reinsertamos..." << std::endl;
        quadtree.add(&personaje1);
        quadtree.add(&personaje6);
        quadtree.add(&personaje7);
        testColisiones(quadtree, caja_test0, 7, 0);
        testColisiones(quadtree, caja_test1, 4, 1);
        testColisiones(quadtree, caja_test2, 1, 2);
        testColisiones(quadtree, caja_test3, 1, 3);
        testColisiones(quadtree, caja_test4, 1, 4);
        //Removemos todos los nodos
        std::cout << "Removemos todos los nodos..." << std::endl;
        quadtree.remove(&personaje1);
        quadtree.remove(&personaje2);
        quadtree.remove(&personaje3);
        quadtree.remove(&personaje4);
        quadtree.remove(&personaje5);
        quadtree.remove(&personaje6);
        quadtree.remove(&personaje7);
        testColisiones(quadtree, caja_test0, 0, 0);
        testColisiones(quadtree, caja_test1, 0, 1);
        testColisiones(quadtree, caja_test2, 0, 2);
        testColisiones(quadtree, caja_test3, 0, 3);
        testColisiones(quadtree, caja_test4, 0, 4);
        //Reinsertamos todos los nodos
        std::cout << "Reinsertamos todos los nodos..." << std::endl;
        quadtree.add(&personaje1);
        quadtree.add(&personaje2);
        quadtree.add(&personaje3);
        quadtree.add(&personaje4);
        quadtree.add(&personaje5);
        quadtree.add(&personaje6);
        quadtree.add(&personaje7);
        testColisiones(quadtree, caja_test0, 7, 0);
        testColisiones(quadtree, caja_test1, 4, 1);
        testColisiones(quadtree, caja_test2, 1, 2);
        testColisiones(quadtree, caja_test3, 1, 3);
        testColisiones(quadtree, caja_test4, 1, 4);
        //Limpiamos el quadtree
        /*
        std::cout << "Limpiamos el quadtree..." << std::endl;
        quadtree.
        testColisiones(quadtree, caja_test0, 0, 0);
        testColisiones(quadtree, caja_test1, 0, 1);
        testColisiones(quadtree, caja_test2, 0, 2);
        testColisiones(quadtree, caja_test3, 0, 3);
        testColisiones(quadtree, caja_test4, 0, 4);
        */


    }catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}


int main(){

    pruebaQuadTree();
    return 0;
}