#include "DatosPersonaje.h"

DatosPersonaje::DatosPersonaje():
vida(0), vida_max(10),
mana(0), mana_max(0),
exp(0) , exp_max(10),
nivel(0), oro(0){
	for(int i = 0; i < INV_ALTO*INV_ANCHO; i++){
		inventario[i] = 0;
	}

	for(int i = 0;i < ESPACIOS_EQUIPO; i++){
		equipados[i] = -1;
	}
}
