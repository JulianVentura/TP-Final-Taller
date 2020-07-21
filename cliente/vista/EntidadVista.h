#ifndef ENTIDADVISTA_H
#define ENTIDADVISTA_H

#include <string>
#include "AnimacionCuatroDirecciones.h"
#include "IObstruible.h"
#include "Imagen.h"
#include "../modelo/parsers/EntidadParser.h"
#include "../modelo/Sprite.h"

class EntidadVista: public IObstruible {
public:
    EntidadVista(EntornoGrafico& entorno, IPosicionable* modelo, 
                                                        EntidadParser& parser);
    EntidadVista(EntornoGrafico& entorno, IPosicionable* modelo, 
                                    EntidadParser& parser, std::string& tipo);
    bool contienePunto(int x, int y);
    virtual ~EntidadVista() {};
    void actualizarApariencia(DatosApariencia& apariencia);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    void reproducirSonido(IPosicionable* foco);

private:
    Sprite sprite;
    EntornoGrafico& entorno;
    std::string ultimo_estado;
    std::string estado_anterior;
    IPosicionable* modelo;
    EntidadParser& parser;
    Animacion animacion;
    AnimacionBase* infoAnimacion;
    DatosApariencia apariencia;
    bool esta_apariencia;
    bool reprodujo_sonido = false;
    SDL_Rect mascara = {};
};

#endif
