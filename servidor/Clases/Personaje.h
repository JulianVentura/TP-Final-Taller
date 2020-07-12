#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__
#include "Entidad.h"
#include "Raza.h"
#include "Clase.h"
#include "Inventario.h"
class Escudo;
class Armadura;
class Casco;
class Estado;
class Criatura;

struct serializacionPersonaje{
    uint32_t x, y;
    uint32_t vidaMaxima;
    uint32_t vidaActual;
    uint32_t manaMaximo;
    uint32_t manaActual;
    uint32_t experiencia;
    uint32_t limiteParaSubir;
    uint32_t nivel;
    uint32_t cantidadOro;
    uint16_t inventario[18];
    uint16_t almacen[18];
}__attribute__((packed, aligned(4)));

class Personaje : public Entidad{
    private:
    uint32_t experiencia;
    uint32_t limiteParaSubir;
    uint32_t cantidadOro;
    Armadura *armadura;
    Escudo *escudo;
    Casco *casco;
    Raza raza;
    Clase clase;
    std::unique_ptr<Estado> estado;
    Inventario inventario;
    std::vector<Item*> almacen;

    bool _recibirDanio(int danio, Entidad *atacante);

    void actualizarAtributos();
    void estadoNormal();
    void estadoFantasma();
    void estadoMeditacion();

    public:
    Personaje();
    Personaje(float x, float y, std::string idPersonaje,
     std::string idClase, std::string idRaza);
    Personaje(std::string idPersonaje, std::string idRaza,
    std::string idClase, serializacionPersonaje& datos);
    Personaje(Personaje &otro) = delete;
    Personaje(Personaje &&otro) = delete;
    Personaje& operator=(Personaje &otro) = delete;
    Personaje& operator=(Personaje &&otro);
    


    void curar(unsigned int curVida, unsigned int curMana);
    void curar();
    std::vector<Item*>& obtenerAlmacen();
    std::vector<Item*>* obtenerInventario();
    //Ataque
    void atacar(Personaje *objetivo) override;
    void atacar(Criatura *objetivo) override;
    void serAtacadoPor(Entidad *atacante) override;
    void serAtacadoPor(Personaje *atacante) override;
    void serAtacadoPor(Criatura *atacante) override;
    bool recibirDanio(int danio, Entidad *atacante) override;
    void dropearItems(Entidad *atacante) override;
    void obtenerExperiencia(unsigned int cantidad);
    serializacionPersonaje serializar();
    //Equipo
    void almacenar(Item *item);
    void eliminarDeInventario(unsigned int pos);
    void equipar(Arma *arma);
    void equipar(Armadura *armadura);
    void equipar(Casco *casco);
    void equipar(Escudo *escudo);
    //Estado
    void actualizarEstado(double tiempo) override;
    void meditar();
    void frenarMeditacion();
    Estado *obtenerEstado();
    //Comercio
    void interactuar(Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Estado *estad, Cliente *clienteo) override;
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    void vender(unsigned int pos, Estado *estado, Cliente *cliente) override;
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    void listar(Personaje *personaje, Cliente *cliente) override;
    bool tieneOroSuficiente(unsigned int cantOro);
    void restarOro(unsigned int cantOro);
    void recibirOro(unsigned int cantOro);
    uint16_t obtenerOro();

    ~Personaje();

    friend class Cliente;
    friend class Configuraciones;
    friend class BaseDeDatos;
    friend class EstadoNormal;
    friend class EstadoFantasma;
    friend class EstadoMeditacion;
};

#endif
