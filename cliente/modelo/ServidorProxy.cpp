#include "ServidorProxy.h"
#include <sys/socket.h>
#include <vector>
#include <utility>
#include <unordered_map>
#include "../controlador/GUI_Chat_Controlador.h"

ServidorProxy::ServidorProxy(DatosPersonaje& datos_personaje,
	DatosTienda& datos_tienda)
	 : datos_personaje(datos_personaje), datos_tienda(datos_tienda) {
	salir = false;
	//
	// TODO: Preguntar si es necesario que esté en el heap
	//
	//protocolo.enviarID(socket, id_usuario);
}

void ServidorProxy::conectar(std::string& direccion, std::string& servicio){
	socket.conectar(direccion.c_str(), servicio.c_str());
	hilo_recepcion = new std::thread(&ServidorProxy::recibirMensaje, this);
}

void ServidorProxy::enviarLogin(std::string nombre, std::string clave){
	uint32_t operacion = CODIGO_ID;
	operacion = htonl(operacion);
	socket.enviar((char*) &operacion, TAM_INT32);
	protocolo.enviarString(socket, nombre);
	protocolo.enviarString(socket, clave);
}

void ServidorProxy::enviarNuevaCuenta(std::string nombre, std::string clave,
		std::string raza, std::string clase){
	uint32_t operacion = CODIGO_NUEVO_PERSONAJE;
	operacion = htonl(operacion);
	socket.enviar((char*) &operacion, TAM_INT32);
	protocolo.enviarString(socket, nombre);
	protocolo.enviarString(socket, clave);
	protocolo.enviarString(socket, raza);
	protocolo.enviarString(socket, clase);
}

void ServidorProxy::enviarMovimiento(uint32_t movimiento) {
	protocolo.enviarMovimiento(socket, movimiento);
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
	protocolo.enviarChat(socket, datos_personaje.id, destino, mensaje);
}

void ServidorProxy::recibirMensaje(){
	uint32_t operacion;
	std::string mensaje;
	bool mensaje_publico;
	while(!salir) {
		socket.recibir((char *)&operacion, TAM_INT32);
		operacion = ntohl(operacion);
		switch (operacion) {
		case CODIGO_CARGA_MAPA:
			protocolo.recibirMapa(socket);
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
