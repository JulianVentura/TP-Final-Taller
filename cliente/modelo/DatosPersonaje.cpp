#include "DatosPersonaje.h"

DatosPersonaje::DatosPersonaje():
vida(0), vida_max(10),
mana(0), mana_max(10),
exp(0) , exp_max(10),
oro(0){
	for(int i = 0; i < INV_ALTO*INV_ANCHO; i++){
		inventario[i] = 0;
	}
}
