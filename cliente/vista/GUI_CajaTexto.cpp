#include "GUI_CajaTexto.h"

GUI_CajaTexto::GUI_CajaTexto(EntornoGrafico& entorno, Colores& paleta) :
 paleta(paleta), marco_entrada({0,0,50,50}) {
	entorno.agregarRendereable(this);
	actualizarDimension();
}

void GUI_CajaTexto::render(){
	renderer -> setColor(paleta.chat_fondo);
	renderer -> rectSolido(marco_entrada);
	renderer -> setColor(paleta.chat_texto);

	if(entrada.size() > 0){
		if(entrada.size() > caracteres_max){
			renderer -> texto(entrada.substr(entrada.size() -caracteres_max,
				entrada.size()), marco_entrada.x, marco_entrada.y);
		}else{
			renderer -> texto(entrada, marco_entrada.x, marco_entrada.y);
		}
	}
}

void GUI_CajaTexto::actualizarDimension(){	
	caracteres_max = marco_entrada.w/ANCHO_CARACTER;
}
