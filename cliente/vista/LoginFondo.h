#ifndef __LOGIN_FONDO_H__
#define __LOGIN_FONDO_H__

#include "../vista/Ventana.h"
#include "../vista/IRendereable.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/Imagen.h"
#include "../vista/Colores.h"

class LoginFondo : public IRendereable{
private:
	Colores& paleta;
	bool& conectado;
	Imagen imagen;
public:
	LoginFondo(EntornoGrafico& entorno, Colores& paleta,bool& conectado);
	void render();
};

#endif /*__LOGIN_FONDO_H__*/