#include "Imagen.h"

Imagen::Imagen(EntornoGrafico& entorno, const std::string& path, 
                                                            SDL_Color* color) {
    entorno.agregarRendereable(this);
    textura = entorno.cargarImagen(path, color);
    iniciarDimension(textura);
}

Imagen::Imagen(EntornoGrafico& entorno, const std::string& path) {
    entorno.agregarRendereable(this);
    textura = entorno.cargarImagen(path);
    iniciarDimension(textura);
}

void Imagen::iniciarDimension(SDL_Texture* textura) {
    SDL_QueryTexture(textura, NULL, NULL, &mascara.w, &mascara.h);
    render_mascara = mascara;
}

void Imagen::setMascara(int x, int y, int ancho, int alto) {
    mascara.x = x;
    mascara.y = y;
    mascara.w = ancho;
    mascara.h = alto;
    render_mascara.w = ancho;
    render_mascara.h = alto;
}

void Imagen::setPosicion(int x, int y) {
    render_mascara.x = x;
    render_mascara.y = y;
}

void Imagen::centrarRelativoA(IDimensionable& contenedor) {
    // Debería estar en una clase más abstracta
    int desplazamientoX = contenedor.getAncho() / 2 - this->getAncho() / 2;
    int desplazamientoY = contenedor.getAlto() / 2 - this->getAlto() / 2;
    this->setPosicion(desplazamientoX, desplazamientoY);
}

void Imagen::render() {
    renderer->renderTextura(textura, mascara, render_mascara);
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
