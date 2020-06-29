#ifndef __SERVIDOR_SALIDA_H__
#define __SERVIDOR_SALIDA_H__

#include <string>

class ServidorSalida{
	virtual void agregarMensaje(std::string& mensaje) = 0;
};

#endif /*__SERVIDOR_SALIDA_H__*/