#ifndef __ENTORNO_MUSICAL_H__
#define __ENTORNO_MUSICAL_H__

#include <SDL2/SDL.h>
#include <unordered_map>

#include "../lib/audio.h"

class EntornoMusical{
private:
	static EntornoMusical instancia;
	static std::unordered_map<std::string, Audio*> sonidos;
	EntornoMusical();
public:
	static EntornoMusical* obtenerInstancia();
	void reproducirSonido(std::string nombre);
	void reproducirMusica(std::string nombre);
	~EntornoMusical();
};

#endif /*__ENTORNO_MUSICAL_H__*/