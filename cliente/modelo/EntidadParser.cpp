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

const std::vector<Imagen*>& PersonajeParser::getImagenes(const std::string& parte) {
    return setDeImagenes[parte];
}

std::string PersonajeParser::getId() {
    return id;
}

void PersonajeParser::parsear(EntornoGrafico& entorno, nlohmann::json& parser, 
        std::string& raiz, const std::string& raza, const std::string& clase, 
                                        const imagenes_t setDeImagenesBase) {
    if (raza == BASE) return;
    setDeImagenes = setDeImagenesBase;
    for (auto& campo: setDeImagenes) {
        for (auto& valor: parser["razas"][raza]["variantes"][clase][campo.first]) {
            parsearImagen(entorno, raiz, setDeImagenes, campo.first, 
                                                    valor.get<std::string>());
        }
    }
    id = raza + DELIMITADOR + clase;
    aMinuscula(id);
}

void PersonajeParser::parsear(EntornoGrafico& entorno, nlohmann::json& parser, 
            std::string& raiz, const std::string& tipo, const imagenes_t 
                                                            setDeImagenesBase) {
    setDeImagenes = setDeImagenesBase;
    for (auto& campo: setDeImagenes) {
        for (auto& valor: parser["npc"][tipo][campo.first]) {
            parsearImagen(entorno, raiz, setDeImagenes, campo.first, 
                                                    valor.get<std::string>());
        }
    }
    id = tipo;
    aMinuscula(id);
}

void PersonajeParser::parsearImagen(EntornoGrafico& entorno, std::string& raiz, 
        imagenes_t& setDeImagenes, const std::string& tipo,
                                                const std::string& variante) {
    std::string ruta_completa = raiz + tipo + DELIMITADOR_RUTA + variante;
    bufferImagenes.push_back(new Imagen(entorno, ruta_completa));
    setDeImagenes[tipo].push_back(bufferImagenes.back());
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
                parsearImagen(setDeImagenesBase, campo.first, 
                                                valor.get<std::string>());
            }
        }
        std::string clase_raza = raza.key() + DELIMITADOR + std::string(BASE);
        aMinuscula(clase_raza);

        for (auto& clase: clases.items()) {
            clase_raza = raza.key() + DELIMITADOR + clase.key() ;
            personajes.insert({ clase_raza, PersonajeParser() });
            personajes[clase_raza].parsear(entorno, parser, raiz, raza.key(), 
                                            clase.key(), setDeImagenesBase);
        }
    }
}
PersonajeParser::~PersonajeParser() {
    for (auto& imagen: bufferImagenes) {
        delete imagen;
    }
}

void EntidadParser::parsearImagen(imagenes_t& setDeImagenes, 
                        const std::string& tipo, const std::string& variante) {
    std::string ruta_completa = raiz + tipo + DELIMITADOR_RUTA + variante;
    bufferImagenes.push_back(new Imagen(entorno, ruta_completa));
    setDeImagenes[tipo].push_back(bufferImagenes.back());
}

void EntidadParser::parsearNPCs() {
    for (auto& npc: parser["npc"].items()) {
        imagenes_t setDeImagenes(aparienciaImagenesBase);
        std::string id = npc.key();
        aMinuscula(id);
        personajes.insert({ id, PersonajeParser() });
        personajes[id].parsear(entorno, parser, raiz, npc.key(), 
                                                                setDeImagenes);
    }    
}

void EntidadParser::parsearAnimaciones() {
    for (auto& animacion: parser["animacion"].items()) {
        AnimacionParser a_parser(parser, animacion.key());
        animaciones.insert({ animacion.key(), a_parser});
    }
}

Imagen* EquipableParser::getImagen() {
    return imagen;
}

EquipableParser::~EquipableParser() {
    delete imagen;
}
std::string EquipableParser::getReemplazaA() {
    return reemplaza_a;
}

void EquipableParser::parsear(EntornoGrafico& entorno, nlohmann::json& parser, 
                            const std::string& tipo, const std::string& id) {
    std::string imagen_s;
    std::string ruta_base;
    std::string ruta_equipables;
    parser["raiz"].get_to(ruta_base);
    parser["ruta_equipables"].get_to(ruta_equipables);
	parser["equipables"][tipo]["reemplaza"].get_to(reemplaza_a);
	parser["equipables"][tipo]["datos"][id]["imagen"].get_to(imagen_s);
    std::string ruta = ruta_base + ruta_equipables + imagen_s;
	animacion = BASE;
	if (parser["equipables"][tipo]["datos"][id].count("animacion"))
		parser["equipables"][tipo]["datos"][id]["animacion"].get_to(animacion);
    imagen = new Imagen(entorno, ruta);
}

EntidadParser::EntidadParser(EntornoGrafico& entorno): entorno(entorno) {
    std::ifstream fuente(RUTA_INFO);
    fuente >> parser;
    parser["raiz"].get_to(raiz);
    parsearRazas();
    parsearNPCs();
    parsearAnimaciones();
    for (auto& equipable: parser["equipables"].items()) {
        for (auto& tipo: equipable.value()["datos"].items()) {
            equipables.insert({ tipo.key(), EquipableParser() });
            equipables[tipo.key()].parsear(entorno, parser, equipable.key(), 
                                                                tipo.key());
        }
    }
}

EntidadParser::~EntidadParser() {
    for (auto& imagen: bufferImagenes) {
        delete imagen;
    }
}

AnimacionParser::AnimacionParser(nlohmann::json& parser, 
                                                    const std::string& tipo) {
    columnas = parser["animacion"][tipo]["Columnas"];    
    for (auto& direccion: parser["animacion"][tipo]["Direcciones"].items()) {
        int direccion_v = direccion.value();
        for (auto& estado: parser["animacion"][tipo]["Estados"].items()) {
            std::string llave = estado.key() + DELIMITADOR + direccion.key();
            aMinuscula(llave);
            std::string llave_quieto = llave + DELIMITADOR + std::string(QUIETO);
            aMinuscula(llave_quieto);
            int cantidad = estado.value()["cantidad"];
            std::vector<int> filas = estado.value()["fila"].get<std::vector<int>>();
            if ((int)filas.size() <= direccion_v) continue;
            int fila = filas.at(direccion_v);
            animaciones[llave_quieto].push_back(fila * columnas);
            for (int i = 0; i < cantidad; ++i) {
                int guid = fila * columnas + i;
                animaciones[llave].push_back(guid);
            }
        }
    }
}

int AnimacionParser::getGuid(std::string &accion, std::string &direccion, int columna, bool quieto) {
    std::string id = accion + DELIMITADOR + direccion;
    aMinuscula(id);
    if (quieto) return animaciones[id][0];
    return animaciones[id][columna % animaciones[id].size()];
}

int AnimacionParser::getColumnas() {
    return columnas;
}

int AnimacionParser::getColumnas(std::string& accion, std::string& direccion) {
    std::string id = accion + DELIMITADOR + direccion;
    aMinuscula(id);
    return animaciones[id].size();
}

int EntidadParser::getGuid(DatosApariencia& apariencia, std::string& accion, 
                            std::string& direccion, int columna, bool quieto) {
    std::string local_tipo = BASE;
    aMinuscula(apariencia.tipo);
    if (animaciones.count(apariencia.tipo)) local_tipo = apariencia.tipo;
    return animaciones[local_tipo].getGuid(accion, direccion, columna, quieto);
}

int EntidadParser::getAnimacionCantidadTipo(DatosApariencia& apariencia) {
    std::string local_tipo = BASE;
    aMinuscula(apariencia.tipo);
    if (animaciones.count(apariencia.tipo)) local_tipo = apariencia.tipo;
    return animaciones[local_tipo].getColumnas();
}

int EntidadParser::getAnimacionCantidad(DatosApariencia& apariencia, std::string& accion, 
                                                    std::string& direccion) {
    std::string local_tipo = BASE;
    if (animaciones.count(apariencia.tipo)) local_tipo = apariencia.tipo;
    return animaciones[local_tipo].getColumnas(accion, direccion);
}

const std::vector<Imagen*>& EntidadParser::getImagenes(
                        DatosApariencia& apariencia, const std::string& parte) {
    std::string id = apariencia.tipo;
    aMinuscula(id);
    if (id.size())
        return getImagenes(id, parte);
    // TODO: provisorio
        // return getImagenes("Arania", parte);
    // else if (apariencia.estado == "101")
    else
        return getImagenes(apariencia.raza, apariencia.clase, parte);
}
std::unordered_map<std::string, Imagen*> EntidadParser::getEquipables(
                                                DatosApariencia& apariencia) {
    std::unordered_map<std::string, Imagen*> resultado;
    std::vector<std::string> ids {
        apariencia.arma,
        apariencia.armadura,
        apariencia.casco,
        apariencia.escudo
    };
    for (auto& id: ids) {
        if (!equipables.count(id)) continue;
        resultado.insert({equipables[id].getReemplazaA() , 
                                                equipables[id].getImagen()});
    }
    return resultado;
}

const std::vector<Imagen*>& EntidadParser::getImagenes(const std::string& tipo, 
                                                const std::string& parte) {
    std::string index(tipo);
    aMinuscula(index);
    return personajes[index].getImagenes(parte);
} 

const std::vector<Imagen*>& EntidadParser::getImagenes(const std::string& raza, 
                        const std::string& clase, const std::string& parte) {
    std::string index(raza + DELIMITADOR + clase);
    aMinuscula(index);
    return personajes[index].getImagenes(parte);
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

int EntidadParser::getAncho(DatosApariencia& apariencia) {
    return getAncho(apariencia.raza, apariencia.tipo);
}
int EntidadParser::getAlto(DatosApariencia& apariencia) {
    return getAlto(apariencia.raza, apariencia.tipo);
}
