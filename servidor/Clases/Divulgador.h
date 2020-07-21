#ifndef __DIVULGADOR_H__
#define __DIVULGADOR_H__

#include <string>
#include <atomic>
#include <tuple>

#include "../../common/Thread.h"
#include "colaBloqueante.h"
#include "OrganizadorClientes.h"
#include "Cliente.h"


#define PALABRA_RESERVADA " "

class OrganizadorClientes;

class Divulgador : public Thread{
	private:
	ColaBloqueante<std::tuple<std::string, std::string, std::string>> mensajes;
	OrganizadorClientes* clientes;
	std::atomic<bool> continuar;

	protected:
	static Divulgador instancia;
	static bool instanciaCreada;
	Divulgador(OrganizadorClientes* clientes);
	Divulgador();
	
	public:
	void procesar();
	void finalizar();
	/*
	Permite encolar un nuevo mensaje en el cual se especifica un origen y un destinatario.
	*/
	void encolarMensaje(std::string origen, std::string destino,
	std::string mensaje);
	/*
	Permite encolar un nuevo mensaje en el cual se especifica un destinatario y se
	toma como origen al propio servidor.
	*/
	void encolarMensaje(std::string destino, std::string mensaje);
	/*
	Inicializa la instancia del singleton.
	*/
	static void inicializarInstancia(OrganizadorClientes* clientes);
	static Divulgador* obtenerInstancia();
};

#endif /*__DIVULGADOR_H__*/