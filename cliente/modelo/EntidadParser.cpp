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
        if (raza.value().count("copiar")) {
            std::string copiar_a;
            raza.value()["copiar"].get_to(copiar_a);
            clases = parser["razas"][copiar_a.c_str()]["variantes"];
        }

        imagenes_t setDeImagenesBase(aparienciaImagenesBase);
        for (auto& campo: setDeImagenesBase) {
            for (auto& valor: clases[BASE][campo.first]) {
                if (valor == "") continue;
                parsearImagen(setDeImagenesBase, campo.first, 
                                                valor.get<std::string>());
            }
        }
        std::string clase_raza = raza.key() + DELIMITADOR + std::string(BASE);
        aMinuscula(clase_raza);
        imagenes[clase_raza] = std::move(setDeImagenesBase);
        
        for (auto& clase: clases.items()) {
            if (raza.key() == BASE) continue;
            imagenes_t setDeImagenes(imagenes[clase_raza]);
            for (auto& campo: setDeImagenes) {
                for (auto& valor: clase.value()[campo.first]) {
                    if (valor == "") continue;
                    parsearImagen(setDeImagenes, campo.first, 
                                                    valor.get<std::string>());
                }
            }
            std::string clase_raza = raza.key() + DELIMITADOR + clase.key();
            aMinuscula(clase_raza);
            imagenes[clase_raza] = std::move(setDeImagenes);
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
        // printf("%s\n", animacion.key().c_str());

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
    // for (auto& animacion: animaciones) {
    //     for (auto& variante: animacion.second) {
    //         // printf("%s %s\n", animacion.first.c_str(), variante.first.c_str());
    //         std::string tipo = animacion.first;
    //         std::string accion = "Caminar";
    //         std::string direccion = "Arriba";
    //         // printf("%d %d\n", getAnimacionCantidadTipo(tipo) , getAnimacionCantidad(tipo, accion, direccion));
    //     }
    // }
    
    // exit(0);
}

EntidadParser::EntidadParser(EntornoGrafico& entorno): entorno(entorno) {
    std::ifstream fuente(RUTA_INFO);
    fuente >> parser;
    parser["raiz"].get_to(raiz);
    parsearRazas();
    parsearNPCs();
    parsearAnimaciones();
}

EntidadParser::~EntidadParser() {
    for (auto& setImagen: imagenes) {
        for (auto& parte: setImagen.second) {
            for (auto& imagen: parte.second) {
                delete imagen;
            }
        }
    }
}

int EntidadParser::getGuid(std::string& tipo, std::string& accion, 
                            std::string& direccion, int columna, bool quieto) {

    std::string local_tipo = BASE;
    aMinuscula(tipo);
    if (animaciones.count(tipo)) local_tipo = tipo;
    std::string id = accion + DELIMITADOR + direccion;
    aMinuscula(id);
    if (quieto) return animaciones[local_tipo][id][0];
    return animaciones[local_tipo][id][columna % getAnimacionCantidad(
                                             local_tipo, accion, direccion)];
}

int EntidadParser::getAnimacionCantidadTipo(std::string& tipo) {
    std::string local_tipo = BASE;
    aMinuscula(tipo);
    if (columnas.count(tipo)) local_tipo = tipo;
    return columnas[local_tipo];
}

int EntidadParser::getAnimacionCantidad(std::string& tipo, std::string& accion, 
                                                    std::string& direccion) {
    std::string local_tipo = BASE;
    if (animaciones.count(tipo)) local_tipo = tipo;
    std::string id = accion + DELIMITADOR + direccion;
    aMinuscula(id);
    return animaciones[local_tipo][id].size();
}

imagenes_t EntidadParser::getImagenes(std::string& tipo) {
    printf("tipo get imagenes: %s\n", tipo.c_str());
    aMinuscula(tipo);
    if (!imagenes.count(tipo)) return aparienciaImagenesBase;
    return imagenes[tipo];
}

imagenes_t EntidadParser::getImagenes(std::string& raza, std::string& clase) {
    std::string index(raza + DELIMITADOR + clase);
    aMinuscula(index);
    printf("tipo get imagenes: %s\n", index.c_str());
    if (!imagenes.count(index)) return aparienciaImagenesBase;
    return imagenes[index];
}

int EntidadParser::getAncho(std::string& raza, std::string& tipo) {
    float factor = 1.0f;
    aMinuscula(raza);
    if (parser["razas"].count(raza)) 
        parser["razas"][raza]["escala"].get_to(factor);
    return getAncho(tipo) * factor;
}

int EntidadParser::getAlto(std::string& raza, std::string& tipo) {
    float factor = 1.0f;
    aMinuscula(raza);
    if (parser["razas"].count(raza)) 
        parser["razas"][raza]["escala"].get_to(factor);
    return getAlto(tipo) * factor;
}

int EntidadParser::getAncho(std::string& tipo) {
    std::string local_tipo = BASE;
    aMinuscula(tipo);
    if (animaciones.count(tipo)) local_tipo = tipo;
    return (int) parser["animacion"][local_tipo]["Ancho"];
}

int EntidadParser::getAlto(std::string& tipo) {
    std::string local_tipo = BASE;
    aMinuscula(tipo);
    if (animaciones.count(tipo)) local_tipo = tipo;
    return parser["animacion"][local_tipo]["Alto"];
}
