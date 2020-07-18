#include "DatosTienda.h"

DatosTienda::DatosTienda(){
	activo = false;
	for(int i = 0; i < INV_ALTO*INV_ANCHO; i++){
		inventario[i] = 0;
		precios[i] = 0;
	}
	oro_almacenado = 0;
}
