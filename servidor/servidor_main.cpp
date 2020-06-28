#include "Clases/Mapa.h"
#include "Clases/Personaje.h"
#include "Clases/Sala.h"
#include "Clases/OperacionMover.h"
#include "Clases/ColaSegura.h"
#include "Clases/OperacionEncapsulada.h"
#include "Clases/Cliente.h"
#include "Clases/Criatura.h"
#include "Clases/Servidor.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#define ARRIBA 'w'
#define ABAJO   's'
#define DERECHA 'd'
#define IZQUIERDA 'a'

void moverPersonaje(char c, ColaSegura *cola, Personaje *personaje){
    //Posicion posicion;
    switch (c){
        case ARRIBA:
            cola->push(OperacionEncapsulada(new OperacionMover(personaje, MOVER_ARRIBA)));
            break;
        case ABAJO:
            cola->push(OperacionEncapsulada(new OperacionMover(personaje, MOVER_ABAJO)));
            break;
        case DERECHA:
            cola->push(OperacionEncapsulada(new OperacionMover(personaje, MOVER_DERECHA)));
            break;
        case IZQUIERDA:
            cola->push(OperacionEncapsulada(new OperacionMover(personaje, MOVER_IZQUIERDA)));
            break;
    }
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
    std::string posiciones = mapa.posicionesACadena();
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
/*
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
*/

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

void pruebaSalaYMapa(){
    try{
        bool continuar = true;
        char c = 0;
        std::string nombre_mapa("mapa2");
        Sala sala(nombre_mapa.c_str());
        //ColaSegura *cola = sala.obtenerCola();
        //Cliente cliente("jugador", nombre_mapa, sala);
        //Cliente cliente2("jugador2", nombre_mapa, sala);
        //Criatura criatura(10, 10, "Araña");
        //Personaje *personaje = cliente.obtenerPersonaje();
        while (continuar){
            std::cin >> c;
            if (c == 'q') break;
            //moverPersonaje(c, cola, personaje);
        }
        sala.finalizar();
    }catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}

void pruebaServidor(){
    try{
        Servidor servidor("8080");
        servidor.procesar();
    }catch(const std::exception &e){
        std::cerr << e.what() <<std::endl;
    }catch(...){
        std::cerr << "Error desconocido capturado en pruebaServidor" <<std::endl;
    }
}

int main(){
    //pruebaSalaYMapa();
    pruebaServidor();
    return 0;
}