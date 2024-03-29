#ifndef __DATOS_TIENDA_H__
#define __DATOS_TIENDA_H__

#include <atomic>
#include "../modelo/DatosPersonaje.h"

class DatosTienda{
public:
	std::string id_vendedor;
	std::atomic<bool> activo;
	std::atomic<uint16_t> inventario[INV_ANCHO*INV_ALTO];
	std::atomic<uint16_t> precios[INV_ANCHO*INV_ALTO];
	std::atomic<uint16_t> oro_almacenado;
	DatosTienda();
};

#endif /*__DATOS_PERSONAJE_H__*/
