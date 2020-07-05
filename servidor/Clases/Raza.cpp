#include "Raza.h"
#include "Configuraciones.h"


Raza::Raza() : id(""){
    FRazaVida = 0;
    FRazaMana = 0;
    FRazaRecuperacion = 0;
    FRazaMeditacion = 0;
    mejoraFuerzaEnSubida = 0;
    mejoraInteligenciaEnSubida = 0;
    mejoraAgilidadEnSubida = 0;
    mejoraConstitucionEnSubida = 0;
}

Raza::Raza(std::string unId) : id(unId){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    FRazaVida = config->obtenerFRazaVida(id);
    FRazaMana = config->obtenerFRazaMana(id);
    FRazaRecuperacion = config->obtenerFRazaRecuperacion(id);
    FRazaMeditacion = config->obtenerFRazaMeditacion(id);
    mejoraFuerzaEnSubida = config->obtenerRazaMejoraFuerzaEnSubida(id);
    mejoraInteligenciaEnSubida = config->obtenerRazaMejoraInteligenciaEnSubida(id);
    mejoraAgilidadEnSubida = config->obtenerRazaMejoraAgilidadEnSubida(id);
    mejoraConstitucionEnSubida = config->obtenerRazaMejoraConstitucionEnSubida(id);
}

Raza& Raza::operator=(Raza &&otro){
    id = std::move(otro.id);
    FRazaVida = otro.FRazaVida;
    FRazaMana = otro.FRazaMana;
    FRazaRecuperacion = otro.FRazaRecuperacion;
    FRazaMeditacion = otro.FRazaMeditacion;
    mejoraFuerzaEnSubida = otro.mejoraFuerzaEnSubida;
    mejoraInteligenciaEnSubida = otro.mejoraInteligenciaEnSubida;
    mejoraAgilidadEnSubida = otro.mejoraAgilidadEnSubida;
    mejoraConstitucionEnSubida = otro.mejoraConstitucionEnSubida;
    
    return *this;
}

const std::string Raza::obtenerId() const{
    return id;
}