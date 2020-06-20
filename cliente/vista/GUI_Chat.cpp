#include "../vista/GUI_Chat.h"
#include "../vista/Ventana.h"
GUI_Chat::GUI_Chat(EntornoGrafico& entorno, Colores& paleta)
: paleta(paleta) {
	entorno.agregarRendereable(this);
	actualizarDimension();
	textura = renderer -> textura(marco_mensajes.w,
		 1000);
}

void GUI_Chat::render(){
	renderer -> setColor(paleta.chat_fondo);
	renderer -> rectSolido(marco_mensajes);
	renderer -> setColor(paleta.chat_entrada);
	renderer -> rectSolido(marco_entrada);
	renderer -> setColor(paleta.chat_borde);
	renderer -> rect(marco_mensajes.x - 1, marco_mensajes.y - 1,
		marco_mensajes.w + 1, marco_mensajes.h + marco_entrada.h + 1);
	renderer ->renderTextura(textura, marco_textura, marco_mensajes);
	
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

void GUI_Chat::actualizarDimension(){
	int ventana_ancho = ventana -> getAncho();
	int ventana_alto = ventana -> getAlto();
	marco_mensajes.x = 0;
	marco_mensajes.y = ventana_alto*0.25;
	marco_mensajes.h = ventana_alto*0.4;
	marco_mensajes.w = ventana_ancho*0.25;
	marco_entrada.x = 0;
	marco_entrada.h = 2*ALTO_CARACTER;
	marco_entrada.y = marco_mensajes.h + marco_mensajes.y;
	marco_entrada.w = marco_mensajes.w;
	marco_textura.x = 0; marco_textura.y = 0;
	marco_textura.w = marco_mensajes.w;
	marco_textura.h = marco_mensajes.h;
	caracteres_max = marco_mensajes.w/ANCHO_CARACTER;
}

void GUI_Chat::renderizarTexto(){
	unsigned int i;
	renderer -> limpiarTextura(textura);
	renderer -> setColor(paleta.chat_texto);
	marco_textura.y = 0;
	for(auto mensaje : mensajes){
		i = 0;
		while(i < mensaje.size()){
			renderer -> textoATextura(textura,
			 mensaje.substr(i, caracteres_max), 0, marco_textura.y);
			i += caracteres_max;
			marco_textura.y += ALTO_CARACTER;
		}
	}

	marco_textura.y -= marco_textura.h - 2*ALTO_CARACTER;
	if (marco_textura.y < 0) marco_textura.y = 0;
}

void GUI_Chat::agregarMensaje(std::string mensaje){
	mensajes.push_back(std::move(mensaje));
	if( mensajes.size() > MENSAJES_MAX) mensajes.pop_front();
	renderizarTexto();
}


void GUI_Chat::scroll(Sint32& incremento){
	if(incremento > 0){
		marco_textura.y -= 20;
		if (marco_textura.y < 0) marco_textura.y = 0;
		return;
	}

	marco_textura.y += 20;
	if (marco_textura.y > marco_textura.h) marco_textura.y = marco_textura.h;
}

GUI_Chat::~GUI_Chat(){
	SDL_DestroyTexture(textura);
}