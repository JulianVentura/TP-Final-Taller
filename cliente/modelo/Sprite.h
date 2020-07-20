#ifndef SPRITE_H
#define SPRITE_H
#include <vector>
#include <unordered_map>
#include <string>

#include "../vista/Imagen.h"
#include "parsers/DatosApariencia.h"
class EntidadParser;
class AnimacionBase;
class CapaSprite {
public:
    explicit CapaSprite(imagenes_t& setDeImagenes);
    virtual void render(EntidadParser& parser, std::unordered_map<std::string, 
        Imagen*>& equipables, int x, int y, int ancho, int alto, DatosApariencia& apariencia);
    void setMascara(SDL_Rect& mascara);
    void setAnimacion(AnimacionBase* animacion);
    AnimacionBase* getInfoAnimacion();
    virtual ~CapaSprite() {}

protected:
    void renderImagen(Imagen* imagen, int x, int y, int ancho, int alto);
    SDL_Rect mascara;
    imagenes_t& setDeImagenes;
    AnimacionBase* animacion;
};

class CapaSpritePersonaje: public CapaSprite {
public:
    explicit CapaSpritePersonaje(imagenes_t& setDeImagenes);
    virtual void render(EntidadParser& parser, std::unordered_map<std::string, Imagen*>& 
        equipables, int x, int y, int ancho, int alto, DatosApariencia& apariencia) override;
private:
    static const std::vector<std::string> ordenDeImagenes;
};

class Sprite {
public:
    void render(EntidadParser& parser, std::unordered_map<std::string, Imagen*>& equipables);
    void actualizar(EntidadParser& parser, DatosApariencia& apariencia);
    void setMascara(SDL_Rect& mascara);
    void setDimension(int x, int y, int ancho, int alto);
    AnimacionBase* getInfoAnimacion();
    ~Sprite();
protected:
    void renderImagen(Imagen* imagen);
    DatosApariencia apariencia;
    CapaSprite* capa = nullptr;
    SDL_Rect mascara;
    int x; 
    int y;
    int ancho;
    int alto;
};
#endif
