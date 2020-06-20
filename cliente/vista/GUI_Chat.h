#ifndef __GUI_CHAT_H__
#define __GUI_CHAT_H__

#include <SDL2/SDL_render.h>
#include <string>
#include <list>

#include "../vista/EntornoGrafico.h"
#include "../vista/IRendereable.h"
#include "../vista/Colores.h"

#define MENSAJES_TAM_MAX 100
#define MENSAJES_MAX   10
#define ALTO_CARACTER  12
#define ANCHO_CARACTER 10

class GUI_Chat : public IRendereable{
private:
	std::list<std::string> mensajes;
	Colores& paleta;
	SDL_Texture* textura;
	unsigned int caracteres_max;
	void renderizarTexto();
public:
	std::string entrada;
	SDL_Rect marco_mensajes, marco_entrada, marco_textura;
	GUI_Chat(EntornoGrafico& entorno, Colores& paleta);
	void render();
	void actualizarDimension();
	void agregarMensaje(std::string mensaje);
	void scroll(Sint32& incremento);
	~GUI_Chat();
};

#endif /*__GUI_CHAT_H__*/