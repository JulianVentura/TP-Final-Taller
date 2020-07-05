#ifndef __GUI_LOGIN_H__
#define __GUI_LOGIN_H__

#include <SDL2/SDL_render.h>
#include <vector>
#include <string>

#include "../modelo/ServidorProxy.h"
#include "../controlador/GUI_Boton_Controlador.h"
#include "../controlador/GUI_CajaTexto_Controlador.h"
#include "../controlador/GUI_BotonConectar_Controlador.h"
#include "../controlador/GUI_BotonLogin_Controlador.h"
#include "../controlador/GUI_BotonNuevaCuenta_Controlador.h"
#include "../controlador/GUI_SelectorLista_Controlador.h"
#include "../controlador/GUI_SelectorClase_Controlador.h"
#include "../controlador/GUI_SelectorRaza_Controlador.h"
#include "../vista/Colores.h"
#include "../vista/IRendereable.h"
#include "../vista/ServidorSalidaAlerta.h"
#include "../vista/LoginFondo.h"
#include "../vista/GUI_CajaTexto.h"
#include "../vista/GUI_BotonConectar.h"
#include "../vista/GUI_BotonLogin.h"
#include "../vista/GUI_BotonNuevaCuenta.h"
#include "../vista/GUI_SelectorLista.h"
#include "../vista/GUI_SelectorClase.h"
#include "../vista/GUI_SelectorRaza.h"

class GUI_BotonNuevaCuenta;

class GUI_Login : public IRendereable {
private:
	bool conectado;
	GUI_CajaTexto entrada_sup_vista, entrada_inf_vista;
	GUI_CajaTextoControlador entrada_sup, entrada_inf;
	ServidorSalidaAlerta salida;
	GUI_BotonConectar    boton_conectar_vista;
	GUI_BotonLogin       boton_login_vista;
	GUI_BotonNuevaCuenta boton_nueva_cuenta_vista;
	GUI_BotonConectarControlador    boton_conectar;
	GUI_BotonLoginControlador       boton_login;
	GUI_SelectorRaza  selector_raza_vista;
	GUI_SelectorRazaControlador selector_raza;
	GUI_SelectorClase  selector_clase_vista;
	GUI_SelectorClaseControlador selector_clase;
	GUI_BotonNuevaCuentaControlador boton_nueva_cuenta;
	LoginFondo fondo;
public:
	std::vector<GUI_BotonControlador*> botones;
	GUI_Login(EntornoGrafico& entorno, Colores& paleta,
		ServidorProxy& servidor);
	~GUI_Login();
	void manejarEvento(SDL_Event& evento);
	void actualizarDimension();
	void render() override;
};


#endif /*__GUI_LOGIN_H__*/