#ifndef __DATOS_TIENDA_H__
#define __DATOS_TIENDA_H__

#include <atomic>
#include "../modelo/DatosPersonaje.h"

class DatosTienda{
public:
	std::atomic<bool> activo;
	std::atomic<int> inventario[INV_ANCHO*INV_ALTO];
	std::atomic<int> precios[INV_ANCHO*INV_ALTO];
	DatosTienda();
};

#endif /*__DATOS_PERSONAJE_H__*/