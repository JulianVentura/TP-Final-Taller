#ifndef __GUI_BOTON_CONECTAR_H__
#define __GUI_BOTON_CONECTAR_H__

#include "../vista/GUI_Boton.h"

class GUI_BotonConectar final : public GUI_Boton{
public:
	GUI_BotonConectar(EntornoGrafico& entorno, Colores& paleta);
	void actualizarDimension();
	~GUI_BotonConectar();
};

#endif /*__GUI_BOTON_NUEVA_CUENTA_H__*/
