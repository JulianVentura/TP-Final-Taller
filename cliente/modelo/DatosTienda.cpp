#include "DatosTienda.h"

DatosTienda::DatosTienda(){
	activo = true;
	
	for(int i = 0; i < INV_ALTO*INV_ANCHO; i++){
		inventario[i] = 0;
		precios[i] = 0;
	}

	inventario[0] = 1;
	inventario[1] = 2;
	precios[0] = 100;
	precios[1] = 25;
}
