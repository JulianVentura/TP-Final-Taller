#ifndef CAMARA_H
#define CAMARA_H

#include "IDimensionable.h"
#include "ITargeteable.h"
#include "Renderer.h"

class Camara {
public:
    /**
     * @brief Crea una cámara.
     * @param contenedor: determina el límite donde se puede mover de la cámara.
     */
    Camara(IDimensionable& contenedor);

    /**
     * @param marco: Determina el campo visual de la cámara.
     */
    void setMarco(IDimensionable* marco);
    
    /**
     * @brief Determina el objetivo, es decir, lo que seguirá la cámara.
     */
    void setObjetivo(ITargeteable* objetivo);

    /**
     * @brief Centra el renderer en el foco de la cámara. Para salir de foco se debe 
     * llamar a reiniciar.
     */
    void centrar(Renderer* renderer, int ancho_unidad, float radio);

    /**
     * @brief Reinicia las transformaciones de renderer. Se debería llamar después de 
     * un centrar. 
     */
    void reiniciar(Renderer* renderer);

    static void transformar(int*x, int* y);
    
private:
    int maxX();
    int maxY();
    IDimensionable& contenedor;
    IDimensionable* marco;
    ITargeteable* objetivo;
    static int desplazamientoX;
    static int desplazamientoY;
    static float zoom;
};
#endif
