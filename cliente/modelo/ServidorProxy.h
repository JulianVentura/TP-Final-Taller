#ifndef __SERVIDOR_PROXY_H__
#define __SERVIDOR_PROXY_H__

#include <string>
#include <thread>

#include "DatosPersonaje.h"
#include "DatosTienda.h"
#include "ServidorSalida.h"
#include "commonProtocolo.h"
#include "commonSocket.h"
#include "../controlador/GUI_Chat_Controlador.h"

//Descomentar para modo offline.
// #define OFFLINE

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
public:
	ServidorSalida* salida;
	ServidorProxy(std::string direccion, std::string servicio,
	 DatosPersonaje& datos_personaje, DatosTienda& datos_tienda);
	void enviarMensaje(std::string mensaje);
	void recibirMensaje();
	void terminar();
	std::string obtenerMapa();
	std::vector<struct Posicionable> obtenerPosiciones();
	void enviarMovimiento(uint32_t movimiento);

};

#endif /*__SERVIDOR_PROXY_H__*/
