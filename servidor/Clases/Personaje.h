#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__
#include "Entidad.h"
#include "Raza.h"
#include "Clase.h"
class Escudo;
class Armadura;
class Casco;
class Estado;
class Criatura;
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
    std::vector<Item*> almacen;

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

    bool tieneOroSuficiente(unsigned int cantOro);
    void restarOro(unsigned int cantOro);
    void recibirOro(unsigned int cantOro) override;
    uint16_t obtenerOro();

    void curar(unsigned int curVida, unsigned int curMana);
    void curar();
    std::vector<Item*>& obtenerAlmacen();
    std::vector<Item*>* obtenerInventario();
    void atacar(Personaje *objetivo, Divulgador *divulgador) override;
    void atacar(Criatura *objetivo, Divulgador *divulgador) override;
    void serAtacadoPor(Personaje *atacante, Divulgador *divulgador) override;
    void serAtacadoPor(Criatura *atacante, Divulgador *divulgador) override;
    void recibirDanio(int danio, Entidad *atacante, Divulgador *divulgador) override;
    void dropearItems(Entidad *atacante) override;

    void eliminarDeInventario(unsigned int pos);
    void equipar(Arma *arma);
    void equipar(Armadura *armadura);
    void equipar(Casco *casco);
    void equipar(Escudo *escudo);
    void meditar();
    void frenarMeditacion();
    Estado *obtenerEstado();
    ~Personaje();

    friend class Configuraciones;
    friend class BaseDeDatos;
    friend class EstadoNormal;
    friend class EstadoFantasma;
    friend class EstadoMeditacion;
};

#endif
