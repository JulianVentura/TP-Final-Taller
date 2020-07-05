#include "GUI_BotonConectar_Controlador.h"

GUI_BotonConectarControlador::GUI_BotonConectarControlador(
	GUI_BotonConectar& vista, ServidorProxy& servidor, ServidorSalida& salida,
	 std::string& direccion, std::string& puerto, bool& conectado)
 : GUI_BotonControlador(vista.x, vista.y, vista.imagen.getAncho(),
  vista.imagen.getAlto()), vista(vista), servidor(servidor), salida(salida),
  direccion(direccion), puerto(puerto), conectado(conectado){}

bool GUI_BotonConectarControlador::enClick(){
	if(conectado) return false;

	try{
		//servidor.conectar(direccion, puerto);
		conectado = true;
	}catch(std::exception& e){
		salida.agregarMensaje("No se encuentra el servidor", true);
	}

	return true;
}

void GUI_BotonConectarControlador::actualizarDimension(){
	rect.x = vista.x;
	rect.y = vista.y;
	rect.w = vista.imagen.getAncho();
	rect.h = vista.imagen.getAlto();
}
