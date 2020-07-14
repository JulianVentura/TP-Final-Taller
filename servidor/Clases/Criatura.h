#ifndef __CRIATURA_H__
#define __CRIATURA_H__
#include "Entidad.h"
#include "Arma.h"

class Criatura : public Entidad{
    private:
    unsigned int diferenciador;
    double tiempoDespawn;
    double tiempoTranscurrido;
    float radioAgresividad;
    float radioVisibilidad;
    bool finalizado;
    std::string idObjetivo;
    Arma *arma;
    void continuarAtacando();
    void buscarObjetivo();
    void perseguir(Personaje *personaje);

    public:
    Criatura(float x, float y, std::string id);
    Criatura(Criatura &&otro) = delete;
    Criatura(Criatura &otro) = delete;
    Criatura& operator=(Criatura &&otro) = delete;
    Criatura& operator=(Criatura &otro) = delete;
    //Identificacion
    void agregarDiferenciador(const unsigned int numero);
    const std::string obtenerId() const override;
    //Estado / IA
    void actualizarEstado(double tiempo) override;
    bool haFinalizado() override;
    //Ataques
    std::string atacar(Personaje *objetivo) override;
    std::string atacar(Criatura *objetivo) override;
    void serAtacadoPor(Personaje *atacante) override;
    void serAtacadoPor(Criatura *atacante) override;
    std::string recibirDanio(int danio, Entidad *atacante) override;
    //Equipo
    void dropearItems(Entidad *atacante) override;
    //Comercio
    void interactuar(Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Estado *estad, Cliente *clienteo) override;
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    void vender(unsigned int pos, Estado *estado, Cliente *cliente) override;
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    void listar(Personaje *personaje, Cliente *cliente) override;

    ~Criatura();

};


#endif
