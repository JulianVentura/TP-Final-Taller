#include <vector>
#include <mutex>
#include <string>

#include "colaBloqueante.h"
#include "../cliente/modelo/commonProtocolo.h"
#include "../cliente/modelo/commonSocket.h"

class Divulgador{
private:
	std::mutex m;
	ColaBloqueante<std::string> mensajes;
	std::vector<Socket*> suscriptos;
public:
	void operator()();
	void suscribir(Socket& socket);
	void encolarMensaje(std::string mensaje);
};