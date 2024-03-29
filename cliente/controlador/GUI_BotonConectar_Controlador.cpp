#include "GUI_BotonConectar_Controlador.h"

GUI_BotonConectarControlador::GUI_BotonConectarControlador(
	GUI_BotonConectar& vista, ServidorProxy& servidor, ServidorSalida& salida,
	 std::string& direccion, std::string& puerto, bool& conectado)
 : GUI_BotonControlador(vista), servidor(servidor), salida(salida),
  direccion(direccion), puerto(puerto), conectado(conectado){}

bool GUI_BotonConectarControlador::enClick(){
	if(conectado) return false;

	try{
		servidor.conectar(direccion, puerto);
		servidor.comenzarRecepcionConcurrente();
		direccion.clear();
		puerto.clear();
		conectado = true;
	}catch(std::exception& e){
		salida.agregarMensaje("No se encuentra el servidor", true);
	}

	return true;
}
