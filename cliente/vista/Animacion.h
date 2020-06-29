#ifndef ANIMACION_H
#define ANIMACION_H

#include "Imagen.h"

#define REPETIR_INDEFINIDAMENTE 0

typedef std::unordered_map<std::string, std::vector<SDL_Rect>> mascaras_t;

class Animacion {
public:
    Animacion() = default;
    Animacion(Imagen& imagen, mascaras_t mascaras, 
                                        const std::string& animacion_inicial);
    void actualizar(unsigned int delta_t);
    void setAnimacion(const std::string& animacion);
    void setTiempoPorCiclo(unsigned int tiempo_por_ciclo);
    void setTiempoPorCuadro(unsigned int tiempo_por_cuadro);

private:
    Imagen* imagen = NULL;
    std::string animacion_actual;
    mascaras_t mascaras;
    unsigned int cuadro = 0;
    
    int tiempo_hasta_proximo_ciclo = 0;
    int tiempo_hasta_proximo_cuadro = 0;

    unsigned int tiempo_por_ciclo = REPETIR_INDEFINIDAMENTE;
    unsigned int tiempo_por_cuadro = 150;
};

#endif
