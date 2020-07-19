#include "Sprite.h"
#include "parsers/EntidadParser.h"
#include "../vista/Animacion.h"

const std::vector<std::string> CapaSpritePersonaje::ordenDeImagenes = {
    "cuerpo",
    "ojos",
    "cicatrices",
    "nariz",
    "orejas",
    "facial",
    "pies",
    "piernas",
    "torso",
    "cinto",
    "pelo",
    "cabeza",
    "arma",
    "escudo"
};

void CapaSprite::setAnimacion(AnimacionBase* animacion) {
    this->animacion = animacion;
}

AnimacionBase* CapaSprite::getInfoAnimacion() {
    return animacion;
}

void CapaSprite::renderImagen(Imagen* imagen, int x, int y, int ancho, int alto) {
    imagen->setMascara(mascara);
    imagen->setAncho(ancho);
    imagen->setAlto(alto);
    imagen->setPosicion(x, y);
    imagen->render();
}

void CapaSpritePersonaje::render(EntidadParser& parser, std::unordered_map<
        std::string, Imagen*>& equipables, int x, int y, int ancho, int alto, DatosApariencia& apariencia) {
    for (auto& parte: ordenDeImagenes) {
        Imagen * imagen_mostrar = nullptr;
        if (equipables.count(parte)) {
            imagen_mostrar = equipables[parte];
            equipables.erase(parte);
            renderImagen(imagen_mostrar, x, y, ancho, alto);
            continue;
        }
        for (auto& imagen: setDeImagenes[parte]) {
            renderImagen(imagen, x, y, ancho, alto);
        }

    }
    for (auto& equipable: equipables) 
        renderImagen(equipable.second, x, y, ancho, alto);
}


void CapaSprite::render(EntidadParser& parser, std::unordered_map<std::string, 
                    Imagen*>& equipables, int x, int y, int ancho, int alto, DatosApariencia& apariencia) {
    for (auto& setDeImagen: setDeImagenes) {
        for (auto& imagen: setDeImagen.second)
            renderImagen(imagen, x, y, ancho, alto);
    }
}

CapaSprite::CapaSprite(imagenes_t& setDeImagenes): 
    setDeImagenes(setDeImagenes) {}
CapaSpritePersonaje::CapaSpritePersonaje(imagenes_t& setDeImagenes): 
    CapaSprite(setDeImagenes) {}

void CapaSprite::setMascara(SDL_Rect& mascara) {
    this->mascara = mascara;
}

void Sprite::render(EntidadParser& parser, std::unordered_map<std::string, Imagen*>& equipables) {
    if (!capa) return;
    capa->render(parser, equipables, x, y, ancho, alto, apariencia);
}

void Sprite::setDimension(int x, int y, int ancho, int alto) {
    this->x = x;
    this->y = y;
    this->ancho = ancho;
    this->alto = alto;
}

void Sprite::setMascara(SDL_Rect& mascara) {
    if (!capa) return;
    capa->setMascara(mascara);
}

void Sprite::actualizar(EntidadParser& parser, DatosApariencia& apariencia) {
    this->apariencia = apariencia;
    capa = parser.getCapaSprite(apariencia);
}

AnimacionBase* Sprite::getInfoAnimacion() {
    if (!capa) return nullptr;
    return capa->getInfoAnimacion();
}

Sprite::~Sprite() {}
