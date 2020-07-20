#ifndef __BOTON_LOGIN_CONTROLADOR_H__
#define __BOTON_LOGIN_CONTROLADOR_H__

#include "../modelo/ServidorProxy.h"
#include "../modelo/ServidorSalida.h"
#include "../controlador/GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonLogin.h"

class GUI_BotonLoginControlador final : public GUI_BotonControlador{
private:
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
};

#endif /*__BOTON_LOGIN_CONTROLADOR_H__*/