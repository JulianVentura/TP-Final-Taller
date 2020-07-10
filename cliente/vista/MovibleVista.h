#ifndef MOVIBLEVISTA_H
#define MOVIBLEVISTA_H

#include <string>
#include "AnimacionEnteDireccionable.h"
#include "IObstruible.h"
#include "Imagen.h"
#include "../modelo/EntidadParser.h"
#include "../controlador/IInteractivo.h"
                                        // TODO: provisorio
class MovibleVista: public IObstruible, public IInteractivo {
public:
    MovibleVista(EntornoGrafico& entorno, IPosicionable* modelo, 
                            EntidadParser& parser, DatosApariencia apariencia);
    virtual ~MovibleVista() {};

    void render() override;
    void actualizar(unsigned int delta_t) override;
    bool manejarEvento(SDL_Event& evento) override;
    
private:
    imagenes_t imagenes;
    std::string ultimo_estado;
    IPosicionable* modelo;
    EntidadParser& parser;
    DatosApariencia apariencia;
    AnimacionEnteDireccionable animacion;
    SDL_Rect mascara = {};
    const static std::vector<std::string> ordenDeImagenes;
};

#endif
