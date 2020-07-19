#include "EntidadParser.h"
#include <vector>
#include <utility>
#include <map>
#include <cctype>
#include <algorithm>
#include <fstream>
#include "PersonajeParser.h"
#include "../Sprite.h"

#define RUTA_INFO "assets/imagenes.json"

using json = nlohmann::json;


void EntidadParser::aMinuscula(std::string& cadena) {
    std::transform(cadena.begin(), cadena.end(), cadena.begin(), ::tolower);
}

void EntidadParser::parsearRazas() {
    // todo: levantar ancho, alto, base
    for (auto& raza: parser["razas"].items()) {
        auto clases = raza.value()["variantes"];
        std::string raza_s = raza.key();
        
        if (raza.value().count("copiar")) {
            raza.value()["copiar"].get_to(raza_s);
            clases = parser["razas"][raza_s]["variantes"];
        }
        imagenes_t setDeImagenesBase;
        for (auto& campos: clases[ENTIDADPARSER_BASE]["estructura"].items()) {
            for (auto& imagen: campos.value()) {
                parsearImagen(setDeImagenesBase, campos.key(), imagen);
            }
        }
        std::string clase_raza;
        for (auto& clase: clases.items()) {
            if (clase.key() == ENTIDADPARSER_BASE) continue;
            clase_raza = raza.key() + ENTIDADPARSER_DELIMITADOR + clase.key() ;
            entidades.insert({ clase_raza, PersonajeParser() });
            entidades[clase_raza].parsear(entorno, parser, raiz, raza_s, 
                                            clase.key(), setDeImagenesBase);
        }
    }
}

void EntidadParser::parsearImagen(imagenes_t& setDeImagenes, 
                        const std::string& tipo, const std::string& variante) {
    std::string ruta_completa = raiz + tipo + ENTIDADPARSER_DELIMITADOR_RUTA + variante;
    bufferImagenes.push_back(new Imagen(entorno, ruta_completa));
    setDeImagenes[tipo].push_back(bufferImagenes.back());
}

void EntidadParser::parsearNPCs() {
    for (auto& npc: parser[ENTIDADPARSER_NPC].items()) {
        imagenes_t setDeImagenes;
        std::string id = npc.key();
        aMinuscula(id);
        entidades.insert({ id, PersonajeParser() });
        entidades[id].parsear(entorno, parser, raiz, npc.key(), 
                                                                setDeImagenes);
    }
}

void EntidadParser::parsearAnimaciones() {
    for (auto& animacion: parser["animacion"].items()) {
        AnimacionParser a_parser(parser, animacion.key());
        animaciones.insert({ animacion.key(), a_parser});
    }
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
    for (auto& entidad: entidades) {
        entidad.second.setAnimacion(animaciones);
    }
}

EntidadParser::~EntidadParser() {
    for (auto& imagen: bufferImagenes) {
        delete imagen;
    }
}

std::string EntidadParser::idReal(DatosApariencia& apariencia) {
    std::string index = "";
    std::string id = apariencia.raza + ENTIDADPARSER_DELIMITADOR + apariencia.clase;
    aMinuscula(id);
    if (entidades.count(id)) index = id;
    id = apariencia.tipo;
    aMinuscula(id);
    if (entidades.count(id)) index = id; 
    id = apariencia.estado;
    aMinuscula(id);
    if (entidades.count(id)) index = id;
    return index;
}
CapaSprite* EntidadParser::getCapaSprite(DatosApariencia& apariencia) {
    std::string index = idReal(apariencia);
    if (index.size() > 0)
        return entidades.at(index).getCapaSprite();
    return nullptr;
}

const std::vector<Imagen*>& EntidadParser::getImagenes(
                                                DatosApariencia& apariencia) {
    std::string id = apariencia.tipo;
    aMinuscula(id);
    return getImagenes(id, ENTIDADPARSER_NPC);
}

const std::vector<Imagen*>& EntidadParser::getImagenes(
                        DatosApariencia& apariencia, const std::string& parte) {
    std::string id = apariencia.tipo;
    aMinuscula(id);
    if (id.size())
        return getImagenes(id, parte);
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
    return entidades.at(index).getImagenes(parte);
} 

const std::vector<Imagen*>& EntidadParser::getImagenes(const std::string& raza, 
                        const std::string& clase, const std::string& parte) {
    std::string index(raza + ENTIDADPARSER_DELIMITADOR + clase);
    aMinuscula(index);
    return entidades.at(index).getImagenes(parte);
}

int EntidadParser::getAnchoReal(DatosApariencia& apariencia) {
    std::string id = idReal(apariencia);
    if (!entidades.count(id)) return 0;
    return entidades.at(id).getAncho();
}

int EntidadParser::getAltoReal(DatosApariencia& apariencia) {
    std::string id = idReal(apariencia);
    if (!entidades.count(id)) return 0;
    return entidades.at(id).getAlto();
}
bool EntidadParser::esObstruible(DatosApariencia& apariencia) {
    std::string id = idReal(apariencia);
    if (entidades.count(id)) return entidades[id].esObstruible();
    return true;
}
    
// int EntidadParser::getAncho(std::string& raza, std::string& tipo) {
//     float factor = 1.0f;
//     aMinuscula(raza);
//     if (parser["razas"].count(raza)) 
//         parser["razas"][raza]["escala"].get_to(factor);
//     return getAncho(tipo) * factor;
// }

// int EntidadParser::getAlto(std::string& raza, std::string& tipo) {
//     float factor = 1.0f;
//     aMinuscula(raza);
//     if (parser["razas"].count(raza)) 
//         parser["razas"][raza]["escala"].get_to(factor);
//     return getAlto(tipo) * factor;
// }

int EntidadParser::getAncho(std::string& tipo) {
    std::string local_tipo = ENTIDADPARSER_BASE;
    aMinuscula(tipo);
    if (animaciones.count(tipo)) local_tipo = tipo;
    return (int) parser["animacion"][local_tipo]["Ancho"];
}

int EntidadParser::getAlto(std::string& tipo) {
    std::string local_tipo = ENTIDADPARSER_BASE;
    aMinuscula(tipo);
    if (animaciones.count(tipo)) local_tipo = tipo;
    return parser["animacion"][local_tipo]["Alto"];
}

int EntidadParser::getAncho(DatosApariencia& apariencia) {
    return getAncho(apariencia.tipo);
}
int EntidadParser::getAlto(DatosApariencia& apariencia) {
    return getAlto(apariencia.tipo);
}
