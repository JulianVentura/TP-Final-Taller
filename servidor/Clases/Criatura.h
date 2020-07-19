#ifndef __CRIATURA_H__
#define __CRIATURA_H__
#include "Entidad.h"
#include "Arma.h"

class Criatura : public Entidad{
    private:
    unsigned int diferenciador;
    double tiempoUltimaActualizacion;
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
    /*
    Agrega el diferenciador que permitira diferenciar las id de esta criatura de la de las demas.
    */
    void agregarDiferenciador(const unsigned int numero);
    /*
    Enviara el id debido a su tipo sumado al diferenciador de instancia.
    */
    const std::string obtenerId() const override;
    //Estado / IA
    /*
    Ejecuta el algoritmo de IA de la criatura.
    Una vez muerta actualizara el tiempo transcurrido hasta superar el tiempo de despawn, momento
    en el cual la criatura habra finalizado y podra ser descargada del mapa.
    */
    void actualizarEstado(double tiempo) override;
    /*
    Indica si puede ser descargada del mapa.
    */
    bool haFinalizado() override;
    //Ataques
    /*
    Marca al personaje recibido como el objetivo actual y efectua un ataque sobre el.
    Ademas buscara acercarse lo maximo posible a el.
    Devuelve siempre una cadena vacia.
    */
    std::string atacar(Personaje *objetivo) override;
    /*
    No efectua ataque, devuelve siempre una cadena vacia.
    */
    std::string atacar(Criatura *objetivo) override;
    /*
    Utilizado para double-dispatch, delegando el ataque en el atacante.
    Envia un mensaje descriptivo al jugador con el resultado obtenido.
    */
    void serAtacadoPor(Personaje *atacante) override;
    /*
    No hace nada.
    */
    void serAtacadoPor(Criatura *atacante) override;
    /*
    Marca al atacante como su nuevo objetivo.
    Disminuye la vida de la criatura en base al parametro danio recibido.
    Existe cierta chance de que el golpe recibido sea critico, el cual hara el doble de daño y
    no podra ser esquivado.
    Existe cierta chance de esquivar el golpe.
    Si la vidaActual se vuelve 0 existe cierta probabilidad de dropear un item u oro. Ademas la criatura
    morira y podra ser eliminada del mapa tras superarse el tiempo de despawn.
    Devuelve en cada caso un mensaje descriptivo con el resultado del ataque.
    */
    std::string recibirDanio(int danio, Entidad *atacante) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void recibirCuracion(unsigned int curacion, Entidad *lanzador) override;
    //Equipo
    /*
    Metodo que define el drop de items u oro.
    El mismo se encargara de crear una instancia de bolsa de items en el mapa al cual pertenece la criatura.
    Devuelve un mensaje describiendo la cantidad de oro dropeada, en tal caso.
    */
    std::string dropearItems(Entidad *atacante) override;
    //Comercio
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void interactuar(Estado *estado, Cliente *cliente) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void comprar(unsigned int pos, Estado *estad, Cliente *clienteo) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void vender(unsigned int pos, Estado *estado, Cliente *cliente) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void listar(Personaje *personaje, Cliente *cliente) override;
    /*
    Inutilizado en esta clase, definido unicamente para respetar herencia de clase abstracta y polimorfismo.
    */
    void transaccion(bool esDeposito, Estado *estado, Cliente *cliente) override;

    ~Criatura();

};


#endif
