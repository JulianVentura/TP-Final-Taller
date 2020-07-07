#include "Clase.h"
#include "Configuraciones.h"


Clase::Clase() : id(""), idTCP(0){
    FClaseVida = 0;
    FClaseMana = 0;
    FClaseRecuperacion = 0;
    FClaseMeditacion = 0;
    mejoraFuerzaEnSubida = 0;
    mejoraInteligenciaEnSubida = 0;
    mejoraAgilidadEnSubida = 0;
    mejoraConstitucionEnSubida = 0;
}

Clase::Clase(std::string unId) : id(unId), idTCP(0){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    FClaseVida = config->obtenerFClaseVida(id);
    FClaseMana = config->obtenerFClaseMana(id);
    FClaseRecuperacion = config->obtenerFClaseRecuperacion(id);
    FClaseMeditacion = config->obtenerFClaseMeditacion(id);
    mejoraFuerzaEnSubida = config->obtenerClaseMejoraFuerzaEnSubida(id);
    mejoraInteligenciaEnSubida = config->obtenerClaseMejoraInteligenciaEnSubida(id);
    mejoraAgilidadEnSubida = config->obtenerClaseMejoraAgilidadEnSubida(id);
    mejoraConstitucionEnSubida = config->obtenerClaseMejoraConstitucionEnSubida(id);
    idTCP = config->obtenerClaseIDTCP(id);
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
    idTCP = std::move(otro.idTCP);
    return *this;
}

const std::string Clase::obtenerId() const{
    return id;
}


const uint16_t Clase::obtenerIDTCP() const{
    return idTCP;
}
