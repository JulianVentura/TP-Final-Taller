#include "GUI_BotonNuevaCuenta_Controlador.h"

GUI_BotonNuevaCuentaControlador::GUI_BotonNuevaCuentaControlador(
	GUI_BotonNuevaCuenta& vista, ServidorProxy& servidor, ServidorSalida& salida,
	 std::string& nombre, std::string& clave, int& raza, int& clase,
	  bool& conectado) : GUI_BotonControlador(vista.x, vista.y,
	  vista.imagen.getAncho(),vista.imagen.getAlto()), vista(vista),
	  servidor(servidor), salida(salida), nombre(nombre), clave(clave),
	   raza(raza), clase(clase), conectado(conectado){}

bool GUI_BotonNuevaCuentaControlador::enClick(){
	if(!conectado) return false;
	
	try{
		//servidor.enviarNuevaCuenta(nombre, clave);
	}catch(std::exception& e){
		salida.agregarMensaje("Falla conexion", true);
		conectado = false;
	}

	return true;
}

void GUI_BotonNuevaCuentaControlador::actualizarDimension(){
	rect.x = vista.x;
	rect.y = vista.y;
	rect.w = vista.imagen.getAncho();
	rect.h = vista.imagen.getAlto();
}