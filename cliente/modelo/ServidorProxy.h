#ifndef __SERVIDOR_PROXY_H__
#define __SERVIDOR_PROXY_H__

#include <string>
#include <thread>

#include "../modelo/DatosPersonaje.h"
#include "../modelo/commonProtocolo.h"
#include "../modelo/commonSocket.h"
#include "../controlador/GUI_Chat_Controlador.h"

//Descomentar para modo offline.
#define OFFLINE

class GUI_ChatControlador;
class ServidorProxy;

class ServidorProxy{
private:
	std::thread* hilo_recepcion;
	bool salir;
	Socket socket;
	DatosPersonaje& datos_personaje;
	GUI_ChatControlador& chat;
public:
	ServidorProxy(std::string direccion, std::string servicio,
	 DatosPersonaje& datos_personaje, GUI_ChatControlador& chat);
	void enviarMensaje(std::string mensaje);
	void recibirMensaje();
	void terminar();
};

#endif /*__SERVIDOR_PROXY_H__*/