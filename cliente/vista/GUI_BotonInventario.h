#ifndef __GUI_BOTON_INVENTARIO_H__
#define __GUI_BOTON_INVENTARIO_H__

#include <atomic>

#include "../modelo/DatosPersonaje.h"
#include "../vista/BancoImagenesEquipo.h"
#include "../vista/IRendereable.h"
#include "../vista/Imagen.h"
#include "../vista/Colores.h"

#define LADO_CASILLA 50
#define SEPARACION 4

class GUI_BotonInventario final : public IRendereable{
private:
	Imagen imagen;
	BancoImagenesEquipo imagenes_equipo;
	Colores& paleta;
	std::atomic<int>* inventario;
	void dibujarCasilla(int i, int j, SDL_Color& fondo);
public:
	int x,y;
	int ancho, alto;
	bool visible;
	GUI_BotonInventario(EntornoGrafico& entorno, Colores& paleta,
		std::atomic<int>* inventario);
	void actualizarDimension();
	void render();
};

#endif /*__GUI_BOTON_INVENTARIO_H__*/