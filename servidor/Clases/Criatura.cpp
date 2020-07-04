#include "Criatura.h"
#include "Configuraciones.h"
#include <utility>
#include <memory>
#include <sstream>

Criatura::Criatura(float x, float y, std::string unId, FabricaDeItems &fabricaItems) : 
                                       Entidad(unId){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    //Seteo los campos.
    vidaMaxima = config->obtenerCriaturaVidaMax(unId);
    vidaActual = vidaMaxima;
    manaMaximo = config->obtenerCriaturaManaMax(unId);
    manaActual = manaMaximo;
    nivel = config->obtenerCriaturaNivel(unId);
    fuerza = config->obtenerCriaturaFuerza(unId);
    inteligencia = config->obtenerCriaturaInteligencia(unId);
    agilidad = config->obtenerCriaturaAgilidad(unId);
    constitucion = config->obtenerCriaturaConstitucion(unId);
    std::string idArma = config->obtenerCriaturaIdArma(id);
    float ancho = config->obtenerCriaturaAncho(unId);
    float alto = config->obtenerCriaturaAncho(unId);
    posicion = std::move(Posicion(x, y, ancho, alto));
    std::unique_ptr<Arma> armaEncapsulada = std::move(fabricaItems.crearArma(idArma));
    this->arma = armaEncapsulada.get();
    inventario.almacenar(std::move(armaEncapsulada));
    desplazamiento = config->obtenerCriaturaVelDesplazamiento(unId);
}

void Criatura::agregarDiferenciador(const unsigned int numero){
    std::stringstream nuevoId;
    nuevoId << this->id << numero;
    id = nuevoId.str();
}

Criatura::~Criatura(){}
