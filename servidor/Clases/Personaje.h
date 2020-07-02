#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__
#include "Entidad.h"

class Personaje : public Entidad{
    private:
    unsigned int manaMaximo;
    unsigned int manaActual;
    unsigned int experiencia;
    unsigned int limiteParaSubir;
    unsigned int cantidadOro;

    void actualizarAtributos();

    public:
    Personaje(float x, float y, std::string id);
    Personaje(Personaje &otro) = delete;
    Personaje(Personaje &&otro) = delete;
    Personaje& operator=(Personaje &otro) = delete;
    Personaje& operator=(Personaje &&otro);
    void obtenerExperiencia(unsigned int cantidad) override;
    void actualizarEstado(double tiempo, Mapa *mapa) override;

    void recibirOro(unsigned int cantOro);
    void curar(unsigned int curVida, unsigned int curMana);
    void eliminarDeInventario(unsigned int pos);
    ~Personaje();
};

#endif
