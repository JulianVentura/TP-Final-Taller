#ifndef __BOTON_CONECTAR_CONTROLADOR_H__
#define __BOTON_CONECTAR_CONTROLADOR_H__

#include <SDL2/SDL_render.h>

#include "../modelo/ServidorProxy.h"
#include "../modelo/ServidorSalida.h"
#include "../controlador/GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonConectar.h"

/*
*	Ver GUI_Boton_Controlador.
*/

class GUI_BotonConectarControlador final : public GUI_BotonControlador{
private:
	ServidorProxy& servidor; 
	ServidorSalida& salida;
	std::string& direccion;
	std::string& puerto;
	bool& conectado;

	/*	Intenta conectarse a la direccion y puerto especificados.
	*	En caso de tener éxito inicia la recepcion concurrente de servidor y
	*	establece conectado en verdadero.
	*	De lo contrario imprime un mensaje por "salida".
	*/
	bool enClick() override;

public:
	GUI_BotonConectarControlador(GUI_BotonConectar& vista,
	 ServidorProxy& servidor, ServidorSalida& salida, std::string& direccion,
	 std::string& puerto, bool& conectado);


};

#endif /*__BOTON_LOGIN_CONTROLADOR_H__*/