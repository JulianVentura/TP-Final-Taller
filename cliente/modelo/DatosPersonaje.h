#ifndef __DATOS_PERSONAJE_H__
#define __DATOS_PERSONAJE_H__

#include <string>
#include <vector>
#include <atomic>

#define INV_ALTO  6
#define INV_ANCHO 3
#define ESPACIOS_EQUIPO 4

class DatosPersonaje{
public:
	std::string id;
	std::atomic<uint16_t> vida, vida_max,
					 mana, mana_max,
					 exp , exp_max,
					 nivel, oro;
	std::atomic<uint16_t> inventario[INV_ANCHO*INV_ALTO];
	std::atomic<uint16_t> equipados[ESPACIOS_EQUIPO];
	DatosPersonaje();
};

#endif /*__DATOS_PERSONAJE_H__*/
