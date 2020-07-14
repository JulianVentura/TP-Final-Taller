#ifndef MOVIBLEVISTA_H
#define MOVIBLEVISTA_H

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
    virtual bool contienePunto(int x, int y);
    virtual void actualizarApariencia(DatosApariencia& apariencia);

protected:
    imagenes_t imagenes;
    std::string ultimo_estado;
    IPosicionable* modelo;
    EntidadParser& parser;
    Animacion animacion;
};

class MovibleVista: public EntidadVista {
public:
    MovibleVista(EntornoGrafico& entorno, IPosicionable* modelo, 
                                                        EntidadParser& parser);
    virtual ~MovibleVista() {};
    void actualizarApariencia(DatosApariencia& apariencia) override;
    void render() override;
    void actualizar(unsigned int delta_t) override;
    
private:
    DatosApariencia apariencia;
    AnimacionEnteDireccionable animacion_local;
    bool esta_apariencia;
    SDL_Rect mascara = {};
    const static std::vector<std::string> ordenDeImagenes;
};

#endif
