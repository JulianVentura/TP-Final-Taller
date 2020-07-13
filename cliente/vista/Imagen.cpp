#include "Imagen.h"

Imagen::Imagen(EntornoGrafico& entorno, const std::string& ruta, 
                                                            SDL_Color* color) {
    entorno.agregarRendereable(this);
    if (color)
        textura = entorno.cargarImagen(ruta, color);
    else
        textura = entorno.cargarImagen(ruta);
    iniciarDimension(textura);
}

Imagen::Imagen(EntornoGrafico& entorno, const std::string& ruta) {
    entorno.agregarRendereable(this);
    textura = entorno.cargarImagen(ruta);
    iniciarDimension(textura);
}

void Imagen::iniciarDimension(SDL_Texture* textura) {
    SDL_QueryTexture(textura, NULL, NULL, &mascara.w, &mascara.h);
    render_mascara = mascara;
}

void Imagen::setMascara(int x, int y, int ancho, int alto) {
    SDL_Rect mascara = { x, y, ancho, alto };
    setMascara(mascara);
}
void Imagen::setMascara(SDL_Rect& mascara) {
    this->mascara = mascara;
    render_mascara.w = mascara.w;
    render_mascara.h = mascara.h;
}

void Imagen::setPosicion(int x, int y) {
    render_mascara.x = x;
    render_mascara.y = y;
}

void Imagen::render() {
    renderer->renderTextura(textura, mascara, render_mascara);
}

void Imagen::renderExpandido() {
    renderer->renderTexturaExpandida(textura, mascara);
}

int Imagen::getAncho() {
    return render_mascara.w;
}

int Imagen::getAlto() {
    return render_mascara.h;
}

void Imagen::setAncho(int ancho) {
    render_mascara.w = ancho;
}

void Imagen::setAlto(int alto) {
    render_mascara.h = alto;
}
