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

static void aMinuscula(std::string& cadena) {
    std::transform(cadena.begin(), cadena.end(), cadena.begin(), ::tolower);
}

void EntidadParser::parsearRazas() {
    for (auto& raza: parser["razas"].items()) {
        auto clases = raza.value()["variantes"];
        if (raza.value().count("copiar") > 0) {
            std::string copiar_a;
            raza.value()["copiar"].get_to(copiar_a);
            clases = parser["razas"][copiar_a.c_str()]["variantes"];
        }

        imagenes_t setDeImagenesBase(aparienciaImagenesBase);
        for (auto& campo: setDeImagenesBase) {
            for (auto& valor: clases[BASE][campo.first]) {
                if (valor == "") continue;
                // parsearImagen(setDeImagenesBase, campo.first, 
                                                // valor.get<std::string>());
            }
        }
        std::string id_clase_raza = raza.key() + DELIMITADOR + std::string(BASE);
        aMinuscula(id_clase_raza);
        imagenes[id_clase_raza] = std::move(setDeImagenesBase);
        
        for (auto& clase: clases.items()) {
            if (raza.key() == BASE) continue;
            imagenes_t setDeImagenes(imagenes[id_clase_raza]);
            for (auto& campo: setDeImagenes) {
                for (auto& valor: clase.value()[campo.first]) {
                    if (valor == "") continue;
                    parsearImagen(setDeImagenes, campo.first, 
                                                    valor.get<std::string>());
                }
            }
            std::string id_clase_raza = raza.key() + DELIMITADOR + clase.key();
            aMinuscula(id_clase_raza);
            imagenes[id_clase_raza] = std::move(setDeImagenes);
        }
    }
}

void EntidadParser::parsearImagen(imagenes_t& setDeImagenes, 
                        const std::string& tipo, const std::string& variante) {
    std::string ruta_completa = raiz + tipo + DELIMITADOR_RUTA + variante;
    setDeImagenes[tipo].push_back(new Imagen(entorno, ruta_completa));
}

void EntidadParser::parsearNPCs() {
    for (auto& npc: parser["npc"].items()) {
        imagenes_t setDeImagenes(aparienciaImagenesBase);
        for (auto& campo: setDeImagenes) {
            for (auto& valor: npc.value()[campo.first]) {
                if (valor == "") continue;
                parsearImagen(setDeImagenes, campo.first, valor.get<std::string>());
            }
        }
        std::string id_npc = npc.key();
        aMinuscula(id_npc);
        imagenes[id_npc] = std::move(setDeImagenes);
    }    
}

void EntidadParser::parsearAnimaciones() {
    for (auto& animacion: parser["animacion"].items()) {
        int columnas = animacion.value()["Columnas"];
        this->columnas[animacion.key()] = columnas;
        for (auto& direccion: animacion.value()["Direcciones"].items()) {
            int direccion_v = direccion.value();
            for (auto& estado: animacion.value()["Estados"].items()) {
                std::string llave = estado.key() + DELIMITADOR + direccion.key();
                aMinuscula(llave);
                std::string llave_quieto = llave + DELIMITADOR + std::string(QUIETO);
                aMinuscula(llave_quieto);
                int cantidad = estado.value()["cantidad"];
                std::vector<int> filas = estado.value()["fila"].get<std::vector<int>>();
                if ((int)filas.size() <= direccion_v) continue;
                int fila = filas.at(direccion_v);
                animaciones[animacion.key()][llave_quieto].push_back(fila * columnas);
                for (int i = 0; i < cantidad; ++i) {
                    int guid = fila * columnas + i;
                    animaciones[animacion.key()][llave].push_back(guid);
                }
            }
        }
    }
}

EntidadParser::EntidadParser(EntornoGrafico& entorno): entorno(entorno) {
    std::ifstream fuente(RUTA_INFO);
    fuente >> parser;
    parser["raiz"].get_to(raiz);
    parsearRazas();
    parsearNPCs();
    parsearAnimaciones();
    for (auto& raza: imagenes) {
        for (auto& variante: raza.second) {
            printf("%s %s\n", raza.first.c_str(), variante.first.c_str());
        }
    }
}

EntidadParser::~EntidadParser() {
    for (auto& setImagen: imagenes) {
        for (auto& parte: setImagen.second) {
            for (auto& imagen: parte.second) {
                printf("%s\n", setImagen.first.c_str());
                printf("%s\n", parte.first.c_str());
                delete imagen;
            }
        }
    }
}

int EntidadParser::getGuid(std::string& tipo, std::string& accion, 
                            std::string& direccion, int columna, bool quieto) {
    std::string id = accion + DELIMITADOR + direccion;
    aMinuscula(id);
    if (quieto) return animaciones[tipo][id][0];
    return animaciones[tipo][id][columna % getAnimacionCantidad(tipo, accion, 
                                                            direccion)];
}

int EntidadParser::getAnimacionCantidadTipo(std::string& tipo) {
    aMinuscula(tipo);   
    if (columnas.count(tipo) <= 0) return -1;
    return columnas[tipo];
}

int EntidadParser::getAnimacionCantidad(std::string& tipo, std::string& accion, 
                                                    std::string& direccion) {
    std::string id = accion + DELIMITADOR + direccion;
    aMinuscula(id);
    return animaciones[tipo][id].size();
}

imagenes_t EntidadParser::getImagenes(std::string& tipo) {
    printf("tipo get imagenes: %s\n", tipo.c_str());
    aMinuscula(tipo);
    if (imagenes.count(tipo) <= 0) return aparienciaImagenesBase;
    return imagenes[tipo];
}

imagenes_t EntidadParser::getImagenes(std::string& raza, std::string& clase) {
    std::string index(raza + DELIMITADOR + clase);
    aMinuscula(index);
    printf("tipo get imagenes: %s\n", index.c_str());
    if (imagenes.count(index) <= 0) return aparienciaImagenesBase;
    return imagenes[index];
}

int EntidadParser::getAncho(std::string& raza) {
    float factor = 1.0f;
    aMinuscula(raza);
    if (parser["razas"].count(raza) > 0) 
        parser["razas"][raza]["escala"].get_to(factor);
    return getAlto() * factor;
}

int EntidadParser::getAlto(std::string& raza) {
    float factor = 1.0f;
    aMinuscula(raza);
    if (parser["razas"].count(raza) > 0) 
        parser["razas"][raza]["escala"].get_to(factor);
    return getAlto() * factor;
}

int EntidadParser::getAncho() {
    return (int) parser["animacion"][BASE]["Ancho"];
}

int EntidadParser::getAlto() {
    return parser["animacion"][BASE]["Alto"];
}
