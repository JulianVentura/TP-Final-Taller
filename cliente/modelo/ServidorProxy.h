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

class GUI_ChatControlador;
class ServidorProxy;

class ServidorProxy{
private:
	std::thread hilo_recepcion;
	bool salir;
	Socket socket;
	std::string& id_usuario;
	DatosPersonaje& datos_personaje;
	DatosTienda& datos_tienda;
	Protocolo protocolo;
	std::unordered_map<std::string, IPosicionable*> posicionables;
	std::string mapa;
	void actualizarPosiciones();

public:
	ServidorSalida* salida;
	ServidorProxy(std::string& direccion, std::string& servicio, std::string& 
		id_usuario, DatosPersonaje& datos_personaje, DatosTienda& datos_tienda);
	void comenzar();
	void enviarMensaje(std::string mensaje);
	void recibirMensaje();
	void recibirMensajeConOperacion(uint32_t operacion);
	void enviarChat(std::string mensaje);
	void terminar();
	void obtenerMapa(std::string& mapa);
	void obtenerMapaInit(std::string& mapa);
	void enviarMovimiento(uint32_t movimiento);
	void agregarPosicionable(std::string& id, IPosicionable* posicionable);
};

#endif /*__SERVIDOR_PROXY_H__*/
