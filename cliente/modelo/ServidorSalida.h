#ifndef __SERVIDOR_SALIDA_H__
#define __SERVIDOR_SALIDA_H__

#include <string>

class ServidorSalida{
public:
	virtual void agregarMensaje(std::string mensaje, bool mensaje_publico) = 0;
};

#endif /*__SERVIDOR_SALIDA_H__*/
