#ifndef __PROYECTIL_H__
#define __PROYECTIL_H__
#include "Entidad.h"
#include <atomic>

class Proyectil : public Entidad{
    private:
    Posicion destino;
    bool finalizado;
    bool haLlegadoADestino;
    double tiempoTranscurrido;
    double tiempoDespawn;
    static std::atomic<int> contador;
    
    public:
    Proyectil(std::string id, Posicion origen, Posicion destino);
    //Ataques
    std::string atacar(Personaje *objetivo) override;
    std::string atacar(Criatura *objetivo) override;
    void serAtacadoPor(Personaje *atacante) override;
    void serAtacadoPor(Criatura *atacante) override;
    std::string recibirDanio(int danio, Entidad *atacante) override;
    void recibirCuracion(unsigned int curacion, Entidad *lanzador) override;
    //Comercio
    void interactuar(Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Estado *estad, Cliente *clienteo) override;
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    void vender(unsigned int pos, Estado *estado, Cliente *cliente) override;
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    void listar(Personaje *personaje, Cliente *cliente) override;
    void transaccion(bool esDeposito, Estado *estado, Cliente *cliente) override;
    void curar(Personaje *personaje, Cliente *cliente);
    //Estado
    void actualizarEstado(double tiempo) override;
    std::string dropearItems(Entidad *atacante) override;

    bool haFinalizado() override;

    ~Proyectil() override;
};


#endif
