#include "DatosPersonaje.h"

DatosPersonaje::DatosPersonaje():
vida(50), vida_max(100),
mana(275), mana_max(350),
exp(740) , exp_max(1000),
oro(169){
	for(int i = 0;i < INV_ALTO*INV_ANCHO;i++){
		inventario[i] = 0;
	}

	inventario[0] = 1;
	inventario[1] = 2;
}