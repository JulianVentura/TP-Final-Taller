#ifndef __ESTADO_NORMAL_H__
#define __ESTADO_NORMAL_H__
#include "Estado.h"

class EstadoNormal : public Estado{
    public:
    EstadoNormal(Personaje *unPersonaje); 
    //Ataque
    /*
    Delega el ataque en el arma del personaje y devuelve un mensaje de respuesta con el resultado del mismo.
    */
    std::string atacar(Entidad *objetivo, Arma *arma) override;
    /*
    Delega el ataque en el atacante y devuelve un mensaje de respuesta con el resultado del mismo.
    */
    std::string serAtacadoPor(Entidad *atacante) override;
    //Otras acciones
    /*
    Cambia el estado del personaje a EstadoMeditacion.
    Ademas envia un mensaje al personaje que le indica que ha comenzado a meditar.
    */
    void meditar() override;
    /*
    No realiza accion alguna
    */
    void dejarDeMeditar() override;
    /*
    Regenera vida y mana del personaje.
    Delega el movimiento del personaje en Posicion.
    */
    void actualizar(double tiempo) override;
    /*
    Lanza una excepcion con un mensaje descriptivo explicando por que no se puede realizar esta accion.
    */
    void resucitar(double tiempo) override;
    //Comercio
    /*
    No realiza accion alguna
    */
    void interactuar(Entidad *entidad) override;
    /*
    Cura la vida del personaje en curVida y el mana en curMana
    */
    bool curar(float curVida, float curMana) override;
    /*
    Cura la vida y mana del personaje a sus niveles maximos.
    */
    void sanar() override;
    /*
    Solicita listado al interactuable
    */
    void pedirListado(Interactuable *interactuable, Cliente *cliente) override;
    /*
    Solicita compra al interactuable
    */
    void pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    /*
    Solicita venta al interactuable, pasandole
    */
    void pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    void pedirTransaccion(bool esDeposito, Cliente *cliente, Banquero *banquero) override;

    ~EstadoNormal() override;
};


#endif