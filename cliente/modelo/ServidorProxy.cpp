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
	 : datos_personaje(datos_personaje), datos_tienda(datos_tienda),
	  enviador(socket, colaEnvio) {
	salir = false;
	se_recibio_mapa = false;
	esta_logueado = false;
	comenzo_recepcion_concurrente = false;
	Uint32 tipo_evento = SDL_RegisterEvents(1);
	if (tipo_evento != ((Uint32) - 1)) {
		SDL_memset(&evento_salida, 0, sizeof(evento_salida));
		evento_salida.type = tipo_evento;
		evento_salida.user.code = SALIR_LOGIN_EXITO;
	}
	enviador.comenzar();
}

ServidorProxy::~ServidorProxy(){
	socket.cerrar_canal(SHUT_RDWR);
	colaEnvio.cerrarCola();
	enviador.recuperar();
}

void ServidorProxy::conectar(std::string& direccion, std::string& servicio){
	socket.conectar(direccion.c_str(), servicio.c_str());
}

void ServidorProxy::enviarLogin(std::string& nombre, std::string& clave){
	protocolo.enviarUint32(socket, CODIGO_ID);
	protocolo.enviarString(socket, nombre);
	protocolo.enviarString(socket, clave);
	encolarMensaje(std::move(protocolo.finalizarEnvio()));
	datos_personaje.id = nombre;
}

void ServidorProxy::enviarNuevaCuenta(std::string& nombre, std::string& clave,
		std::string& raza, std::string& clase){
	protocolo.enviarUint32(socket, CODIGO_NUEVO_PERSONAJE);
	protocolo.enviarString(socket, nombre);
	protocolo.enviarString(socket, clave);
	protocolo.enviarString(socket, raza);
	protocolo.enviarString(socket, clase);
	encolarMensaje(std::move(protocolo.finalizarEnvio()));
	datos_personaje.id = nombre;
}

// General

bool ServidorProxy::estaLogueado() const {
	return esta_logueado;
}

void ServidorProxy::recibirMensaje(){
	try{
		while(!salir) {
			recibirMensajeConOperacion(protocolo.recibirUint32(socket));
		}
	}catch(std::exception& e){
		SDL_PushEvent(&evento_salida);
	}
}

void ServidorProxy::recibirMensajeConOperacion(uint32_t operacion) {
	std::string mensaje;
	bool mensaje_publico;

	switch (operacion) {
		case CODIGO_POSICIONES:
		this->actualizarPosiciones();	
		break;
		
		case CODIGO_ESTADOS:
			recibir_estados();
		break;

		case CODIGO_MENSAJE_CHAT:
		protocolo.recibirString(socket, mensaje);
		socket.recibir((char*) &mensaje_publico, 1);
		salida -> agregarMensaje(mensaje, mensaje_publico);
		break;

		case CODIGO_ESTADISTICAS:
			datos_personaje.vida = protocolo.recibirUint16(socket);
			datos_personaje.vida_max = protocolo.recibirUint16(socket);
			datos_personaje.mana = protocolo.recibirUint16(socket);
			datos_personaje.mana_max = protocolo.recibirUint16(socket);
			datos_personaje.exp = protocolo.recibirUint16(socket);
			datos_personaje.exp_max = protocolo.recibirUint16(socket);
			{
			uint16_t exp_min = protocolo.recibirUint16(socket);
			datos_personaje.exp -= exp_min;
			datos_personaje.exp_max -= exp_min;
			}
			datos_personaje.nivel = protocolo.recibirUint32(socket);
		break;
		
		case CODIGO_ERROR:
		protocolo.recibirString(socket, mensaje);
		salida -> agregarMensaje(mensaje, mensaje_publico);
		break;

		case CODIGO_INVENTARIO:
		for(int i = 0; i < ESPACIOS_EQUIPO; i++){
			datos_personaje.equipados[i] = protocolo.recibirUint16(socket);
		}
		for(int i = 0; i < INV_ANCHO*INV_ALTO; i++){
			datos_personaje.inventario[i] = protocolo.recibirUint16(socket);
		}
		datos_personaje.oro = protocolo.recibirUint16(socket);
		break;

		case CODIGO_TIENDA:
		datos_tienda.oro_almacenado = protocolo.recibirUint16(socket);
		for(int i = 0; i < INV_ANCHO*INV_ALTO; i++){
			datos_tienda.inventario[i] = protocolo.recibirUint16(socket);
			datos_tienda.precios[i] = protocolo.recibirUint16(socket);
		}
		datos_tienda.activo = true;
		break;

		case CODIGO_CARGA_MAPA:
		{
			std::unique_lock<std::mutex> lock(mtx);
			protocolo.recibirString(socket, mapa);
			if (juego) juego->cambiarMapa(mapa);
			se_recibio_mapa = true;
			cv.notify_all();
		}
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
	comenzo_recepcion_concurrente = true;
}
void ServidorProxy::terminarJuego() {
	std::unique_lock<std::mutex> lock(mtx);
	juego = nullptr;
}
void ServidorProxy::terminar() {
	salir = true;
	socket.cerrar_canal(SHUT_RDWR);
	if (comenzo_recepcion_concurrente)
		hilo_recepcion.join();
}

// Manejo de mapa

std::string ServidorProxy::obtenerMapa() {
	std::unique_lock<std::mutex> lock(mtx);
	while (!se_recibio_mapa) cv.wait(lock);
	se_recibio_mapa = false;
	return std::move(mapa);
}

void ServidorProxy::actualizarPosiciones() {
	std::unordered_map<std::string, std::pair<int, int>> posiciones;
	uint32_t longitud = protocolo.recibirUint32(socket);
	posiciones.reserve(longitud);
	for (uint32_t i = 0; i < longitud; ++i) {
		std::string id;
		protocolo.recibirString(socket, id);
		posiciones[id] = { protocolo.recibirUint32(socket),
						   protocolo.recibirUint32(socket)};
	}
	std::unique_lock<std::mutex> lock(mtx);
	if (!juego) return;
	juego->actualizarPosiciones((posiciones));
}

void ServidorProxy::enviarMovimiento(uint32_t movimiento) {
	protocolo.enviarUint32(socket, CODIGO_MOVIMIENTO);
	protocolo.enviarUint32(socket, movimiento);
	encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ServidorProxy::recibir_estados() {
	uint32_t largo = protocolo.recibirUint32(socket);
	std::vector<serializacionDibujado> resultado;
	for (std::size_t i = 0; i < largo; i++) {
		serializacionDibujado actual;
		std::string id;
		protocolo.recibirString(socket, id);
		std::strncpy(actual.id, id.c_str(), id.length() + 1);
        actual.idArmaEquipada = protocolo.recibirUint16(socket);
		actual.idArmaduraEquipada = protocolo.recibirUint16(socket);
		actual.idCascoEquipado = protocolo.recibirUint16(socket);
		actual.idEscudoEquipado = protocolo.recibirUint16(socket);
		actual.idRaza = protocolo.recibirUint16(socket);
		actual.idClase = protocolo.recibirUint16(socket);
		actual.idEstado = protocolo.recibirUint16(socket);
		resultado.push_back(std::move(actual));
	}
	std::unique_lock<std::mutex> lock(mtx);
	if (!juego) return;
	juego->actualizarEstados((resultado));
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
	encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

// Inventario

void ServidorProxy::enviarCompra(int pos){
	if(!datos_tienda.activo) return;
	protocolo.enviarUint32(socket, CODIGO_COMPRA);
	protocolo.enviarString(socket, datos_tienda.id_vendedor);
	protocolo.enviarUint16(socket, pos);
	encolarMensaje(std::move(protocolo.finalizarEnvio()));
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
	encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ServidorProxy::enviarUtilizar(int pos){
	protocolo.enviarUint32(socket, CODIGO_UTILIZACION);
	protocolo.enviarUint16(socket, pos);
	encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ServidorProxy::enviarTransaccion(bool esDeposito){
	if(!datos_tienda.activo) return;
	protocolo.enviarUint32(socket, CODIGO_TRANSACCION);
	protocolo.enviarUint8(socket, esDeposito);
	protocolo.enviarString(socket, datos_tienda.id_vendedor);
	encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

//Interaccion

void ServidorProxy::enviarAtaque(const std::string& id){
	protocolo.enviarUint32(socket, CODIGO_ATAQUE);
	protocolo.enviarString(socket, id);
	encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ServidorProxy::enviarInteraccion(const std::string& id){
	datos_tienda.id_vendedor = id;
	protocolo.enviarUint32(socket, CODIGO_INTERACCION);
	protocolo.enviarString(socket, id);
	encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ServidorProxy::enviarMeditacion(){
	protocolo.enviarUint32(socket, CODIGO_MEDITACION);
	encolarMensaje(std::move(protocolo.finalizarEnvio()));
}

void ServidorProxy::enviarResucitacion(){
	protocolo.enviarUint32(socket, CODIGO_RESUCITACION);
	encolarMensaje(std::move(protocolo.finalizarEnvio()));
}


void ServidorProxy::setJuego(Juego* juego) {
	std::unique_lock<std::mutex> lock(mtx);
	this->juego = juego;
}

void ServidorProxy::encolarMensaje(Mensaje&& mensaje){
	if(enviador.envioBloqueado()){
		SDL_PushEvent(&evento_salida);
	}else{
		colaEnvio.push(std::move(mensaje));
	}
}
