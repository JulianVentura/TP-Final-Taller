#ifndef ANIMACIONBASE_H
#define ANIMACIONBASE_H
#include <SDL2/SDL_rect.h>
#include <string>
#define REPETIR_INDEFINIDAMENTE 0

class AnimacionParser;
class AnimacionBase {
public:
    AnimacionBase() {};
    AnimacionBase(AnimacionParser& parser);
    virtual ~AnimacionBase() = default;
    virtual void getMascara(SDL_Rect& mascara, int columna, int delta_x, int delta_y);
    virtual int getColumnas();
    virtual int getTiempoPorCiclo();
    virtual int getTiempoPorCuadro();

private:
    void reiniciar();
    AnimacionParser* parser;

protected:
    std::string accion;
    std::string direccion;
    int columna = 0;
    int tiempo_por_ciclo = REPETIR_INDEFINIDAMENTE;
    int tiempo_por_cuadro = 80;
    unsigned int ultimo_delta_t = 0;
    bool esta_quieto;
};

#endif
