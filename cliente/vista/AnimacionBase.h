#ifndef ANIMACIONBASE_H
#define ANIMACIONBASE_H
#include <SDL2/SDL_rect.h>
#include <string>
#define REPETIR_INDEFINIDAMENTE 0

class AnimacionParser;
class Animacion;
class AnimacionBase {
public:
    AnimacionBase() {};
    AnimacionBase(AnimacionParser& parser);
    virtual ~AnimacionBase() = default;
    AnimacionParser* getParser();
    virtual void getMascara(Animacion& animacion, std::string& direccion_anterior, 
            SDL_Rect& mascara, int delta_x, int delta_y);
    virtual int getColumnas(std::string& accion, std::string& direccion);
    virtual int getTiempoPorCiclo();
    virtual int getTiempoPorCuadro();

private:
    void reiniciar();
    AnimacionParser* parser;

protected:
    virtual std::string getDireccion(int delta_x, int delta_y);
    virtual bool estaQuieto(int delta_x, int delta_y);
    int tiempo_por_ciclo = REPETIR_INDEFINIDAMENTE;
    int tiempo_por_cuadro = 80;
};

#endif
