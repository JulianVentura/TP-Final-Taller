#include "Divulgador.h"

static void _enviarMensaje(std::unique_ptr<Cliente>& cliente, void* mensaje){
	cliente -> enviarMensaje(*((std::string*) mensaje));
}

Divulgador::Divulgador(OrganizadorClientes& clientes) : clientes(clientes),
														continuar(true){}

void Divulgador::procesar(){
	std::string mensaje;
	Cliente* destinatario;
	while(continuar){
		try{
			mensaje = mensajes.retirar();
			if(!mensaje.size()) continue;
			if(mensaje.front() != '@'){
				clientes.aplicarFuncion(_enviarMensaje, &mensaje);
			}else{
				unsigned int pos = mensaje.find_first_of(' ');
				if(pos == std::string::npos) continue;
				destinatario = clientes.obtenerCliente(
					mensaje.substr(0,pos - 1));
				destinatario -> enviarMensaje(
					mensaje.substr(pos + 1, std::string::npos));
				}
		}catch(std::exception& e){
			continue;
		}
	}
}

void Divulgador::encolarMensaje(std::string mensaje){
	mensajes.depositar(std::move(mensaje));
}

void Divulgador::finalizar(){
	continuar = false;
	mensajes.cerrar();
}
