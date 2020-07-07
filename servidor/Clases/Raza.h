#ifndef __RAZA_H__
#define __RAZA_H__
#include <string>

class Raza{
    private:
    std::string id;
    uint16_t idTCP;
    float FRazaVida;
    float FRazaMana;
    float FRazaRecuperacion;
    float FRazaMeditacion;
    float mejoraFuerzaEnSubida;
    float mejoraInteligenciaEnSubida;
    float mejoraAgilidadEnSubida;
    float mejoraConstitucionEnSubida;

    public:
    Raza();
    Raza(std::string id);
    Raza& operator=(Raza &&otro);
    Raza& operator=(Raza &otro) = delete;
    const std::string obtenerId() const;
    const uint16_t obtenerIDTCP() const;

    friend class Configuraciones;    
};


#endif
