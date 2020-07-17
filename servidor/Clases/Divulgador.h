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
	void encolarMensaje(std::string origen, std::string destino,
	std::string mensaje);
	void encolarMensaje(std::string destino, std::string mensaje);
	static void inicializarInstancia(OrganizadorClientes* clientes);
	static Divulgador* obtenerInstancia();
};

#endif /*__DIVULGADOR_H__*/