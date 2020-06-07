#include "Imagen.h"

Imagen::Imagen(EntornoGrafico& entorno, const std::string& path, 
                                                        SDL_Color* key_color) {
    src_clip = {};
    render_clip = {};
    texture = entorno.loadImagen(path, &src_clip, key_color);
    render_clip = src_clip;
    entorno.addRenderable(this);
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
    renderer->renderTexture(texture, src_clip, render_clip);
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