#include "Clases/Mapa.h"
#include "Clases/Personaje.h"
#include "Clases/Sala.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
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
    for (std::size_t i=0; i<vector.size() - 1; i++){ // Creo que debería ser -1
                                                     // Porque si tenes 
                                                     // jugador1/x/y$jugador2/x/y$
                                                     // Te en el split te quedan
                                                     // 3: ["jugador1/x/y", "jugador2/x/y", ""]
        std::vector<std::string> subVector = split(vector[i], delimitador);
        std::cout << std::endl;
        std::cout << "Nombre: " << subVector[0] << std::endl;
        std::cout << "x: " << subVector[1] << std::endl;
        std::cout << "y: " << subVector[2] << std::endl;
    }
}
/*
void imprimirMapa(Mapa &mapa){
    double ancho = mapa.obtenerAncho();
    double alto = mapa.obtenerAlto();
}
*/
void pruebaMapa(){
    try{
        bool continuar = true;
        char c;
        Mapa mapa("mapa1.json");
        Personaje personaje1(0, 0, "jugador1");
        Personaje personaje2(20, 60, "jugador2");
        mapa.cargarPersonaje(&personaje1);
        mapa.cargarPersonaje(&personaje2);
        while (continuar) {
            std::cin >> c;
            if (c == 'q') break;
            moverPersonaje(&personaje1, mapa, c);
            imprimirPosiciones(mapa);
            //imprimirMapa(mapa);
            std::cout << mapa.aCadena();
        }
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}

void pruebaReloj1(){
    Reloj reloj;
    double transcurrido = 0;
    unsigned int i = 0;
    double MS_SLEEP = 10;
    while(i < 20){
        transcurrido = reloj.actualizar();
        reloj.dormir(MS_SLEEP);
        std::cout << "Se indico sleep por " << transcurrido << " y se durmio por " << reloj.tiempoTranscurrido() << std::endl;
        i++;
    }
}

void pruebaReloj(){
    Reloj reloj;
    double transcurrido = 0;
    unsigned int i = 0;
    double MS_SLEEP = 10;
    while(i < 20){
        transcurrido = reloj.actualizar();
        reloj.dormir(MS_SLEEP);
        std::cout << "Se indico sleep por " << transcurrido << " y se durmio por " << reloj.tiempoTranscurrido() << std::endl;
        i++;
    }
}

void pruebaSala(){
    try{
        Sala sala("mapa1");
        bool continuar = true;
        char c = 0;
        while (continuar) {
            std::cin >> c;
            if (c == 'q'){
                continuar = false;
            }
        }
    }catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}

int main(){
    pruebaMapa();
    return 0;
}