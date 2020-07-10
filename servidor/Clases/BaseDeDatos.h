#ifndef __BASE_DE_DATOS_H__
#define __BASE_DE_DATOS_H__

#include <iostream>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

#include <string>
#include <mutex>

#include "Personaje.h"

#define TAM_BLOQUES 20
#define TAM_CADENAS 20

class Personaje;
class BaseDeDatos{
    private:
    uint32_t ultima_dir;
    std::mutex m;
    std::fstream archivo;
    nlohmann::json dirs;

    std::string leerCadena();

    void escribirCadena(std::string cadena);

    public:
    BaseDeDatos();
    void nuevoCliente(std::pair<std::string, std::string> &credenciales, 
                      std::string &mapaActual, Personaje *personaje);

    void guardarCliente(std::string &id);

    std::pair<std::string, std::unique_ptr<Personaje>>
     cargarCliente(std::pair<std::string, std::string> &credenciales);

    bool verificarCliente(std::pair<std::string, std::string> &credenciales);

    void guardarDirs();
};


#endif
