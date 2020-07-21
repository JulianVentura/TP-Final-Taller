#ifndef __ESTADO_MEDITACION_H__
#define __ESTADO_MEDITACION_H__
#include "Estado.h"

class EstadoMeditacion : public Estado{
    public:
    EstadoMeditacion(Personaje *unPersonaje); 
    //Ataque
    /*
    No realiza accion alguna, no se puede atacar en EstadoMeditacion.
    */
    std::string atacar(Entidad *objetivo, Arma *arma) override;
    /*
    Delega el ataque en el atacante y devuelve un mensaje de respuesta con el resultado del mismo.
    */
    std::string serAtacadoPor(Entidad *atacante) override;
    //Otras acciones
    /*
    No realiza accion alguna.
    */
    void meditar() override;
    /*
    El personaje deja de meditar, pasa a EstadoNormal
    */
    void dejarDeMeditar() override;
    /*
    Regenera la vida y mana del personaje.
    Si el manaActual del personaje se iguala al manaMaximo se cambiara el estado del personaje
    a EstadoNormal.
    El personaje no podra moverse mientras medite.
    */
    void actualizar(double tiempo) override;
    /*
    Lanza una instancia de Excepcion con un mensaje descriptivo explicando el motivo.
    */
    void resucitar(double tiempo) override;
    //Comercio
    /*
    No realiza accion alguna
    */
    void interactuar(Entidad *entidad) override;
    /*
    No realiza accion alguna
    */
    bool curar(float curVida, float curMana) override;
    /*
    No realiza accion alguna
    */
    void sanar() override;
    /*
    Le envia un mensaje descriptivo al cliente explicando por que no se puede realizar la accion
    */
    void pedirListado(Interactuable *interactuable, Cliente *cliente) override;
    /*
    Le envia un mensaje descriptivo al cliente explicando por que no se puede realizar la accion
    */
    void pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    /*
    Le envia un mensaje descriptivo al cliente explicando por que no se puede realizar la accion
    */
    void pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    /*
    Le envia un mensaje descriptivo al cliente explicando por que no se puede realizar la accion
    */
    void pedirTransaccion(bool esDeposito, Cliente *cliente, Banquero *banquero) override;
    ~EstadoMeditacion() override;
};


#endif