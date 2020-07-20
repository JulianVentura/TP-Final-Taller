#include "GUI_BotonConectar.h"
#include "../vista/GUI_Login.h"

GUI_BotonConectar::GUI_BotonConectar(EntornoGrafico& entorno,
 Colores& paleta) : GUI_Boton(entorno, "assets/gui/botonConectar.png"){}

void GUI_BotonConectar::actualizarDimension(){
	x = X_BASE_LOGIN;
	y = Y_BASE_LOGIN + 120;
	imagen.setPosicion(x, y);
}

GUI_BotonConectar::~GUI_BotonConectar(){}