#include <vector>

#include "GUI_Login.h"
#include "GUI_Barra.h"
#include "EntornoGrafico.h"
#include "Renderer.h"
#include "Ventana.h"

#include "../modelo/BucleLogin.h"

GUI_Login::GUI_Login(EntornoGrafico& entorno, Colores& paleta,
	ServidorProxy& servidor):
	entrada_sup_vista(entorno, paleta),
	entrada_inf_vista(entorno, paleta),
	entrada_sup(entrada_sup_vista),
	entrada_inf(entrada_inf_vista),
	salida(entorno, paleta),
	boton_conectar_vista(entorno, paleta),
	boton_login_vista(entorno, paleta),
	boton_nueva_cuenta_vista(entorno, paleta),
	boton_conectar(boton_conectar_vista, servidor, salida,
	 entrada_sup_vista.entrada, entrada_inf_vista.entrada, conectado),
	boton_login(boton_login_vista, servidor, salida,
	 entrada_sup_vista.entrada, entrada_inf_vista.entrada, conectado),
	selector_raza_vista(entorno, paleta),
	selector_raza(selector_raza_vista),
	selector_clase_vista(entorno, paleta),
	selector_clase(selector_clase_vista),
	boton_nueva_cuenta(boton_nueva_cuenta_vista, servidor, salida,
	 entrada_sup_vista.entrada, entrada_inf_vista.entrada,
	 selector_raza.i, selector_clase.i, conectado),
	fondo(entorno, paleta, conectado){
	entorno.agregarRendereable(this);
	conectado = false;

	botones.push_back(&entrada_sup);
	botones.push_back(&entrada_inf);
	botones.push_back(&boton_conectar);
	botones.push_back(&boton_login);
	botones.push_back(&boton_nueva_cuenta);
	botones.push_back(&selector_raza);
	botones.push_back(&selector_clase);

	servidor.salida = &salida;
	actualizarDimension();
}

void GUI_Login::render() {
		fondo.render();

		entrada_sup_vista.render();
		entrada_inf_vista.render();

		if(conectado){
			boton_login_vista.render();
			boton_nueva_cuenta_vista.render();
			selector_clase_vista.render();
			selector_raza_vista.render();
		}else{
			boton_conectar_vista.render();
		}

		salida.render();
}

void GUI_Login::actualizarDimension(){
	int ventana_ancho  = ventana -> getAncho();
	int ventana_alto = ventana -> getAlto();

	//Cuadros entrada
	entrada_sup_vista.marco_entrada.x = ventana_ancho*0.1;
	entrada_sup_vista.marco_entrada.y = ventana_alto*0.2 + 20;
	entrada_sup_vista.marco_entrada.h = 16;
	entrada_sup_vista.marco_entrada.w = ventana_ancho*0.2;
	entrada_inf_vista.marco_entrada = entrada_sup_vista.marco_entrada;
	entrada_inf_vista.marco_entrada.y += 56;
	entrada_sup_vista.actualizarDimension();
	entrada_inf_vista.actualizarDimension(); 
	entrada_sup.actualizarDimension();
	entrada_inf.actualizarDimension();

	selector_clase_vista.actualizarDimension();
	selector_raza_vista.actualizarDimension();
	selector_raza.actualizarDimension();
	selector_clase.actualizarDimension();

	boton_login_vista.actualizarDimension();
	boton_conectar_vista.actualizarDimension();
	boton_nueva_cuenta_vista.actualizarDimension();	
	boton_login.actualizarDimension();
	boton_conectar.actualizarDimension();
	boton_nueva_cuenta.actualizarDimension();
}

void GUI_Login::manejarEvento(SDL_Event& evento){
	entrada_sup.manejarEvento(evento);
	entrada_inf.manejarEvento(evento);
} 

GUI_Login::~GUI_Login(){}
