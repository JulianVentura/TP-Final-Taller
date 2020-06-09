#include "Imagen.h"

Imagen::Imagen(EntornoGrafico& entorno, const std::string& path, 
                                                            SDL_Color* color) {
    entorno.addRenderable(this);
    texture = entorno.loadImagen(path, color);
    iniciarDimension(texture);
}

Imagen::Imagen(EntornoGrafico& entorno, const std::string& path) {
    entorno.addRenderable(this);
    texture = entorno.loadImagen(path);
    iniciarDimension(texture);
}

void Imagen::iniciarDimension(SDL_Texture* texture) {
    SDL_QueryTexture(texture, NULL, NULL, &src_clip.w, &src_clip.h);
    render_clip = src_clip;
}

void Imagen::setClip(int x, int y, int ancho, int alto) {
    src_clip.x = x;
    src_clip.x = y;
    src_clip.w = ancho;
    src_clip.h = alto;
    render_clip.w = ancho;
    render_clip.h = alto;
}

void Imagen::setPosicion(int x, int y) {
    render_clip.x = x;
    render_clip.y = y;
}

void Imagen::render() {
    renderer->renderTextura(texture, src_clip, render_clip);
}

int Imagen::getAncho() {
    return render_clip.w;
}

int Imagen::getAlto() {
    return render_clip.h;
}

void Imagen::setAncho(int ancho) {
    render_clip.w = ancho;
}

void Imagen::setAlto(int alto) {
    render_clip.h = alto;
}
