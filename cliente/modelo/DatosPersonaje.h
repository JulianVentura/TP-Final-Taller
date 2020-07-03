#ifndef __DATOS_PERSONAJE_H__
#define __DATOS_PERSONAJE_H__

#include <atomic>

#define INV_ALTO  6
#define INV_ANCHO 3

class DatosPersonaje{
public:
	std::atomic<int> vida, vida_max,
					 mana, mana_max,
					 exp , exp_max,
					 oro;
	std::atomic<int> inventario[INV_ANCHO*INV_ALTO];
	DatosPersonaje();
};

#endif /*__DATOS_PERSONAJE_H__*/
