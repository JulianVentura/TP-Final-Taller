#ifndef __SERVIDOR_PROXY_H__
#define __SERVIDOR_PROXY_H__

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <thread>
#include <condition_variable>
#include <arpa/inet.h>

#include "DatosPersonaje.h"
#include "DatosTienda.h"
#include "ServidorSalida.h"
#include "IPosicionable.h"

#include "../../common/ColaBloqueanteMensajes.h"
#include "../../common/Mensaje.h"
#include "../../common/ProxyEnviador.h"
#include "../../common/commonProtocolo.h"
#include "../../common/commonSocket.h"
#include "../../common/CodigosOperacion.h"
#include "../../common/Serializacion.h"

#define TAM_ID 20
#define SALIR_LOGIN_EXITO 1


class Juego;

class GUI_ChatControlador;
class ServidorProxy;

class ServidorProxy{
private:
	std::condition_variable cv;
	ColaBloqueanteMensajes colaEnvio;
	std::mutex mtx;
	std::thread hilo_recepcion;
	bool salir;
	bool se_recibio_mapa;
	bool esta_logueado;
	Socket socket;
	DatosPersonaje& datos_personaje;
	DatosTienda& datos_tienda;
	Protocolo protocolo;
	ProxyEnviador enviador;	
	Juego* juego = nullptr;
	SDL_Event evento_salida;
	void actualizarPosiciones();

public:
	std::string mapa;
	ServidorSalida* salida;
	ServidorProxy(DatosPersonaje& datos_personaje, DatosTienda& datos_tienda);
	~ServidorProxy();

	// Conexion e inicio sesion
	void conectar(std::string& direccion, std::string& servicio);
	void enviarLogin(std::string& nombre, std::string& clave);
	void enviarNuevaCuenta(std::string& nombre, std::string& clave,
						   std::string& raza, std::string& clase);
	void enviarMeditacion();
	bool estaLogueado() const;

	// General
	void recibirMensajeConOperacion(uint32_t operacion);
	void enviarMensaje(std::string mensaje);
	void recibirMensaje();
	void comenzarRecepcionConcurrente();
	void terminar();
	void encolarMensaje(Mensaje&& mensaje);

	// Chat
	void enviarChat(std::string mensaje);

	// Manejo mapa
	std::string obtenerMapa();
	void enviarMovimiento(uint32_t movimiento);
	void recibir_estados();
	
	// Inventario
	void enviarCompra(int pos);
	void enviarUtilizar(int pos);
	void enviarTirar(int pos);
	void enviarTransaccion(bool esDeposito);

	// Interaccion
	void enviarInteraccion(const std::string& id);
	void enviarAtaque(const std::string& id);

	void setJuego(Juego* juego);
};

#endif /*__SERVIDOR_PROXY_H__*/
