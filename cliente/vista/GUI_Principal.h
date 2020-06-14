#ifndef __GUI_PRINCIPAL_H__
#define __GUI_PRINCIPAL_H__

#include <SDL2/SDL_render.h>
#include <vector>
#include "GUI_Barra.h"
#include "EntornoGrafico.h"

class GUI_Principal : public IRendereable {
private:
	std::vector<IRendereable*> guis;
public:
	Barra *barra_vida, *barra_mana;
	GUI_Principal(EntornoGrafico& entorno);
	~GUI_Principal();
	void render() override;
};

#endif /*__GUI_PRINCIPAL_H__*/
