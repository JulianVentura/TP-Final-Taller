#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__
#include "Entidad.h"
#include "Raza.h"
#include "Clase.h"
#include "Inventario.h"
#include <string>

#define NO_EQUIPADO -1

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

class Estado;
class Criatura;
class Casco;
class Arma;
class Escudo;
class Armadura;
class Personaje : public Entidad{
    private:
    uint32_t experiencia;
    uint32_t limiteParaSubir;
    uint32_t cantidadOro;
    int arma;
    int armadura;
    int escudo;
    int casco;
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
    


    void curar(float curVida, float curMana);
    void curar();
    std::vector<Item*>& obtenerAlmacen();
    std::vector<Item*>* obtenerInventario();
    //Ataque
    std::string atacar(Personaje *objetivo) override;
    std::string atacar(Criatura *objetivo) override;
    void serAtacadoPor(Personaje *atacante) override;
    void serAtacadoPor(Criatura *atacante) override;
    std::string recibirDanio(int danio, Entidad *atacante) override;
    void dropearItems(Entidad *atacante) override;
    void obtenerExperiencia(unsigned int cantidad);
    //Equipo
    void almacenar(Item *item);
    void eliminarDeInventario(unsigned int pos);
    void equipar(Arma *arma, unsigned int pos);
    void equipar(Armadura *armadura, unsigned int pos);
    void equipar(Casco *casco, unsigned int pos);
    void equipar(Escudo *escudo, unsigned int pos);
    void desequipar(Arma *arma, int pos);
    void desequipar(Armadura *armadura, int pos);
    void desequipar(Escudo *escudo, int pos);
    void desequipar(Casco *casco, int pos);
    //Estado
    void actualizarEstado(double tiempo) override;
    void meditar();
    void frenarMeditacion();
    Estado *obtenerEstado();
    //Comercio
    void tirar(unsigned int pos);
    void utilizar(unsigned int pos);
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
    //Serializacion
    serializacionPersonaje serializar();
    serializacionDibujado serializarEstado();
    // serializacionEstado serializarEstado();
    SerializacionEquipo serializarEquipo();

    ~Personaje();

    friend class Cliente;               //ELIMINAR ESTO
    friend class Configuraciones;
    friend class BaseDeDatos;
    friend class EstadoNormal;
    friend class EstadoFantasma;
    friend class EstadoMeditacion;
};

#endif
