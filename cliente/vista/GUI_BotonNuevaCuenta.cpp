#include "GUI_BotonNuevaCuenta.h"
#include "../vista/GUI_Login.h"

GUI_BotonNuevaCuenta::GUI_BotonNuevaCuenta(EntornoGrafico& entorno,
 Colores& paleta) : GUI_Boton(entorno, "assets/gui/botonNuevaCuenta.png"){}

void GUI_BotonNuevaCuenta::actualizarDimension(){
	x = X_BASE_LOGIN;
	y = ventana->getAlto() - 45;
	imagen.setPosicion(x, y);
}
