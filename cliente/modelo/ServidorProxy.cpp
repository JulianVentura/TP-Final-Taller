#include "../modelo/ServidorProxy.h"
#include <sys/socket.h>
#include <vector>

#ifndef OFFLINE
ServidorProxy::ServidorProxy(std::string direccion, std::string servicio,
	 DatosPersonaje& datos_personaje, DatosTienda& datos_tienda):
	 datos_personaje(datos_personaje), datos_tienda(datos_tienda) {
	salir = false;
	socket.conectar(direccion.c_str(), servicio.c_str());
	hilo_recepcion = new std::thread(&ServidorProxy::recibirMensaje, this);
}

void ServidorProxy::enviarMensaje(std::string mensaje){
	if(mensaje.size() != 0) enviarString(socket, mensaje);
}

void ServidorProxy::recibirMensaje(){
	std::string mensaje;
	
	while(!salir){
		recibirString(socket, mensaje);
		salida -> agregarMensaje(mensaje);
		mensaje.clear();
	}
}

void ServidorProxy::terminar(){
	salir = true;
	hilo_recepcion -> join();
	delete hilo_recepcion;
	socket.cerrar_canal(SHUT_RDWR);
}
#else
ServidorProxy::ServidorProxy(std::string direccion, std::string servicio,
	 DatosPersonaje& datos_personaje, DatosTienda& datos_tienda):
	 datos_personaje(datos_personaje), datos_tienda(datos_tienda){}

void ServidorProxy::enviarMensaje(std::string mensaje){}

void ServidorProxy::recibirMensaje(){}

void ServidorProxy::terminar(){}
#endif