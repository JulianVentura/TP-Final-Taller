#include "GUI_BotonLogin_Controlador.h"

GUI_BotonLoginControlador::GUI_BotonLoginControlador(
	GUI_BotonLogin& vista, ServidorProxy& servidor, ServidorSalida& salida,
	 std::string& nombre, std::string& clave, bool& conectado)
 : GUI_BotonControlador(vista.x, vista.y, vista.imagen.getAncho(),
  vista.imagen.getAlto()), vista(vista), servidor(servidor), salida(salida),
  nombre(nombre), clave(clave), conectado(conectado){}

bool GUI_BotonLoginControlador::enClick(){
	if(!conectado) return false;

	try{
		//servidor.enviarLogin(nombre, clave);
	}catch(std::exception& e){
		salida.agregarMensaje("Falla conexion", true);
		conectado = false;
	}

	return true;
}

void GUI_BotonLoginControlador::actualizarDimension(){
	rect.x = vista.x;
	rect.y = vista.y;
	rect.w = vista.imagen.getAncho();
	rect.h = vista.imagen.getAlto();
}