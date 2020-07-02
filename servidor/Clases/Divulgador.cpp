#include "Divulgador.h"

#include <iostream>

static void _enviarMensaje(std::unique_ptr<Cliente>& cliente, void* mensaje){
	std::pair<std::string, bool>* par_mensaje =
	(std::pair<std::string, bool>*) mensaje; 
	cliente -> enviarChat(std::get<0>(*par_mensaje), std::get<1>(*par_mensaje));
}

Divulgador::Divulgador(OrganizadorClientes& clientes) : clientes(clientes),
														continuar(true){}

void Divulgador::procesar(){
	//En orden: origen, destino y mensaje.
	std::tuple<std::string, std::string, std::string> tupla_mensaje;
	std::string mensaje;
	Cliente *origen = nullptr;
	Cliente *destino = nullptr;
	while(continuar){
		try{
			tupla_mensaje = mensajes.retirar();
			if(std::get<0>(tupla_mensaje) != PALABRA_RESERVADA){
				origen = clientes.obtenerCliente(std::get<0>(tupla_mensaje));
				mensaje = std::get<0>(tupla_mensaje) + ": " +
						  std::get<2>(tupla_mensaje);
			}else{
				mensaje = std::get<2>(tupla_mensaje);
			}
			
			if(std::get<1>(tupla_mensaje) != PALABRA_RESERVADA){
				destino = clientes.obtenerCliente(std::get<1>(tupla_mensaje));
				if(std::get<0>(tupla_mensaje) != PALABRA_RESERVADA)
					origen  -> enviarChat(mensaje, false);
				destino -> enviarChat(mensaje, false);
			}else{
				std::pair<std::string, bool> par_mensaje = 
				std::make_pair(mensaje, true);
				clientes.aplicarFuncion(_enviarMensaje, &par_mensaje);
			}
		}catch(std::exception& e){
			std::cerr << "No se encontro Cliente";
			continue;
		}
	}
}

void Divulgador::encolarMensaje(std::string origen, std::string destino,
	 std::string mensaje){
	mensajes.depositar(std::make_tuple(std::move(origen),
		std::move(destino), std::move(mensaje)));
}

void Divulgador::finalizar(){
	continuar = false;
	mensajes.cerrar();
}
