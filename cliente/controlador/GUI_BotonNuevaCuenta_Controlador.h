#ifndef __BOTON_NUEVA_CUENTA_CONTROLADOR_H__
#define __BOTON_NUEVA_CUENTA_CONTROLADOR_H__

#include <SDL2/SDL_render.h>

#include "../modelo/ServidorProxy.h"
#include "../modelo/ServidorSalida.h"
#include "../controlador/GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonNuevaCuenta.h"

class GUI_BotonNuevaCuentaControlador : public GUI_BotonControlador{
private:
	GUI_BotonNuevaCuenta& vista;
	ServidorProxy& servidor; 
	ServidorSalida& salida;
	std::string& nombre;
	std::string& clave;
	int& raza;
	int& clase;
	bool& conectado;
public:
	GUI_BotonNuevaCuentaControlador(GUI_BotonNuevaCuenta& vista,
	 ServidorProxy& servidor, ServidorSalida& salida, std::string& nombre,
	 std::string& clave, int& raza, int& clase, bool& conectado);
	bool enClick() override;
	void actualizarDimension();
};

#endif /*__BOTON_LOGIN_CONTROLADOR_H__*/