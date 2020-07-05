#ifndef __CLASE_H__
#define __CLASE_H__
#include <string>

class Clase{
    protected:
    std::string id;
    float FClaseVida;
    float FClaseMana;
    float FClaseRecuperacion;
    float FClaseMeditacion;
    float mejoraFuerzaEnSubida;
    float mejoraInteligenciaEnSubida;
    float mejoraAgilidadEnSubida;
    float mejoraConstitucionEnSubida;

    public:
    Clase();
    Clase(std::string id);
    Clase& operator=(Clase &&otro);
    Clase& operator=(Clase &otro) = delete;
    const std::string obtenerId() const;

    friend class Configuraciones;
};


#endif
