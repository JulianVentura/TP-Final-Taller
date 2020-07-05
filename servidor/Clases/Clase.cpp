#include "Clase.h"
#include "Configuraciones.h"


Clase::Clase() : id(""){
    FClaseVida = 0;
    FClaseMana = 0;
    FClaseRecuperacion = 0;
    FClaseMeditacion = 0;
    mejoraFuerzaEnSubida = 0;
    mejoraInteligenciaEnSubida = 0;
    mejoraAgilidadEnSubida = 0;
    mejoraConstitucionEnSubida = 0;
}

Clase::Clase(std::string unId) : id(unId){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    FClaseVida = config->obtenerFClaseVida(id);
    FClaseMana = config->obtenerFClaseMana(id);
    FClaseRecuperacion = config->obtenerFClaseRecuperacion(id);
    FClaseMeditacion = config->obtenerFClaseMeditacion(id);
    mejoraFuerzaEnSubida = config->obtenerClaseMejoraFuerzaEnSubida(id);
    mejoraInteligenciaEnSubida = config->obtenerClaseMejoraInteligenciaEnSubida(id);
    mejoraAgilidadEnSubida = config->obtenerClaseMejoraAgilidadEnSubida(id);
    mejoraConstitucionEnSubida = config->obtenerClaseMejoraConstitucionEnSubida(id);
}


Clase& Clase::operator=(Clase &&otro){
    id = std::move(otro.id);
    FClaseVida = otro.FClaseVida;
    FClaseMana = otro.FClaseMana;
    FClaseRecuperacion = otro.FClaseRecuperacion;
    FClaseMeditacion = otro.FClaseMeditacion;
    mejoraFuerzaEnSubida = otro.mejoraFuerzaEnSubida;
    mejoraInteligenciaEnSubida = otro.mejoraInteligenciaEnSubida;
    mejoraAgilidadEnSubida = otro.mejoraAgilidadEnSubida;
    mejoraConstitucionEnSubida = otro.mejoraConstitucionEnSubida;

    return *this;
}

const std::string Clase::obtenerId() const{
    return id;
}
