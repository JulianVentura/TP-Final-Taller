#include "PersonajeParser.h"
#include "EntidadParser.h"
#include "../Sprite.h"
#include "../../vista/Colores.h"

#include "../../vista/AnimacionCuatroDirecciones.h"
#include "../../vista/AnimacionOchoDirecciones.h"
#include "../../vista/AnimacionEstatica.h"
#include <SDL2/SDL_pixels.h>

#define CUARTETO 4
#define OCTETO 8

CapaSprite* PersonajeParser::getCapaSprite() { return capa; }

AnimacionBase* PersonajeParser::getAnimacion() { return animacion; }

const std::vector<Imagen*>& PersonajeParser::getImagenes(const std::string& parte) {
    return setDeImagenes[parte];
}

int PersonajeParser::getAncho() { return ancho; }
int PersonajeParser::getAlto() { return alto; }

void PersonajeParser::setAnimacion(std::unordered_map<std::string, AnimacionParser>& animaciones) {
    if (animaciones.count(animacion_s)) {
        AnimacionParser& animacion = animaciones.at(animacion_s);
        if (animacion.getDirecciones() == 0) {
            this->animacion = new AnimacionBase(animacion);
        } else if (animacion.getDirecciones() == CUARTETO) {
            this->animacion = new AnimacionCuatroDirecciones(animacion);
        } else if (animacion.getDirecciones() == OCTETO) {
            this->animacion = new AnimacionOchoDirecciones(animacion);
        }
    } else {
        this->animacion = new AnimacionEstatica(ancho, alto);
    }
    capa->setAnimacion(this->animacion);
}
float PersonajeParser::getFactor() { return factor; }

bool PersonajeParser::esObstruible() { return es_obstruible; }

void PersonajeParser::parsear(EntornoGrafico& entorno, nlohmann::json& parser, 
        std::string& raiz, const std::string& raza, const std::string& clase, 
                                        const imagenes_t setDeImagenesBase) {
    if (clase == ENTIDADPARSER_BASE) return;
    std::string color_fondo;
    setDeImagenes = setDeImagenesBase;
    for (auto& valor: parser["razas"][raza]["variantes"][clase]["estructura"].items()) {        
        if (valor.value().size() && setDeImagenes[valor.key()].size())
            setDeImagenes[valor.key()].clear();
        for (auto& parte: valor.value())
            parsearImagen(entorno, raiz, setDeImagenes, valor.key(), parte, color_fondo);
    }
    capa = new CapaSpritePersonaje(setDeImagenes);
    id = raza + ENTIDADPARSER_DELIMITADOR + clase;
    animacion_s = ENTIDADPARSER_BASE;
    factor = parser["razas"][raza]["escala"];
    ancho = parser["ancho"].get<int>() * factor;
    alto = parser["alto"].get<int>() * factor;
    EntidadParser::aMinuscula(id);
}

void PersonajeParser::parsear(EntornoGrafico& entorno, nlohmann::json& parser, 
            std::string& raiz, const std::string& tipo, const imagenes_t 
                                                            setDeImagenesBase) {
    std::string color_fondo;
    if (parser[ENTIDADPARSER_NPC][tipo].count("imagen")) {
        if (parser[ENTIDADPARSER_NPC][tipo].count("key_color")) 
            color_fondo = parser[ENTIDADPARSER_NPC][tipo]["key_color"];
        for (auto& imagen: parser[ENTIDADPARSER_NPC][tipo]["imagen"])
            parsearImagen(entorno, raiz, setDeImagenes, ENTIDADPARSER_NPC, imagen, color_fondo);
        capa = new CapaSprite(setDeImagenes);
        if (parser[ENTIDADPARSER_NPC][tipo].count("animacion") && 
            parser[ENTIDADPARSER_NPC][tipo]["animacion"].size())
            animacion_s = parser[ENTIDADPARSER_NPC][tipo]["animacion"];
    } else if (parser[ENTIDADPARSER_NPC][tipo].count("estructura")) {
        for (auto& valor: parser[ENTIDADPARSER_NPC][tipo]["estructura"].items()) {
            for (auto& parte: valor.value())
                parsearImagen(entorno, raiz, setDeImagenes, valor.key(), parte, color_fondo);
        }
        capa = new CapaSpritePersonaje(setDeImagenes);
        animacion_s = ENTIDADPARSER_BASE;
    }
    ancho = parser[ENTIDADPARSER_NPC][tipo]["ancho"];
    alto = parser[ENTIDADPARSER_NPC][tipo]["alto"];
    if (parser[ENTIDADPARSER_NPC][tipo].count("es_obstruible"))
        es_obstruible = parser[ENTIDADPARSER_NPC][tipo]["es_obstruible"];
    id = tipo;
    EntidadParser::aMinuscula(id);
}

void PersonajeParser::parsearImagen(EntornoGrafico& entorno, std::string& raiz, 
        imagenes_t& setDeImagenes, const std::string& tipo,
                        const std::string& variante, std::string& color_fondo) {
    std::string ruta_completa = raiz + tipo + ENTIDADPARSER_DELIMITADOR_RUTA + variante;
    SDL_Color* color_ptr = nullptr;
    SDL_Color color;
    if (color_fondo.size()) {
        color = Colores::colorDesdeHexa(color_fondo);
        color_ptr = &color;
    }
    bufferImagenes.push_back(new Imagen(entorno, ruta_completa, color_ptr));
    setDeImagenes[tipo].push_back(bufferImagenes.back());
}

PersonajeParser::~PersonajeParser() {
    for (auto& imagen: bufferImagenes) {
        delete imagen;
    }
    delete capa;
    delete animacion;
}
