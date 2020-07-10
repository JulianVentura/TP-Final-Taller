#ifndef __SERVIDOR_SALIDA_ALERTA_H__
#define __SERVIDOR_SALIDA_ALERTA_H__

#include <string>

#include "../modelo/ServidorSalida.h"
#include "../vista/Ventana.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/IRendereable.h"
#include "../vista/Colores.h"

class ServidorSalidaAlerta : public IRendereable, public ServidorSalida{
private:
	std::string mensaje;
	Colores& paleta;
public:
	ServidorSalidaAlerta(EntornoGrafico& entorno, Colores& paleta);
	void render();
	void agregarMensaje(std::string mensaje, bool mensaje_publico);
	void salir();
};

#endif /*__SERVIDOR_SALIDA_ALERTA_H__*/ 