#ifndef CAMARA_H
#define CAMARA_H

#include "IDimensionable.h"
#include "ITargeteable.h"
#include "Renderer.h"

class Camara {
public:
    Camara() = default;
    /**
     * @brief Crea una cámara.
     * @param contenedor: determina el límite donde se puede mover de la cámara.
     * @param marco: Determina el campo visual de la cámara.
     */
    Camara(IDimensionable* contenedor, IDimensionable* marco, float zoom);

    /**
     * @brief Determina el objetivo, es decir, lo que seguirá la cámara.
     */
    void setObjetivo(ITargeteable& objetivo);

    /**
     * @brief Centra el renderer en el foco de la cámara. Para salir de foco se debe 
     * llamar a reiniciar.
     */
    void centrar(Renderer* renderer);

    /**
     * @brief Reinicia las transformaciones de renderer. Se debería llamar después de 
     * un centrar. 
     */
    void reiniciar(Renderer* renderer);

private:
    IDimensionable* contenedor;
    IDimensionable* marco;
    ITargeteable* objetivo;
    int desplazamientoX = 0;
    int desplazamientoY = 0;
    float zoom = 1.0f;
};
#endif
