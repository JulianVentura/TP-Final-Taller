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
	std::thread* hilo_recepcion;
	bool salir;
	Socket socket;
	DatosPersonaje& datos_personaje;
	DatosTienda& datos_tienda;
	Protocolo protocolo;
	std::unordered_map<std::string, IPosicionable*> posicionables;
	void actualizarPosiciones();

public:
	ServidorSalida* salida;
	ServidorProxy(DatosPersonaje& datos_personaje, DatosTienda& datos_tienda);
	void conectar(std::string& direccion, std::string& servicio);
	void enviarMensaje(std::string mensaje);
	void recibirMensaje();
	void enviarLogin(std::string nombre, std::string clave);
	void enviarNuevaCuenta(std::string nombre, std::string clave,
		std::string raza, std::string clase);
	void enviarChat(std::string mensaje);
	void terminar();
	std::string obtenerMapa();
	void enviarMovimiento(uint32_t movimiento);
	void agregarPosicionable(std::string& id, IPosicionable* posicionable);
};

#endif /*__SERVIDOR_PROXY_H__*/
