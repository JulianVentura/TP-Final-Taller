#ifndef ENTIDADVISTA_H
#define ENTIDADVISTA_H

#include <string>
#include "AnimacionEnteDireccionable.h"
#include "IObstruible.h"
#include "Imagen.h"
#include "../modelo/EntidadParser.h"

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
    imagenes_t imagenes;
    std::string ultimo_estado;
    IPosicionable* modelo;
    EntidadParser& parser;
    AnimacionEnteDireccionable animacion_local;
    Animacion animacion;
    DatosApariencia apariencia;
    bool esta_apariencia;
    SDL_Rect mascara = {};
    const static std::vector<std::string> ordenDeImagenes;
};

#endif
