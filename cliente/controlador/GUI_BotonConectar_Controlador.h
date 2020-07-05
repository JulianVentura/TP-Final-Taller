#ifndef __BOTON_CONECTAR_CONTROLADOR_H__
#define __BOTON_CONECTAR_CONTROLADOR_H__

#include <SDL2/SDL_render.h>

#include "../modelo/ServidorProxy.h"
#include "../modelo/ServidorSalida.h"
#include "../controlador/GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonConectar.h"

class GUI_BotonConectarControlador : public GUI_BotonControlador{
private:
	GUI_BotonConectar& vista;
	ServidorProxy& servidor; 
	ServidorSalida& salida;
	std::string& direccion;
	std::string& puerto;
	bool& conectado;
public:
	GUI_BotonConectarControlador(GUI_BotonConectar& vista,
	 ServidorProxy& servidor, ServidorSalida& salida, std::string& direccion,
	 std::string& puerto, bool& conectado);
	bool enClick() override;
	void actualizarDimension();
};

#endif /*__BOTON_LOGIN_CONTROLADOR_H__*/