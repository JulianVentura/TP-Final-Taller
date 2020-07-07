#ifndef __SERVIDOR_PROXY_H__
#define __SERVIDOR_PROXY_H__

#include <string>
#include <unordered_map>
#include <thread>
#include <arpa/inet.h>

#include "DatosPersonaje.h"
#include "DatosTienda.h"
#include "ServidorSalida.h"
#include "IPosicionable.h"

#include "../../common/commonProtocolo.h"
#include "../../common/commonSocket.h"
#include "../../common/CodigosOperacion.h"

#define TAM_ID 20

class Juego;

class GUI_ChatControlador;
class ServidorProxy;

class ServidorProxy{
private:
	std::thread hilo_recepcion;
	bool salir;
	Socket socket;
	DatosPersonaje& datos_personaje;
	DatosTienda& datos_tienda;
	Protocolo protocolo;
	Juego* juego;
	std::unordered_map<std::string, IPosicionable*> posicionables;
	std::string mapa;
	void actualizarPosiciones();
public:
	ServidorSalida* salida;
	ServidorProxy(DatosPersonaje& datos_personaje, DatosTienda& datos_tienda);

	// Conexion e inicio sesion
	void conectar(std::string& direccion, std::string& servicio);
	void enviarLogin(std::string& nombre, std::string& clave);
	void enviarNuevaCuenta(std::string& nombre, std::string& clave,
		std::string& raza, std::string& clase);

	// General
	void recibirMensajeConOperacion(uint32_t operacion);
	void enviarMensaje(std::string mensaje);
	void recibirMensaje();
	void comenzar();
	void terminar();

	// Chat
	void enviarChat(std::string mensaje);

	// Manejo mapa
	void obtenerMapaInit(std::string& mapa);
	void enviarMovimiento(uint32_t movimiento);
	void agregarPosicionable(std::string& id, IPosicionable* posicionable);

	// Inventario
	void enviarCompra(int pos);
	void enviarUtilizar(int pos);
	void enviarTirar(int pos);

	// Interaccion
	void enviarInteraccion(std::string& id);
	void enviarAtaque(std::string& id);

	void setJuego(Juego* juego);
};

#endif /*__SERVIDOR_PROXY_H__*/
