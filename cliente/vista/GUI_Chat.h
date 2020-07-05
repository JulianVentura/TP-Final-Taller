#ifndef __GUI_CHAT_H__
#define __GUI_CHAT_H__

#include <SDL2/SDL_render.h>
#include <string>
#include <list>
#include <mutex>
#include <atomic>
#include <utility>

#include "../vista/EntornoGrafico.h"
#include "../vista/IRendereable.h"
#include "../vista/Colores.h"
#include "../vista/GUI_CajaTexto.h"

#define MENSAJES_TAM_MAX 100
#define MENSAJES_MAX   10
#define ALTO_TEXTURA 1000

class GUI_Chat : public GUI_CajaTexto{
private:
	std::mutex m;
	std::atomic<bool> actualizar;
	std::list<std::pair<std::string, bool>> mensajes;
	SDL_Texture* textura = nullptr;
	void renderizarTexto();
public:
	std::string entrada;
	SDL_Rect marco_mensajes, marco_entrada, marco_textura;
	GUI_Chat(EntornoGrafico& entorno, Colores& paleta);
	void render();
	void actualizarDimension();
	void agregarMensaje(std::string mensaje, bool mensaje_publico);
	void scroll(Sint32& incremento);
	~GUI_Chat();
};

#endif /*__GUI_CHAT_H__*/
