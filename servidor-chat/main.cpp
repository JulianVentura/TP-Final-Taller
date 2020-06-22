#include <thread>
#include <iostream>

#include "../cliente/modelo/commonSocket.h"
#include "Divulgador.h"

void _recibirMensaje(Socket& socket, Divulgador& divulgador){
	std::string mensaje;
	while(true){
		try {
		recibirString(socket, mensaje);
		divulgador.encolarMensaje(mensaje);
		}catch(std::exception& e){
			std::cerr << "Problema al recbir";
		}
	}
}

int main(int argc, char const *argv[])
{
	std::thread hilo;
	std::vector<std::thread> hilos;
	Socket socket_aceptador;
	socket_aceptador.ligar("80");
	socket_aceptador.escuchar(10);
	Socket socket1, socket2;
	Socket socket3;
	Divulgador divulgador;
	hilo = std::thread(&Divulgador::operator(), &divulgador);

	socket1 = std::move(socket_aceptador.aceptar());
	socket2 = std::move(socket_aceptador.aceptar());
	socket3 = std::move(socket_aceptador.aceptar());

	divulgador.suscribir(socket1);
	divulgador.suscribir(socket2);
	divulgador.suscribir(socket3);

	hilos.emplace_back(_recibirMensaje, std::ref(socket1),
		 std::ref(divulgador));

	hilos.emplace_back(_recibirMensaje, std::ref(socket2),
		 std::ref(divulgador));

	hilos.emplace_back(_recibirMensaje, std::ref(socket3),
		 std::ref(divulgador));

	socket_aceptador.aceptar();
	return 0;
}