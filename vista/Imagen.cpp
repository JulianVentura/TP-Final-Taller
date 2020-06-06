#include "Imagen.h"

Imagen::Imagen(EntornoGrafico& entorno, std::string& path, SDL_Color* key_color) {
    src_clip = {};
    render_clip = {};
    texture = entorno.loadImagen(path, &src_clip, key_color);
    render_clip = src_clip;
    entorno.addRenderable(this);
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
