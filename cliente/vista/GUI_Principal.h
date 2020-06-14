#ifndef __GUI_PRINCIPAL_H__
#define __GUI_PRINCIPAL_H__

#include <SDL2/SDL_render.h>
#include <vector>
#include "GUI_Barra.h"
#include "EntornoGrafico.h"

class GUI_Principal{
private:
	std::vector<IRendereable*> guis;
public:
	Barra *barra_vida, *barra_mana;
	GUI_Principal(EntornoGrafico& entorno, Ventana& ventana);
	~GUI_Principal();
};

#endif /*__GUI_PRINCIPAL_H__*/