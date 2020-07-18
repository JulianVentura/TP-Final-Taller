#ifndef __ESTADO_INMOVILIZADO_H__
#define __ESTADO_INMOVILIZADO_H__
#include "Estado.h"
#include "Posicion.h"
class EstadoInmovilizado : public Estado{
    private:
    double penalizacion;
    double timepoTranscurrido;
    public:
    EstadoInmovilizado(Personaje *unPersonaje, double pen);
    //Ataque
    std::string atacar(Entidad *objetivo, Arma *arma) override;
    std::string serAtacadoPor(Entidad *atacante) override;
    //Otras acciones
    void meditar() override;
    void dejarDeMeditar() override;
    void actualizar(double tiempo) override;
    void resucitar(double tiempo) override;
    //Comercio
    void interactuar(Entidad *entidad) override;
    bool curar(float curVida, float curMana) override;
    void sanar() override;
    void pedirListado(Interactuable *interactuable, Cliente *cliente) override;
    void pedirCompra(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    void pedirVenta(unsigned int pos, Interactuable *interactuable, Cliente *cliente) override;
    void pedirTransaccion(bool esDeposito, Cliente *cliente, Banquero *banquero) override;
    
    ~EstadoInmovilizado() override;

};

#endif