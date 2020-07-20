#include "GUI_BotonLogin.h"
#include "../vista/GUI_Login.h"

GUI_BotonLogin::GUI_BotonLogin(EntornoGrafico& entorno,
 Colores& paleta) : GUI_Boton(entorno, "assets/gui/botonLogin.png"){}

void GUI_BotonLogin::actualizarDimension(){
	x = X_BASE_LOGIN;
	y = ventana->getAlto() - 90;
	imagen.setPosicion(x, y);
}
