#ifndef __ESTADO_FANTASMA_H__
#define __ESTADO_FANTASMA_H__
#include "Estado.h"

class EstadoFantasma : public Estado{
    public:
    EstadoFantasma(Personaje *unPersonaje);
    //Ataque
    /*
    Devuelve un mensaje explicando la negacion al ataque.
    */
    std::string atacar(Entidad *objetivo, Arma *arma) override;
    /*
    Devuelve un mensaje explicando la negacion al ataque.
    */
    std::string serAtacadoPor(Entidad *atacante) override;
    //Otras acciones
    /*
    Metodo inutilizado, unicamente se define por cuestiones de polimorfismo y herencia de clase abstracta
    */
    void meditar() override;
    /*
    Metodo inutilizado, unicamente se define por cuestiones de polimorfismo y herencia de clase abstracta
    */
    void dejarDeMeditar() override;
    /*
    Setea vida y mana actual a cero y permite mover al personaje en el mapa.
    */
    void actualizar(double tiempo) override;
    /*
    Cambia el estado del personaje a EstadoInmovilizado
    */
    void resucitar(double tiempo) override;
    //Comercio
    /*
    Metodo inutilizado, unicamente se define por cuestiones de polimorfismo y herencia de clase abstracta
    */
    void interactuar(Entidad *entidad) override;
    /*
    Metodo inutilizado, unicamente se define por cuestiones de polimorfismo y herencia de clase abstracta
    */
    bool curar(float curVida, float curMana) override;
    /*
    Restaura completamente la vida y mana del personaje y cambia su estado a EstadoNormal.
    */
    void sanar() override;
    /*
    Metodo inutilizado, unicamente se define por cuestiones de polimorfismo y herencia de clase abstracta
    */
    void pedirListado(Interactuable *interactuable, Cliente *cliente) override;
    /*
    Metodo inutilizado, unicamente se define por cuestiones de polimorfismo y herencia de clase abstracta
    */
    void pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    /*
    Metodo inutilizado, unicamente se define por cuestiones de polimorfismo y herencia de clase abstracta
    */
    void pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    /*
    Metodo inutilizado, unicamente se define por cuestiones de polimorfismo y herencia de clase abstracta
    */
    void pedirTransaccion(bool esDeposito, Cliente *cliente, Banquero *banquero) override;
    
    ~EstadoFantasma() override;

};

#endif