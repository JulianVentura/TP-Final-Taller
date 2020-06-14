#include "Clases/Mapa.h"
#include "Clases/Personaje.h"
#include <iostream>
#include <vector>
#define ARRIBA 'w'
#define ABAJO   's'
#define DERECHA 'd'
#define IZQUIERDA 'a'


void moverPersonaje(Personaje *personaje, Mapa &mapa, char c){
    Posicion posicion;
    switch (c){
        case ARRIBA:
            posicion = personaje->moverHaciaArriba();
            break;
        case ABAJO:
            posicion = personaje->moverHaciaAbajo();
            break;
        case DERECHA:
            posicion = personaje->moverHaciaDerecha();
            break;
        case IZQUIERDA:
            posicion = personaje->moverHaciaIzquierda();
            break;
        default:
            return;
    }
    mapa.actualizarPosicion(personaje, std::move(posicion));
}

std::vector<std::string> split(std::string &s, std::string &delimiter){
    size_t pos = 0;
    std::string token;
    std::vector<std::string> resultado;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        resultado.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    resultado.push_back(s);
    return resultado;
}




void imprimirPosiciones(Mapa &mapa){
    std::string posiciones = mapa.recolectarPosiciones();
    std::string delimitador = "$";
    std::vector<std::string> vector = split(posiciones, delimitador);
    delimitador = "/";
    for (std::size_t i=0; i<vector.size(); i++){
        std::vector<std::string> subVector = split(vector[i], delimitador);
        std::cout << std::endl;
        std::cout << "Nombre: " << subVector[0] << std::endl;
        std::cout << "x: " << subVector[1] << std::endl;
        std::cout << "y: " << subVector[2] << std::endl;
    }
}


int main(){
    try{
        bool continuar = true;
        char c;
        Mapa mapa("mapa1.json");
        Personaje personaje1(0, 0, "osvaldo");
        Personaje personaje2(30, 50, "edgardo");
        while (continuar){
            std::cin >> c;
            if (c == 'q') break;
            moverPersonaje(&personaje1, mapa, c);
            imprimirPosiciones(mapa);
        }
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }

    return 0;
}