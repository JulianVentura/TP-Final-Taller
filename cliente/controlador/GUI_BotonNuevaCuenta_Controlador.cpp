#include "GUI_BotonNuevaCuenta_Controlador.h"

GUI_BotonNuevaCuentaControlador::GUI_BotonNuevaCuentaControlador(
	GUI_BotonNuevaCuenta& vista, ServidorProxy& servidor, ServidorSalida& salida,
	 std::string& nombre, std::string& clave, std::string& raza,
	 std::string& clase, bool& conectado) : GUI_BotonControlador(vista),
	 servidor(servidor), salida(salida), nombre(nombre), clave(clave),
	 raza(raza), clase(clase), conectado(conectado){}

bool GUI_BotonNuevaCuentaControlador::enClick(){
	if(!conectado) return false;
	
	try{
		servidor.enviarNuevaCuenta(nombre, clave, raza, clase);
	}catch(std::exception& e){
		salida.agregarMensaje("Falla conexion", true);
		conectado = false;
	}
	return true;
}
