#include "GUI_CajaTexto.h"
#define MS_CURSOR 300

enum margen_cursor : int {
	izquierda = 3,
	arriba = 2,
	derecha = 0,
	abajo = 3
};
#define ANCHO_CURSOR 1

GUI_CajaTexto::GUI_CajaTexto(EntornoGrafico& entorno, Colores& paleta) :
 paleta(paleta), tiempo(MS_CURSOR), mostrar_cursor(false), en_foco(false), 
 marco_entrada({ 0, 0, 50, 50 }) {
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_CajaTexto::darFoco(bool en_foco) {
	this->en_foco = en_foco;
}

void GUI_CajaTexto::actualizar(unsigned int delta_t) {
	tiempo -= delta_t;
	if (tiempo <= 0) {
		mostrar_cursor = !mostrar_cursor;
		tiempo = MS_CURSOR;
	}
}

void GUI_CajaTexto::render(){
	renderer -> setColor(paleta.chat_fondo);
	renderer -> rectSolido(marco_entrada);
	renderer -> setColor(paleta.chat_texto);

	std::string texto_a_mostrar = entrada;
	if(entrada.size() > 0){
		if(entrada.size() > caracteres_max){
			texto_a_mostrar = entrada.substr(entrada.size() - caracteres_max,
				entrada.size());
		}
		renderer->texto(
			texto_a_mostrar, 
			marco_entrada.x + margen_cursor::izquierda, 
			marco_entrada.y + margen_cursor::arriba);
	}

	int ancho;
	renderer->calcularDimensionTexto(texto_a_mostrar, &ancho, NULL);
	
	renderer->setColor(paleta.chat_texto);
	if (en_foco && mostrar_cursor) {
		renderer->rectSolido(
			marco_entrada.x + margen_cursor::izquierda + ancho,
			marco_entrada.y + margen_cursor::arriba, 
			ANCHO_CURSOR, 
			marco_entrada.h - margen_cursor::arriba - margen_cursor::abajo);
	}
}

void GUI_CajaTexto::actualizarDimension(){	
	caracteres_max = marco_entrada.w/ANCHO_CARACTER;
}
