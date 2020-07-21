#include "main_juego.h"

int main_juego(EntornoGrafico& entorno, Ventana& ventana,
	ServidorProxy& servidor, Colores& paleta, DatosPersonaje& datos_personaje,
	DatosTienda& datos_tienda){
	   EntornoMusical::obtenerInstancia() -> reproducirMusica("musicaJuego");
	BuclePrincipal bucle(ventana);
	GUI_Principal gui(entorno, paleta, datos_personaje, datos_tienda);
	GUI_PrincipalControlador gui_controllador(servidor, gui);
	Juego juego(entorno, datos_personaje, servidor);
	ventana.agregarRendereable(&juego);
	ventana.agregarRendereable(&gui);

	bucle.agregarInteractivo(SDL_MOUSEBUTTONDOWN, &gui_controllador);
	bucle.agregarInteractivo(SDL_MOUSEBUTTONDOWN, &juego);
	bucle.agregarInteractivo(SDL_TEXTINPUT, &gui_controllador);
	bucle.agregarInteractivo(SDL_KEYDOWN, &gui_controllador);
	bucle.agregarInteractivo(SDL_KEYDOWN, &juego);
	bucle.agregarInteractivo(SDL_KEYUP, &juego);
	bucle.agregarInteractivo(SDL_WINDOWEVENT, &gui_controllador);
	bucle.agregarInteractivo(SDL_MOUSEWHEEL, &gui_controllador);
	bucle.correr();
	return 0;
}
