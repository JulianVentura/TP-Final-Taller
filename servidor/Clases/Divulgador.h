#ifndef __DIVULGADOR_H__
#define __DIVULGADOR_H__

#include <string>
#include "Thread.h"
#include "colaBloqueante.h"
#include "OrganizadorClientes.h"
#include <atomic>

class Divulgador : public Thread{
private:
	ColaBloqueante<std::string> mensajes;
	OrganizadorClientes& clientes;
	std::atomic<bool> continuar;
public:
	Divulgador(OrganizadorClientes& clientes);
	void procesar();
	void finalizar();
	void encolarMensaje(std::string mensaje);
};

#endif /*__DIVULGADOR_H__*/