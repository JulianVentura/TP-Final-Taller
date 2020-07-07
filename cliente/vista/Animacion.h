#ifndef ANIMACION_H
#define ANIMACION_H

#include "Imagen.h"
#include "../modelo/EntidadParser.h"
#include <unordered_map>
#include <vector>
#include <string>

#define REPETIR_INDEFINIDAMENTE 0

class Animacion {
public:
    Animacion(EntidadParser& parser, const std::string& animacion_inicial);
    virtual ~Animacion() = default;
    virtual void actualizar(unsigned int delta_t);
    void setAnimacion(const std::string& animacion);
    void setDireccion(const std::string& direccion);
    void setAccion(const std::string& accion);
    void setMascara(Imagen* imagen);
    void avanzar();
    void setTiempoPorCiclo(unsigned int tiempo_por_ciclo);
    void setTiempoPorCuadro(unsigned int tiempo_por_cuadro);

private:
    void reiniciar();
    EntidadParser& parser;

protected:
    std::string tipo;
    std::string accion;
    std::string direccion;
    int columna = 0;
    bool esta_quieto = true;
    int tiempo_hasta_proximo_ciclo = 0;
    int tiempo_hasta_proximo_cuadro = 0;
    int tiempo_por_ciclo = REPETIR_INDEFINIDAMENTE;
    int tiempo_por_cuadro = 300;
    unsigned int ultimo_delta_t = 0;
};

#endif
