#include "ServidorProxy.h"
#include <sys/socket.h>
#include <vector>

#ifndef OFFLINE
ServidorProxy::ServidorProxy(std::string direccion, std::string servicio,
	 DatosPersonaje& datos_personaje, DatosTienda& datos_tienda):
	 datos_personaje(datos_personaje), datos_tienda(datos_tienda) {
	salir = false;
	socket.conectar(direccion.c_str(), servicio.c_str());
	hilo_recepcion = new std::thread(&ServidorProxy::recibirMensaje, this);
	std::string id("personaje1"); // TODO: harcodeado
	protocolo.enviarID(socket, id);
}

void ServidorProxy::enviarMensaje(std::string mensaje){
	if(mensaje.size() != 0) protocolo.enviarString(socket, mensaje);
}

void ServidorProxy::enviarMovimiento(uint32_t movimiento) {
	protocolo.enviarMovimiento(socket, movimiento);
}

void ServidorProxy::recibirMensaje(){
	std::string mensaje;
	
	while(!salir){
		protocolo.recibirMensaje(socket);
	//	recibirString(socket, mensaje);
	// 	salida -> agregarMensaje(mensaje);
	// 	mensaje.clear();

	}
}

void ServidorProxy::terminar(){
	salir = true;
	hilo_recepcion -> join();
	delete hilo_recepcion;
	socket.cerrar_canal(SHUT_RDWR);
}

std::string ServidorProxy::obtenerMapa() {
	return std::move(protocolo.obtenerMapa());
}

std::vector<struct Posicionable> ServidorProxy::obtenerPosiciones() {
	return std::move(protocolo.obtenerPosiciones());
}
#else
ServidorProxy::ServidorProxy(std::string direccion, std::string servicio,
	 DatosPersonaje& datos_personaje, DatosTienda& datos_tienda):
	 datos_personaje(datos_personaje), datos_tienda(datos_tienda){}

void ServidorProxy::enviarMensaje(std::string mensaje){}

void ServidorProxy::recibirMensaje(){}

void ServidorProxy::terminar(){}
#endif