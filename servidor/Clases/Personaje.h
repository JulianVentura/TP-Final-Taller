#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__
#include "Entidad.h"
class Escudo;
class Armadura;
class Casco;
class Personaje : public Entidad{
    private:
    unsigned int manaMaximo;
    unsigned int manaActual;
    unsigned int experiencia;
    unsigned int limiteParaSubir;
    unsigned int cantidadOro;
    Armadura *armadura;
    Escudo *escudo;
    Casco *casco;

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
    void equipar(Arma *arma);
    void equipar(Armadura *armadura);
    void equipar(Casco *casco);
    void equipar(Escudo *escudo);
    ~Personaje();
};

#endif
