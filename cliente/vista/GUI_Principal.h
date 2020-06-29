#ifndef __GUI_PRINCIPAL_H__
#define __GUI_PRINCIPAL_H__

#include <SDL2/SDL_render.h>
#include <vector>

#include "../modelo/DatosPersonaje.h"
#include "../modelo/DatosTienda.h"
#include "../modelo/ServidorProxy.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/BancoImagenesEquipo.h"
#include "../vista/Colores.h"
#include "../vista/GUI_BotonInventario.h"
#include "../vista/GUI_Oro.h"
#include "../vista/GUI_Dock.h"
#include "../vista/GUI_BarraVida.h"
#include "../vista/GUI_BarraMana.h"
#include "../vista/GUI_BarraExp.h"
#include "../vista/GUI_Chat.h"
#include "../vista/GUI_PanelInventario.h"
#include "../vista/GUI_PanelTienda.h"
#include "../controlador/GUI_BotonInventario_Controlador.h"
#include "../controlador/GUI_Inventario_Controlador.h"
#include "../controlador/GUI_Tienda_Controlador.h"
#include "../controlador/GUI_Chat_Controlador.h"

class GUI_Principal : public IRendereable {
private:
	GUI_Dock dock;
	GUI_BarraVida barra_vida;
	GUI_BarraMana barra_mana;
	GUI_BarraExp barra_exp;
	GUI_Oro oro;
	BancoImagenesEquipo imagenes_equipo;
	GUI_PanelInventario inventario_vista;
	GUI_InventarioControlador inventario_controlador;
	GUI_BotonInventario boton_inventario_vista;
	GUI_BotonInventarioControlador boton_inventario_controlador;
	GUI_PanelTienda tienda_vista;
	GUI_TiendaControlador tienda_controlador;
	GUI_Chat chat_vista;

public:
	GUI_ChatControlador chat_controlador;
	std::vector<GUI_BotonControlador*> botones;
	GUI_Principal(EntornoGrafico& entorno, Colores& paleta,
		DatosPersonaje& datos_personaje, DatosTienda& datos_tienda,
		ServidorProxy& servidor);
	~GUI_Principal();
	void actualizarDimension();
	void render() override;
};

#endif /*__GUI_PRINCIPAL_H__*/
