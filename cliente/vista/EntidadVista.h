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
    
private:
    Sprite sprite;
    std::string ultimo_estado;
    IPosicionable* modelo;
    EntidadParser& parser;
    Animacion animacion;
    AnimacionBase* infoAnimacion;
    DatosApariencia apariencia;
    bool esta_apariencia;
    SDL_Rect mascara = {};
};

#endif
