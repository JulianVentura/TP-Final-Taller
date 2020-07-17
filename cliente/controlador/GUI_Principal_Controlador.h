#ifndef __GUI_PRINCIPAL_CONTROLADOR_H__
#define __GUI_PRINCIPAL_CONTROLADOR_H__

#include "../controlador/GUI_BotonInventario_Controlador.h"
#include "../controlador/GUI_BotonMeditar_Controlador.h"
#include "../controlador/GUI_BotonOro_Controlador.h"
#include "../controlador/GUI_Inventario_Controlador.h"
#include "../controlador/GUI_Chat_Controlador.h"
#include "../controlador/GUI_Tienda_Controlador.h"
#include "../controlador/IInteractivo.h"

class GUI_Principal;

class GUI_PrincipalControlador: public IInteractivo {
public:
    GUI_PrincipalControlador(ServidorProxy& servidor,
        GUI_Principal& vista_principal);
    bool manejarEvento(SDL_Event& evento) override;

private:
	std::vector<GUI_BotonControlador*> botones;
	GUI_Principal& vista_principal; 
	GUI_InventarioControlador inventario_controlador;
	GUI_BotonInventarioControlador boton_inventario_controlador;
	GUI_BotonMeditarControlador boton_meditar_controlador;
	GUI_BotonOroControlador boton_oro_controlador;
	GUI_TiendaControlador tienda_controlador;
	GUI_ChatControlador chat_controlador;
};

#endif /* __GUI_PRINCIPAL_CONTROLADOR_H__ */
