#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__
#include "Entidad.h"
#include "Raza.h"
#include "Clase.h"
class Escudo;
class Armadura;
class Casco;
class Estado;
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
    Raza raza;
    Clase clase;
    std::unique_ptr<Estado> estado;

    void actualizarAtributos();
    void estadoNormal();
    void estadoFantasma();
    void estadoMeditacion();

    public:
    Personaje();
    Personaje(float x, float y, std::string idPersonaje, std::string idClase, std::string idRaza);
    Personaje(Personaje &otro) = delete;
    Personaje(Personaje &&otro) = delete;
    Personaje& operator=(Personaje &otro) = delete;
    Personaje& operator=(Personaje &&otro);
    void obtenerExperiencia(unsigned int cantidad) override;
    void actualizarEstado(double tiempo, Mapa *mapa) override;

    void recibirOro(unsigned int cantOro);
    void curar(unsigned int curVida, unsigned int curMana);
    void recibirDanio(int danio, Entidad *atacante) override;
    void eliminarDeInventario(unsigned int pos);
    void equipar(Arma *arma);
    void equipar(Armadura *armadura);
    void equipar(Casco *casco);
    void equipar(Escudo *escudo);
    void meditar();
    void frenarMeditacion();
    ~Personaje();

    friend class Configuraciones;
    friend class BaseDeDatos;
    friend class EstadoNormal;
    friend class EstadoFantasma;
    friend class EstadoMeditacion;
};

#endif
