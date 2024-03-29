#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__
#include "Entidad.h"
#include "Raza.h"
#include "Clase.h"
#include "Inventario.h"
#include <string>

#define NO_EQUIPADO -1

struct serializacionPersonaje;
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
    uint32_t limiteExpInferior;
    uint32_t cantidadOro;
    uint32_t oroEnAlmacen;
    uint32_t penalidad;
    int arma;
    int armadura;
    int escudo;
    int casco;
    Raza raza;
    Clase clase;
    std::unique_ptr<Estado> estado;
    Inventario inventario;
    std::vector<Item*> almacen;
    /*
    Actualiza todos los atributos del usuario, accediendo a Configuraciones para obtenerlos segun su nivel.
    */
    void actualizarAtributos();
    /* Cambia el estado a Normal */
    void estadoNormal();
    /* Cambia el estado a Fantasma */
    void estadoFantasma();
    /* Cambia el estado a Meditacion */
    void estadoMeditacion();
    /* Cambia el estado a Inmovilizado */
    void estadoInmovilizado(double tiempo);

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
    /*
    Sana completamente al personaje, delegando en el Estado.
    */
    void sanar();
    std::vector<Item*>& obtenerAlmacen();
    uint32_t& obtenerOroAlmacen();
    std::vector<Item*>* obtenerInventario();
    //Ataque
    std::string atacar(Personaje *objetivo) override;
    std::string atacar(Criatura *objetivo) override;
    void serAtacadoPor(Personaje *atacante) override;
    void serAtacadoPor(Criatura *atacante) override;
    std::string recibirDanio(int danio, Entidad *atacante) override;
    std::string dropearItems(Entidad *atacante) override;
    void obtenerExperiencia(unsigned int cantidad);
    void recibirCuracion(unsigned int curacion, Entidad *lanzador) override;
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
    void resucitar(double tiempo);
    //Comercio
    void tirar(unsigned int pos);
    void utilizar(unsigned int pos);
    void interactuar(Estado *estado, Cliente *cliente) override;
    void comprar(unsigned int pos, Estado *estad, Cliente *clienteo) override;
    void comprar(unsigned int pos, Personaje *personaje, Cliente *cliente) override;
    void vender(unsigned int pos, Estado *estado, Cliente *cliente) override;
    void vender(Item* item, Personaje *personaje, Cliente *cliente) override;
    void listar(Personaje *personaje, Cliente *cliente) override;
    void transaccion(bool esDeposito, Estado *estado, Cliente *cliente) override;
    bool tieneOroSuficiente(unsigned int cantOro);
    void restarOro(unsigned int cantOro);
    void recibirOro(unsigned int cantOro);
    uint16_t obtenerOro();
    //Serializacion
    serializacionPersonaje serializar();
    SerializacionEstado serializarEstado();
    SerializacionDibujado serializarDibujado();
    SerializacionEquipo serializarEquipo();

    ~Personaje();

    friend class Configuraciones;
    friend class EstadoNormal;
    friend class EstadoFantasma;
    friend class EstadoMeditacion;
    friend class EstadoInmovilizado;
};

#endif