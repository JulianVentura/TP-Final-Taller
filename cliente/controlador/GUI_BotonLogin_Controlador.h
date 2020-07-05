#ifndef __BOTON_LOGIN_CONTROLADOR_H__
#define __BOTON_LOGIN_CONTROLADOR_H__

#include <SDL2/SDL_render.h>

#include "../modelo/ServidorProxy.h"
#include "../modelo/ServidorSalida.h"
#include "../controlador/GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonLogin.h"

class GUI_BotonLoginControlador : public GUI_BotonControlador{
private:
	GUI_BotonLogin& vista;
	ServidorProxy& servidor; 
	ServidorSalida& salida;
	std::string& nombre;
	std::string& clave;
	bool& conectado;
public:
	GUI_BotonLoginControlador(GUI_BotonLogin& vista,
	 ServidorProxy& servidor, ServidorSalida& salida, std::string& nombre,
	 std::string& clave, bool& conectado);
	bool enClick() override;
	void actualizarDimension();
};

#endif /*__BOTON_LOGIN_CONTROLADOR_H__*/