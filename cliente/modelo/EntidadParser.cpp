#include "EntidadParser.h"
#include <vector>
#include <utility>
#include <map>
#include <cctype>
#include <algorithm>
#include <fstream>
#define RUTA_INFO "assets/imagenes.json"
#define DELIMITADOR "-"
#define DELIMITADOR_RUTA "/"
#define BASE "base"
#define QUIETO "quieto"
#define QUIETO_VALOR -1
using json = nlohmann::json;

const imagenes_t EntidadParser::aparienciaImagenesBase = {
    { "cuerpo", std::vector<Imagen*>() },
    { "ojos", std::vector<Imagen*>() },
    { "cicatrices", std::vector<Imagen*>() },
    { "nariz", std::vector<Imagen*>() },
    { "orejas", std::vector<Imagen*>() },
    { "facial", std::vector<Imagen*>() },
    { "pies", std::vector<Imagen*>() },
    { "piernas", std::vector<Imagen*>() },
    { "torso", std::vector<Imagen*>() },
    { "cinto", std::vector<Imagen*>() },
    { "pelo", std::vector<Imagen*>() },
    { "cabeza", std::vector<Imagen*>() }
};

EntidadParser::EntidadParser(EntornoGrafico& entorno): entorno(entorno) {
    std::ifstream fuente(RUTA_INFO);
    fuente >> parser;

    std::string raiz;
    parser["raiz"].get_to(raiz);
    for (auto& raza: parser["razas"].items()) {
        auto clases = raza.value()["variantes"];
        if (raza.value().count("copiar") > 0) {
            std::string copiar_a;
            raza.value()["copiar"].get_to(copiar_a);
            clases = parser["razas"][copiar_a.c_str()]["variantes"];
        }
        for (auto& clase: clases.items()) {
            imagenes_t setDeImagenes(aparienciaImagenesBase);
            for (auto& campo :setDeImagenes) {
                for (auto& valor: clase.value()[campo.first]) {
                    std::string ruta_completa = raiz + campo.first + DELIMITADOR_RUTA + valor.get<std::string>();
                    // buffer.push_back(Imagen(entorno, ruta_completa));
                    // setDeImagenes[campo.first].push_back(&buffer.back());
                    setDeImagenes[campo.first].push_back(new Imagen(entorno, ruta_completa));
                }
            }
            imagenes[raza.key() + DELIMITADOR + clase.key()] = std::move(setDeImagenes);
        }
    }

    for (auto& animacion: parser["animacion"].items()) {
        int columnas = animacion.value()["Columnas"];
        this->columnas[animacion.key()] = columnas;
        for (auto& direccion: animacion.value()["Direcciones"].items()) {
            int direccion_v = direccion.value();
            for (auto& estado: animacion.value()["Estados"].items()) {
                std::string llave = estado.key() + DELIMITADOR + direccion.key();
                std::transform(llave.begin(), llave.end(), llave.begin(), ::tolower);
                std::string llave_quieto = std::string(QUIETO) + DELIMITADOR + llave;
                std::transform(llave_quieto.begin(), llave_quieto.end(), llave_quieto.begin(), ::tolower);    
            
                int cantidad = estado.value()["cantidad"];
                std::vector<int> filas = estado.value()["fila"].get<std::vector<int>>();
                if ((int)filas.size() < direccion_v) continue;
                int fila = 10; // filas.at(direccion_v);

                animaciones[animacion.key()][llave_quieto].push_back(fila * columnas);

                for (int i = 0; i < cantidad; ++i) {
                    int guid = fila * columnas + i;
                    animaciones[animacion.key()][llave].push_back(guid);
                }
            }
        }
    }
}

int EntidadParser::getGuid(std::string& tipo, std::string& accion, 
                            std::string& direccion, int columna, bool quieto) {
    std::string id = accion + DELIMITADOR + direccion;
    if (quieto) {
        id = std::string(QUIETO) + DELIMITADOR + id;
        columna = 0;
    }
    std::transform(id.begin(), id.end(), id.begin(), ::tolower);
    return animaciones[tipo][id][columna];
}

int EntidadParser::getAnimacionCantidadTipo(std::string& tipo) {
    return columnas[tipo];
}

int EntidadParser::getAnimacionCantidad(std::string& tipo, std::string& accion, 
                                                    std::string& direccion) {
    std::string id = accion + DELIMITADOR + direccion;
    std::transform(id.begin(), id.end(), id.begin(), ::tolower);
    return animaciones[tipo][id].size();
}

imagenes_t EntidadParser::getImagenes(std::string& raza, std::string& clase) {
    std::string index(raza + DELIMITADOR + clase);
    return imagenes[index];
}

int EntidadParser::getAncho() {
    return parser["animacion"][BASE]["Ancho"];
}

int EntidadParser::getAlto() {
    return parser["animacion"][BASE]["Alto"];
}
