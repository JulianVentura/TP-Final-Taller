#ifndef __ESTADO_INMOVILIZADO_H__
#define __ESTADO_INMOVILIZADO_H__
#include "Estado.h"
#include "Posicion.h"
class EstadoInmovilizado : public Estado{
    private:
    double tiempoTranscurrido;
    public:
    EstadoInmovilizado(Personaje *unPersonaje, double pen);
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
    Regenera la barra de salud del personaje en base al tiempo transcurrido y la penalidad obtenida.
    Cuando la vida actual del personaje sea igual a la maxima cambiara el estado del personaje a 
    EstadoNormal
    */
    void actualizar(double tiempo) override;
    /*
    Lanza una instancia de Excepcion con un mensaje descriptivo del motivo.
    */
    void resucitar(double tiempo) override;
    //Comercio
    /*
    Envia un mensaje al cliente explicando la negacion al pedido.
    */
    void interactuar(Entidad *entidad) override;
    /*
    Envia un mensaje al cliente explicando la negacion al pedido.
    */
    bool curar(float curVida, float curMana) override;
    /*
    Lanza una instancia de Excepcion con un mensaje descriptivo del motivo
    */
    void sanar() override;
    /*
    Envia un mensaje al cliente explicando la negacion al pedido.
    */
    void pedirListado(Interactuable *interactuable, Cliente *cliente) override;
    /*
    Envia un mensaje al cliente explicando la negacion al pedido.
    */
    void pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    /*
    Envia un mensaje al cliente explicando la negacion al pedido.
    */
    void pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    /*
    Envia un mensaje al cliente explicando la negacion al pedido.
    */
    void pedirTransaccion(bool esDeposito, Cliente *cliente, Banquero *banquero) override;
    
    ~EstadoInmovilizado() override;

};

#endif