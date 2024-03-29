#ifndef __GUI_PRINCIPAL_CONTROLADOR_H__
#define __GUI_PRINCIPAL_CONTROLADOR_H__

#include "../controlador/GUI_Clickeable.h"
#include "../controlador/GUI_BotonInventario_Controlador.h"
#include "../controlador/GUI_BotonMeditar_Controlador.h"
#include "../controlador/GUI_BotonResucitar_Controlador.h"
#include "../controlador/GUI_BotonOro_Controlador.h"
#include "../controlador/GUI_Inventario_Controlador.h"
#include "../controlador/GUI_Chat_Controlador.h"
#include "../controlador/GUI_Tienda_Controlador.h"
#include "../controlador/IInteractivo.h"

/*
*	Clase que reune los controladores de la interfaz involucrados en
*	la ejecución normal del juego. Permite explicitar la prioridad
*	con la que se manejan los eventos.
*	Cuando un componente puede responder a un evento, lo consume y éste
*	no alcanza al resto.
*/

class GUI_Principal;

class GUI_PrincipalControlador: public IInteractivo {
public:
    GUI_PrincipalControlador(ServidorProxy& servidor,
        GUI_Principal& vista_principal);
    bool manejarEvento(SDL_Event& evento) override;

private:
	std::vector<GUI_Clickeable*> botones;
	GUI_Principal& vista_principal; 
	GUI_InventarioControlador inventario_controlador;
	GUI_BotonInventarioControlador boton_inventario_controlador;
	GUI_BotonMeditarControlador boton_meditar_controlador;
	GUI_BotonResucitarControlador boton_resucitar_controlador;
	GUI_BotonOroControlador boton_oro_controlador;
	GUI_TiendaControlador tienda_controlador;
	GUI_ChatControlador chat_controlador;
};

#endif /* __GUI_PRINCIPAL_CONTROLADOR_H__ */
