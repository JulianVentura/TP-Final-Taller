#ifndef __BASE_DE_DATOS_H__
#define __BASE_DE_DATOS_H__

#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

#include <string>
#include <mutex>

#include "Personaje.h"
#include "Item.h"

#define TAM_CADENAS 20
#define TAM_BLOQUES (TAM_CADENAS*4 + sizeof(serializacionPersonaje))


class Personaje;
class Cliente;
class BaseDeDatos{
    private:
    uint32_t ultima_dir;
    std::mutex m;
    std::fstream archivo;
    nlohmann::json dirs;

    std::string leerCadena();

    void escribirCadena(std::string cadena);

    bool existeCliente(std::string id);

    void moverACliente(const std::string& nombre);

    void guardarDirs();
    
    public:
    BaseDeDatos();
    void nuevoCliente(std::pair<std::string, std::string> &credenciales, 
                      std::string& idRaza, std::string& idClase,
                      std::string& idMapa, Personaje *personaje);

    void guardarCliente(Cliente* cliente);

    std::pair<std::string, std::unique_ptr<Personaje>>
     cargarCliente(std::pair<std::string, std::string> &credenciales);

    bool verificarCliente(std::pair<std::string, std::string> &credenciales);

    ~BaseDeDatos();
};


#endif
