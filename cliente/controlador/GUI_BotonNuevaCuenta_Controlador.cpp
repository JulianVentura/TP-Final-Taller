#include "GUI_BotonNuevaCuenta_Controlador.h"

GUI_BotonNuevaCuentaControlador::GUI_BotonNuevaCuentaControlador(
	GUI_BotonNuevaCuenta& vista, ServidorProxy& servidor, ServidorSalida& salida,
	 std::string& nombre, std::string& clave, std::string& raza,
	 std::string& clase, bool& conectado, SDL_Event& evento_salida) :
	 GUI_BotonControlador(vista.x, vista.y, vista.imagen.getAncho(),
	 vista.imagen.getAlto()), vista(vista), servidor(servidor), salida(salida),
	 nombre(nombre), clave(clave), raza(raza), clase(clase),
	 conectado(conectado), evento_salida(evento_salida){}

bool GUI_BotonNuevaCuentaControlador::enClick(){
	if(!conectado) return false;
	
	try{
		servidor.enviarNuevaCuenta(nombre, clave, raza, clase);
		SDL_PushEvent(&evento_salida);
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