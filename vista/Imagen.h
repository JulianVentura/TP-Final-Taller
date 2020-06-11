#ifndef IMAGEN_H
#define IMAGEN_H

#include "EntornoGrafico.h"
#include "Ventana.h"
#include <string>

class Imagen: public IRendereable, public IDimensionable {
public:
    Imagen() = default;
    Imagen(EntornoGrafico& entorno, const std::string& path);
    Imagen(EntornoGrafico& entorno, const std::string& path, SDL_Color* color);
    void render() override;
    void setPosicion(int x, int y);
    virtual int getAncho() override;
    virtual int getAlto() override;
    void setAncho(int ancho);
    void setAlto(int alto);
    void setMascara(int x, int y, int ancho, int alto);

    // Debería estar en una clase más abstracta
    void centrarRelativoA(IDimensionable& contenedor);
private:
    void iniciarDimension(SDL_Texture* texture);
    EntornoGrafico* entorno;
    SDL_Texture* textura;
    SDL_Rect mascara = {};
    SDL_Rect render_mascara = {};
};

#endif
