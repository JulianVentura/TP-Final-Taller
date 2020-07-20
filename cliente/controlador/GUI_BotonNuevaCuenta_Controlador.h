#ifndef __BOTON_NUEVA_CUENTA_CONTROLADOR_H__
#define __BOTON_NUEVA_CUENTA_CONTROLADOR_H__

#include "../modelo/ServidorProxy.h"
#include "../modelo/ServidorSalida.h"
#include "../controlador/GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonNuevaCuenta.h"

/*
*	Ver GUI_Boton_Controlador.
*/


class GUI_BotonNuevaCuentaControlador final : public GUI_BotonControlador{
private:
	ServidorProxy& servidor; 
	ServidorSalida& salida;
	std::string& nombre;
	std::string& clave;
	std::string& raza;
	std::string& clase;
	bool& conectado;

	/*	Si conectado es verdadero, intenta crear una cuenta con los datos provistos.
	*	Ante una falla imprime un mensaje por "salida", en caso de desconexion establece
	*	conectado en falso.
	*/
	bool enClick() override;
public:
	GUI_BotonNuevaCuentaControlador(GUI_BotonNuevaCuenta& vista,
	 ServidorProxy& servidor, ServidorSalida& salida, std::string& nombre,
	 std::string& clave, std::string& raza, std::string& clase, bool& conectado);
};

#endif /*__BOTON_LOGIN_CONTROLADOR_H__*/