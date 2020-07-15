#include "Clases/Configuraciones.h"
#include "Clases/Interactuable.h"
#include "Clases/Sacerdote.h"
#include "Clases/Banquero.h"
#include "Clases/Personaje.h"
#include "Clases/Criatura.h"
#include "Clases/FabricaDeItems.h"
#include "Clases/Mapa.h"
#include "Clases/Raza.h"
#include "Clases/Clase.h"
#include "Clases/OrganizadorClientes.h"
#include "Clases/Divulgador.h"
#include <iostream>
//Valores de retorno
#define EXITO 0
#define ERROR -1
//Validacion de parametros
#define NUMERO_PARAMETROS 2
#define POS_ARCHIVO_CONFIG 1


int pruebaLanzamientoProyectiles(const char* archivoConfig){
    try{
        Configuraciones::crearInstancia(archivoConfig);
        OrganizadorClientes organizador;
        Divulgador::inicializarInstancia(&organizador);
        Mapa mapa("mapa");
        Personaje personaje1(200, 200, "Ricardo", "Guerrero", "Humano");
        Personaje personaje2(205, 205, "Edgardo", "Guerrero", "Humano");
        mapa.cargarEntidad(&personaje1);
        mapa.cargarEntidad(&personaje2);
        personaje1.serAtacadoPor(&personaje2);
        mapa.entidadesActualizarEstados(300);
        mapa.entidadesActualizarEstados(300);
        mapa.entidadesActualizarEstados(300);
        mapa.entidadesActualizarEstados(300);

    }catch(const std::exception &e){
        std::cerr << e.what() <<std::endl;
        return ERROR;
    }catch(...){
        std::cerr << "Error desconocido capturado en pruebaServidor" <<std::endl;
        return ERROR;
    }

    return EXITO;
}


int pruebaInteractuables(const char* archivoConfig){
    /*
    try{
        
        Configuraciones::crearInstancia(archivoConfig);
        Mapa *mapa = new Mapa("mapa");
        Divulgador *divulgador = nullptr;
        Criatura *criatura = new Criatura(0, 0, "Arania");
        mapa->cargarEntidad(criatura);
        Personaje *personaje = new Personaje(0, 0, "Julian", "Guerrero", "Humano");
        criatura->atacar(personaje, divulgador);
        criatura->atacar(personaje, divulgador);
        Interactuable *banquero = new Banquero(0, 0);
        Interactuable *sacerdote = new Sacerdote(0, 0);
        std::cout << "Personaje habla con banquero, estado normal" << std::endl;
        banquero->interactuar(personaje->obtenerEstado(), nullptr);
        banquero->comprar(0, personaje->obtenerEstado(), nullptr);
        banquero->vender(0, personaje, nullptr);
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

    */
    return EXITO;
    
}


int pruebaCreacionObjetos(const char* nombreArchivo){
    try{
        Configuraciones::crearInstancia(nombreArchivo);
        FabricaDeItems *fabricaItems = FabricaDeItems::obtenerInstancia();
        //Armas
        std::string idItem = "Espada";
        fabricaItems->crearArma(idItem);
        idItem = "Hacha";
        fabricaItems->crearArma(idItem);
        idItem = "Martillo";
        fabricaItems->crearArma(idItem);
        idItem = "VaraDeFresno";
        fabricaItems->crearArma(idItem);
        idItem = "FlautaElfica";
        fabricaItems->crearArma(idItem);
        idItem = "BaculoNudoso";
        fabricaItems->crearArma(idItem);
        idItem = "BaculoEngarzado";
        fabricaItems->crearArma(idItem);
        idItem = "ArcoSimple";
        fabricaItems->crearArma(idItem);
        idItem = "ArcoCompuesto";
        fabricaItems->crearArma(idItem);
        idItem = "Garra";
        fabricaItems->crearArma(idItem);
        idItem = "ManoHuesuda";
        fabricaItems->crearArma(idItem);
        idItem = "ManoPodrida";
        fabricaItems->crearArma(idItem);
        idItem = "ColmilloVenenoso";
        fabricaItems->crearArma(idItem);
        //Armaduras
        idItem = "ArmaduraDeCuero";
        fabricaItems->crearArmadura(idItem);
        idItem = "ArmaduraDePlacas";
        fabricaItems->crearArmadura(idItem);
        idItem = "TunicaAzul";
        fabricaItems->crearArmadura(idItem);
        //Cascos
        idItem = "Capucha";
        fabricaItems->crearCasco(idItem);
        idItem = "CascoDeHierro";
        fabricaItems->crearCasco(idItem);
        idItem = "SombreroMagico";
        fabricaItems->crearCasco(idItem);
        //Escudos
        idItem = "EscudoDeTortuga";
        fabricaItems->crearEscudo(idItem);
        idItem = "EscudoDeHierro";
        fabricaItems->crearEscudo(idItem);
        //Pociones
        idItem = "PocionVida";
        fabricaItems->crearPocion(idItem);
        idItem = "PocionMana";
        fabricaItems->crearPocion(idItem);


        //Razas
        Raza raza1("Humano");
        Raza raza2("Elfo");
        Raza raza3("Enano");
        Raza raza4("Gnomo");

        //Clases
        Clase clase1("Guerrero");
        Clase clase2("Mago");
        Clase clase3("Paladin");
        Clase clase4("Clerigo");

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
    return pruebaLanzamientoProyectiles(argv[POS_ARCHIVO_CONFIG]);
}
