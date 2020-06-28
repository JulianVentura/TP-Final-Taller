#include "divulgador.h"
#include <iostream>

void Divulgador::operator()(){
	std::string mensaje;
	while(true){
		mensaje = mensajes.retirar();
		m.lock();
		for(Socket* suscrito : suscriptos){
			try{
				enviarString(*suscrito, mensaje);
			}catch(std::exception& e){
				std::cerr << "Problema al enviar";
			}
			
		}
		m.unlock();
	}
	
}

void Divulgador::suscribir(Socket& socket){
	std::lock_guard<std::mutex> lock(m);
	suscriptos.push_back(&socket);
}

void Divulgador::encolarMensaje(std::string mensaje){
	//std::lock_guard<std::mutex> lock(m);
	mensajes.depositar(std::move(mensaje));
}

