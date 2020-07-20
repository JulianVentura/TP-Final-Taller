#ifndef __MAIN_JUEGO_H__
#define __MAIN_JUEGO_H__

#include "../modelo/Juego.h"
#include "../modelo/BuclePrincipal.h"
#include "../modelo/DatosPersonaje.h"
#include "../modelo/DatosTienda.h"
#include "../vista/GUI_Principal.h"
#include "../vista/EntornoMusical.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/EntornoMusical.h"
#include "../vista/Ventana.h"
#include "../vista/Colores.h"

int main_juego(EntornoGrafico& entorno, Ventana& ventana,
	ServidorProxy& servidor, Colores& paleta, DatosPersonaje& datos_personaje,
	DatosTienda& datos_tienda);

#endif /*__MAIN_JUEGO_H__*/