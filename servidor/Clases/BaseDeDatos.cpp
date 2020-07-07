#include "BaseDeDatos.h"
#include "Personaje.h"


BaseDeDatos::BaseDeDatos() : numero(0){
    //Do nothing
}

void BaseDeDatos::nuevoCliente(std::pair<std::string, std::string> &credenciales, 
                               std::string &mapaActual,
                               Personaje *personaje){
    //
}

void BaseDeDatos::actualizarDatos(std::string &id){
    //
}

//Necesito el id del mapa y el Personaje
std::pair<std::string, std::unique_ptr<Personaje>> BaseDeDatos::recuperarInformacion(std::pair<std::string, std::string> &credenciales){
    std::unique_ptr<Personaje> personaje(new Personaje(0, 0, "Jugador1", "Paladin", "Humano"));
    return std::pair<std::string, std::unique_ptr<Personaje>>("mapa", std::move(personaje));
}

//Chequea que el id exista y la contraseña sea valida
bool BaseDeDatos::idExistente(std::pair<std::string, std::string> &credenciales){
    //
    return true;
}