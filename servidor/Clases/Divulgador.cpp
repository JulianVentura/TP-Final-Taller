#include "Divulgador.h"

#include <iostream>

bool Divulgador::instanciaCreada = false;
Divulgador Divulgador::instancia;

Divulgador::Divulgador() : clientes(nullptr),
						   continuar(true){}

void Divulgador::inicializarInstancia(OrganizadorClientes* clientes){
	if (instanciaCreada){
		throw Excepcion
		("Error: Se ha intentado crear una instancia de Divulgador, pero "
		"una ya ha sido creada.");
	}
	instancia.clientes = clientes;
	instanciaCreada = true;
	instancia.comenzar();
}

Divulgador* Divulgador::obtenerInstancia(){
	if (!instanciaCreada){
		throw Excepcion
		("Error: Se ha intentado obtener una instancia de Divulgador, pero "
		"la misma no fue creada.");
	}
	return &instancia;
}

static void _enviarMensaje(std::unique_ptr<Cliente>& cliente, void* mensaje){
	std::pair<std::string, bool>* par_mensaje =
	(std::pair<std::string, bool>*) mensaje; 
	cliente -> enviarMensaje(std::get<0>(*par_mensaje), std::get<1>(*par_mensaje));
}

Divulgador::Divulgador(OrganizadorClientes* clientes) : clientes(clientes),
														continuar(true){
	this->comenzar();
	instanciaCreada = true;
}

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
				origen = clientes->obtenerCliente(std::get<0>(tupla_mensaje));
				mensaje = std::get<0>(tupla_mensaje) + ": " +
						  std::get<2>(tupla_mensaje);
			}else{
				mensaje = std::get<2>(tupla_mensaje);
			}
			if(std::get<1>(tupla_mensaje) != PALABRA_RESERVADA){
				destino = clientes->obtenerCliente(std::get<1>(tupla_mensaje));
				if(std::get<0>(tupla_mensaje) != PALABRA_RESERVADA)
					origen  -> enviarMensaje(mensaje, false);
				destino -> enviarMensaje(mensaje, false);
			}else{
				std::pair<std::string, bool> par_mensaje = 
				std::make_pair(mensaje, true);
				clientes->aplicarFuncion(_enviarMensaje, &par_mensaje);
			}
		}catch (const ColaVacia &e){
			//No quiero reportar un mensaje de cola vacia.
		}catch (const std::exception& e){
			//Si otro tipo de excepcion
			std::cerr << e.what() << std::endl;
		}catch (...){
			std::cerr << "Error desconocido capturado en Divulgador" << std::endl;
		}
	}
}

void Divulgador::encolarMensaje(std::string origen, std::string destino,
	 std::string mensaje){
	mensajes.depositar(std::make_tuple(std::move(origen),
		std::move(destino), std::move(mensaje)));
}

void Divulgador::encolarMensaje(std::string destino, std::string mensaje){
	encolarMensaje(PALABRA_RESERVADA, std::move(destino), std::move(mensaje));
}

void Divulgador::finalizar(){
	continuar = false;
	mensajes.cerrar();
}
