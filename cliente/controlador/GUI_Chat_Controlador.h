#include <SDL2/SDL.h>
#include "../vista/GUI_Chat.h"
#include "../controlador/GUI_Boton_Controlador.h"

class GUI_ChatControlador : public GUI_BotonControlador{
private:
	GUI_Chat& chat_vista;

public:
	explicit GUI_ChatControlador(GUI_Chat& vista);
	void ingresarCaracter(SDL_Event& evento);
	void scroll(SDL_Event& evento);
	bool operator()(SDL_Event& evento) override;
	bool enClick();
	void actualizarDimension();
};
