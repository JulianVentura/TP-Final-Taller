#ifndef MOVIBLEVISTA_H
#define MOVIBLEVISTA_H

#include <string>
#include "AnimacionEnteDireccionable.h"
#include "IObstruible.h"
#include "Imagen.h"
#include "../modelo/EntidadParser.h"

class MovibleVista: public IObstruible {
public:
    MovibleVista(EntornoGrafico& entorno, IPosicionable* modelo, 
                                                        EntidadParser& parser);
    virtual ~MovibleVista() {};
    void actualizarApariencia(DatosApariencia& apariencia);
    void render() override;
    void actualizar(unsigned int delta_t) override;
    bool contienePunto(int x, int y);
    
private:
    imagenes_t imagenes;
    std::string ultimo_estado;
    IPosicionable* modelo;
    EntidadParser& parser;
    DatosApariencia apariencia;
    AnimacionEnteDireccionable animacion;
    bool esta_apariencia;
    SDL_Rect mascara = {};
    const static std::vector<std::string> ordenDeImagenes;
};

#endif
