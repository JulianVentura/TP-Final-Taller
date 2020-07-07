#ifndef __DIVULGADOR_H__
#define __DIVULGADOR_H__

#include <string>
#include "Thread.h"
#include "colaBloqueante.h"
#include "OrganizadorClientes.h"
#include "Cliente.h"
#include <atomic>
#include <tuple>

#define PALABRA_RESERVADA " "

class OrganizadorClientes;

class Divulgador : public Thread{
private:
	ColaBloqueante<std::tuple<std::string, std::string, std::string>> mensajes;
	OrganizadorClientes& clientes;
	std::atomic<bool> continuar;
public:
	Divulgador(OrganizadorClientes& clientes);
	void procesar();
	void finalizar();
	void encolarMensaje(std::string origen, std::string destino,
	 std::string mensaje);
	void encolarMensaje(std::string destino, std::string mensaje);
};

#endif /*__DIVULGADOR_H__*/