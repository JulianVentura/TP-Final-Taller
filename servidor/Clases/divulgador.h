#ifndef __DIVULGADOR_H__
#define __DIVULGADOR_H__

#include <string>

#include "colaBloqueante.h"
#include "OrganizadorClientes.h"

class Divulgador{
private:
	ColaBloqueante<std::string> mensajes;
	OrganizadorClientes& clientes;
public:
	Divulgador(OrganizadorClientes& clientes);
	void operator()();
	void encolarMensaje(std::string mensaje);
};

#endif /*__DIVULGADOR_H__*/