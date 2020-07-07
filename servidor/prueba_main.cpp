#include "Clases/Configuraciones.h"
#include "Clases/Interactuable.h"
#include "Clases/Sacerdote.h"
#include "Clases/Banquero.h"
#include "Clases/Personaje.h"
#include "Clases/Criatura.h"
#include "Clases/FabricaDeItems.h"
#include <iostream>
//Valores de retorno
#define EXITO 0
#define ERROR -1
//Validacion de parametros
#define NUMERO_PARAMETROS 2
#define POS_ARCHIVO_CONFIG 1

int pruebaInteractuables(const char* archivoConfig){
    try{
        Configuraciones::crearInstancia(archivoConfig);
        Criatura *criatura = new Criatura(0, 0, "Arania");
        //Configuraciones *config = Configuraciones::obtenerInstancia();
        Personaje *personaje = new Personaje(0, 0, "Julian", "Guerrero", "Humano");
        criatura->atacar(personaje);
        criatura->atacar(personaje);
        Interactuable *banquero = new Banquero();
        Interactuable *sacerdote = new Sacerdote();
        std::cout << "Personaje habla con banquero, estado normal" << std::endl;
        banquero->interactuar(personaje->obtenerEstado(), nullptr);
        banquero->comprar(0, personaje->obtenerEstado(), nullptr);
        banquero->vender(nullptr, personaje->obtenerEstado(), nullptr);
        std::cout << "Personaje habla con sacerdote, estado normal" << std::endl;
        sacerdote->interactuar(personaje->obtenerEstado(), nullptr);
        sacerdote->comprar(0, personaje->obtenerEstado(), nullptr);
        sacerdote->vender(nullptr, personaje->obtenerEstado(), nullptr);
        personaje->meditar();
        std::cout << "Personaje meditando habla con banquero" << std::endl;
        banquero->interactuar(personaje->obtenerEstado(), nullptr);
        banquero->comprar(0, personaje->obtenerEstado(), nullptr);
        banquero->vender(nullptr, personaje->obtenerEstado(), nullptr);
        std::cout << "Personaje meditando habla con sacerdote" << std::endl;
        sacerdote->interactuar(personaje->obtenerEstado(), nullptr);
        //personaje->estadoFantasma(); //Aca realizar un combate para que personaje muera
        std::cout << "Personaje fantasma habla con banquero" << std::endl;
        banquero->interactuar(personaje->obtenerEstado(), nullptr);
        banquero->comprar(0, personaje->obtenerEstado(), nullptr);
        banquero->vender(nullptr, personaje->obtenerEstado(), nullptr);
        std::cout << "Personaje fantasma habla con sacerdote" << std::endl;
        sacerdote->interactuar(personaje->obtenerEstado(), nullptr);
        std::cout << "Personaje curado habla con banquero" << std::endl;
        banquero->interactuar(personaje->obtenerEstado(), nullptr);
        banquero->comprar(0, personaje->obtenerEstado(), nullptr);
        banquero->vender(nullptr, personaje->obtenerEstado(), nullptr);


    }catch(const std::exception &e){
        std::cerr << e.what() <<std::endl;
        return ERROR;
    }catch(...){
        std::cerr << "Error desconocido capturado en pruebaServidor" <<std::endl;
        return ERROR;
    }
    return EXITO;
}

int main(int argc, const char* argv[]){
    return pruebaInteractuables(argv[POS_ARCHIVO_CONFIG]);
}


/*

Entidad *atacante = new Personaje;
Entidad *objetivo = new Personaje;

atacante.atacar(objetivo);

Personaje::atacar(Entidad *objetivo){
    objetivo.serAtacadoPor(this);
}

Personaje::serAtacadoPor(Personaje *atacante){
    //Chequear los niveles, si todo ok continuar
    atacante.atacar(this);
}

Personaje::atacar(Personaje *objetivo){
    arma.atacar(objetivo);
}


*/