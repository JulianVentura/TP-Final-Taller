#include "ServidorProxy.h"
#include <bits/stdint-uintn.h>
#include <sys/socket.h>
#include <vector>
#include <utility>
#include <iostream>
#include <unordered_map>
#include "ErrorServidor.h"
#include "../controlador/GUI_Chat_Controlador.h"

#include "Juego.h"

// Conexion e inicio de sesion

ServidorProxy::ServidorProxy(DatosPersonaje& datos_personaje,
	DatosTienda& datos_tienda)
	 : datos_personaje(datos_personaje), datos_tienda(datos_tienda) {
	salir = false;
	se_recibio_mapa = false;
	esta_logueado = false;
	
	Uint32 tipo_evento = SDL_RegisterEvents(1);
	if (tipo_evento != ((Uint32) - 1)) {
		SDL_memset(&evento_salida, 0, sizeof(evento_salida));
		evento_salida.type = tipo_evento;
		evento_salida.user.code = SALIR_LOGIN_EXITO;
	}
}

void ServidorProxy::conectar(std::string& direccion, std::string& servicio){
	socket.conectar(direccion.c_str(), servicio.c_str());
}

void ServidorProxy::enviarLogin(std::string& nombre, std::string& clave){
	protocolo.enviarUint32(socket, CODIGO_ID);
	protocolo.enviarString(socket, nombre);
	protocolo.enviarString(socket, clave);
	datos_personaje.id = nombre;
}

void ServidorProxy::enviarNuevaCuenta(std::string& nombre, std::string& clave,
		std::string& raza, std::string& clase){
	protocolo.enviarUint32(socket, CODIGO_NUEVO_PERSONAJE);
	protocolo.enviarString(socket, nombre);
	protocolo.enviarString(socket, clave);
	protocolo.enviarString(socket, raza);
	protocolo.enviarString(socket, clase);
	datos_personaje.id = nombre;
}

// General

bool ServidorProxy::estaLogueado() const {
	return esta_logueado;
}

void ServidorProxy::recibirMensaje(){
	while(!salir) {
		recibirMensajeConOperacion(protocolo.recibirUint32(socket));
	}
}

void ServidorProxy::recibirMensajeConOperacion(uint32_t operacion) {
	std::string mensaje;
	bool mensaje_publico;

	switch (operacion) {
		case CODIGO_CARGA_MAPA:
		{
			std::unique_lock<std::mutex> lock(mtx);
			protocolo.recibirString(socket, mapa);
			se_recibio_mapa = true;
			cv.notify_all();
		}
		break;
		case CODIGO_POSICIONES:
		this->actualizarPosiciones();	
		break;

		case CODIGO_MENSAJE_CHAT:
		protocolo.recibirString(socket, mensaje);
		socket.recibir((char*) &mensaje_publico, 1);
		salida -> agregarMensaje(mensaje, mensaje_publico);
		break;

		case CODIGO_ERROR:
		protocolo.recibirString(socket, mensaje);
		salida -> agregarMensaje(mensaje, mensaje_publico);
			// throw ErrorServidor("Error de servidor: %s\n", mensaje.c_str());
		break;

		case CODIGO_INVENTARIO:
		for(int i = 0; i < INV_ANCHO*INV_ALTO; i++){
			datos_personaje.inventario[i] = protocolo.recibirUint16(socket);
		}
		datos_personaje.oro = protocolo.recibirUint16(socket);
		break;

		case CODIGO_TIENDA:
		for(int i = 0; i < INV_ANCHO*INV_ALTO; i++){
			datos_tienda.inventario[i] = protocolo.recibirUint16(socket);
			datos_tienda.precios[i] = protocolo.recibirUint16(socket);
		}
		datos_tienda.activo = true;
		break;

		case CODIGO_ESTADISTICAS:
			datos_personaje.vida = protocolo.recibirUint16(socket);
			datos_personaje.vida_max = protocolo.recibirUint16(socket);
			datos_personaje.mana = protocolo.recibirUint16(socket);
			datos_personaje.mana_max = protocolo.recibirUint16(socket);
			datos_personaje.exp = protocolo.recibirUint16(socket);
			datos_personaje.exp_max = protocolo.recibirUint16(socket);
		break;

		case CODIGO_CONFIRMACION:
			esta_logueado = true;
			SDL_PushEvent(&evento_salida);
		break;

		default:
		printf("No reconocido %d\n", operacion);
		break;
	}
}

void ServidorProxy::comenzarRecepcionConcurrente() {
	hilo_recepcion = std::thread(&ServidorProxy::recibirMensaje, this);	
}

void ServidorProxy::terminar() {
	salir = true;
	hilo_recepcion.join();
	socket.cerrar_canal(SHUT_RDWR);
}

// Manejo de mapa

std::string ServidorProxy::obtenerMapa() {
	std::unique_lock<std::mutex> lock(mtx);
	while (!se_recibio_mapa) {
		cv.wait(lock);
	}
	se_recibio_mapa = false;
	return std::move(mapa);
}

void ServidorProxy::actualizarPosiciones() {
	std::unordered_map<std::string, std::pair<int, int>> posiciones;
	uint32_t longitud = protocolo.recibirUint32(socket);
	posiciones.reserve(longitud);
	for (uint32_t i = 0; i < longitud; ++i) {
		std::string id_temp;
		id_temp.resize(TAM_ID);
		socket.recibir(&id_temp[0], TAM_ID);
		id_temp[TAM_ID - 1] = 0;
		float x;
		float y;
		socket.recibir((char *) &x, TAM_INT32);
		x = (float) ntohl(x);
		socket.recibir((char *) &y, TAM_INT32);
		y = (float) ntohl(y);
		std::string id(id_temp.c_str());
		posiciones[id] = { std::round(x), std::round(y) };
	}
	if (!juego) return;
	juego->actualizarPosiciones(std::move(posiciones));
}

void ServidorProxy::agregarPosicionable(std::string& id, 
	IPosicionable* posicionable) {
	posicionables[id] = posicionable;
}

void ServidorProxy::borrarPosicionable(std::string& id) {
	posicionables.erase(id);
}

void ServidorProxy::enviarMovimiento(uint32_t movimiento) {
	protocolo.enviarUint32(socket, CODIGO_MOVIMIENTO);
	protocolo.enviarUint32(socket, movimiento);
}

// Chat

void ServidorProxy::enviarChat(std::string mensaje){
	std::string destino = " ";
	if(mensaje.size() == 0) return;
	if(mensaje.front() == '@'){
		std::size_t pos = mensaje.find_first_of(' ');
		if(pos == std::string::npos) return;
		destino = mensaje.substr(1,pos - 1);
		mensaje = mensaje.substr(pos + 1, std::string::npos);
	}

	protocolo.enviarUint32(socket, CODIGO_MENSAJE_CHAT);
	protocolo.enviarString(socket, datos_personaje.id);
	protocolo.enviarString(socket, destino);
	protocolo.enviarString(socket, mensaje);
}

// Inventario

void ServidorProxy::enviarCompra(int pos){
	protocolo.enviarUint32(socket, CODIGO_COMPRA);
	protocolo.enviarString(socket, datos_tienda.id_vendedor);
	protocolo.enviarUint16(socket, pos);
}

void ServidorProxy::enviarTirar(int pos){
	if(datos_tienda.activo){
		protocolo.enviarUint32(socket, CODIGO_VENTA);
		protocolo.enviarString(socket, datos_tienda.id_vendedor);
		protocolo.enviarUint16(socket, pos);
	}else{
		protocolo.enviarUint32(socket, CODIGO_TIRADO);
		protocolo.enviarUint16(socket, pos);
	}
}

void ServidorProxy::enviarUtilizar(int pos){
	protocolo.enviarUint32(socket, CODIGO_UTILIZACION);
	protocolo.enviarUint16(socket, pos);
}

//Interaccion

void ServidorProxy::enviarAtaque(const std::string& id){
	protocolo.enviarUint32(socket, CODIGO_ATAQUE);
	protocolo.enviarString(socket, id);
}

void ServidorProxy::enviarInteraccion(const std::string& id){
	datos_tienda.id_vendedor = id;
	protocolo.enviarUint32(socket, CODIGO_INTERACCION);
	protocolo.enviarString(socket, id);
}

void ServidorProxy::setJuego(Juego* juego) {
	this->juego = juego;
}
