#ifndef __GUI_BOTON_NUEVA_CUENTA_H__
#define __GUI_BOTON_NUEVA_CUENTA_H__

#include "../vista/GUI_Boton.h"

class GUI_BotonNuevaCuenta final : public GUI_Boton{
public:
	GUI_BotonNuevaCuenta(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
};

#endif /*__GUI_BOTON_NUEVA_CUENTA_H__*/
