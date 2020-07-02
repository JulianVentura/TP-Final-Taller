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

void ServidorProxy::enviarMovimiento(uint32_t movimiento) {
	protocolo.enviarMovimiento(socket, movimiento);
}

void ServidorProxy::enviarChat(std::string mensaje){
	std::string destino = " ";
	if(mensaje.size() == 0) return;
	if(mensaje.front() == '@'){
		unsigned int pos = mensaje.find_first_of(' ');
		if(pos == std::string::npos) return;
		destino = mensaje.substr(1,pos - 1);
		mensaje = mensaje.substr(pos + 1, std::string::npos);
	}

	std::string id("personaje1"); // TODO: harcodeado
	protocolo.enviarChat(socket, id, destino, mensaje);
}

void ServidorProxy::recibirMensaje(){
	uint32_t operacion;
	std::string mensaje;
	bool mensaje_publico;
	while(!salir){
		socket.recibir((char *)&operacion, TAM_INT32);
		operacion = ntohl(operacion);
		switch (operacion) {
			case CODIGO_CARGA_MAPA:
			protocolo.recibirMapa(socket);
			break;

			case CODIGO_POSICIONES:
			protocolo.recibirPosiciones(socket);

			break;
			case CODIGO_MENSAJE_CHAT:
			protocolo.recibirChat(socket, mensaje, mensaje_publico);
			salida -> agregarMensaje(mensaje, mensaje_publico);
			break;
		default:
		printf("No reconocido %d\n", operacion);
		break;
		}
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
	return protocolo.obtenerPosiciones();
}
#else
ServidorProxy::ServidorProxy(std::string direccion, std::string servicio,
	 DatosPersonaje& datos_personaje, DatosTienda& datos_tienda):
	 datos_personaje(datos_personaje), datos_tienda(datos_tienda){}

void ServidorProxy::terminar(){}
#endif