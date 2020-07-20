#ifndef __GUI_BOTON_ORO_CONTROLADOR_H__
#define __GUI_BOTON_ORO_CONTROLADOR_H__

#include "GUI_Boton_Controlador.h"
#include "../vista/GUI_BotonOro.h"
#include "../modelo/ServidorProxy.h"

class GUI_BotonOroControlador final : public GUI_BotonControlador{
private:
	ServidorProxy& servidor;
	bool enClick() override;
public:
	GUI_BotonOroControlador(GUI_BotonOro& vista, ServidorProxy& servidor);
};

#endif /*__GUI_BOTON_ORO_CONTROLADOR_H__*/
