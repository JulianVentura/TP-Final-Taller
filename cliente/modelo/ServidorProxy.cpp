#include "ServidorProxy.h"
#include <bits/stdint-uintn.h>
#include <sys/socket.h>
#include <vector>
#include <utility>
#include <unordered_map>
#include "ErrorServidor.h"
#include "../controlador/GUI_Chat_Controlador.h"

#ifndef OFFLINE
ServidorProxy::ServidorProxy(std::string& direccion, std::string& servicio, 
		std::string& id_usuario, DatosPersonaje& datos_personaje, DatosTienda& 
		datos_tienda): id_usuario(id_usuario), datos_personaje(datos_personaje), 
		datos_tienda(datos_tienda) {
	salir = false;
	socket.conectar(direccion.c_str(), servicio.c_str());
	protocolo.enviarID(socket, id_usuario);
}

void ServidorProxy::enviarMovimiento(uint32_t movimiento) {
	protocolo.enviarMovimiento(socket, movimiento);
}

void ServidorProxy::comenzar() {
	hilo_recepcion = std::thread(&ServidorProxy::recibirMensaje, this);	
}

void ServidorProxy::enviarChat(std::string mensaje){
	std::string destino = " ";
	if(mensaje.size() == 0) return;
	if(mensaje.front() == '@'){
		std::size_t pos = mensaje.find_first_of(' ');
		if(pos == std::string::npos) return;
		destino = mensaje.substr(1,pos - 1);
		mensaje = mensaje.substr(pos + 1, std::string::npos);
	}

	protocolo.enviarChat(socket, id_usuario, destino, mensaje);
}

void ServidorProxy::recibirMensaje(){
	uint32_t operacion;
	while(!salir) {
		socket.recibir((char *)&operacion, TAM_INT32);
		operacion = ntohl(operacion);
		
		recibirMensajeConOperacion(operacion);
	}
}

void ServidorProxy::recibirMensajeConOperacion(uint32_t operacion) {
	std::string mensaje;
	bool mensaje_publico;

	switch (operacion) {
		case CODIGO_CARGA_MAPA:
			protocolo.recibirMapa(socket, mapa);

			break;
		case CODIGO_POSICIONES:
			this->actualizarPosiciones();	
			break;
		case CODIGO_MENSAJE_CHAT:
			protocolo.recibirChat(socket, mensaje, mensaje_publico);
			salida -> agregarMensaje(mensaje, mensaje_publico);
			break;
		case CODIGO_ERROR:
			protocolo.recibirString(socket, mensaje);
			throw ErrorServidor("Error de servidor: %s\n", mensaje.c_str());
			break;
		default:
			printf("No reconocido %d\n", operacion);
			break;
	}
}
void ServidorProxy::terminar() {
	salir = true;
	hilo_recepcion.join();
	socket.cerrar_canal(SHUT_RDWR);
}

void ServidorProxy::obtenerMapaInit(std::string& mapa) {
	uint32_t operacion;
	socket.recibir((char *)&operacion, TAM_INT32);
	operacion = ntohl(operacion);
	if (operacion != CODIGO_CARGA_MAPA) {
		recibirMensajeConOperacion(operacion);
		return;
	}

	protocolo.recibirMapa(socket, mapa);
	this->mapa = mapa;
}

void ServidorProxy::obtenerMapa(std::string& mapa) {
	protocolo.recibirMapa(socket, mapa);
	this->mapa = mapa;
}

void ServidorProxy::actualizarPosiciones() {
	std::unordered_map<std::string, std::pair<int, int>> posiciones;
	protocolo.recibirPosiciones(socket, posiciones);
	for (auto& posicion: posiciones) {
		if (posicionables.count(posicion.first) == 0) continue;
		auto& coordenadas = posicion.second;
		
		posicionables[posicion.first]->actualizarPosicion(coordenadas.first, 
															coordenadas.second);
	}
}

void ServidorProxy::agregarPosicionable(std::string& id, 
												IPosicionable* posicionable) {
	posicionables[id] = posicionable;
}

#else
ServidorProxy::ServidorProxy(std::string direccion, std::string servicio,
	 DatosPersonaje& datos_personaje, DatosTienda& datos_tienda):
	 datos_personaje(datos_personaje), datos_tienda(datos_tienda){}

void ServidorProxy::terminar(){}
#endif
