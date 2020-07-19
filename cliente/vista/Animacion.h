#ifndef ANIMACION_H
#define ANIMACION_H

#include "Imagen.h"
#include "AnimacionBase.h"
#include "../modelo/parsers/DatosApariencia.h"
#include <unordered_map>
#include <vector>
#include <string>


class Animacion {
public:
    explicit Animacion();
    virtual ~Animacion() = default;
    virtual void actualizar(unsigned int delta_t);
    void setInfo(AnimacionBase* infoAnimacion);
    void setAccion(const std::string& accion);
    void setMascara(SDL_Rect& mascara, int delta_x, int delta_y);
    void avanzar();
    void setTiempoPorCiclo(unsigned int tiempo_por_ciclo);
    void setTiempoPorCuadro(unsigned int tiempo_por_cuadro);

private:
    void reiniciar();
    AnimacionBase* infoAnimacion;
    std::string accion;
    int columna = 0;
    int tiempo_hasta_proximo_ciclo = 0;
    int tiempo_hasta_proximo_cuadro = 0;
    int tiempo_por_ciclo;
    int tiempo_por_cuadro;
    unsigned int ultimo_delta_t = 0;
};

#endif
