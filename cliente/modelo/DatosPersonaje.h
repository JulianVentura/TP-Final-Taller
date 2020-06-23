#ifndef __DATOS_PERSONAJE_H__
#define __DATOS_PERSONAJE_H__

#include <atomic>

class DatosPersonaje{
public:
	std::atomic<int> vida, vida_max,
					 mana, mana_max,
					 exp , exp_max,
					 oro;
	DatosPersonaje();
};

#endif /*__DATOS_PERSONAJE_H__*/