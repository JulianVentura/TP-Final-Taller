#include "../vista/GUI_Chat.h"
#include "../vista/Ventana.h"

GUI_Chat::GUI_Chat(EntornoGrafico& entorno, Colores& paleta)
: paleta(paleta) {
	entorno.agregarRendereable(this);
	actualizarDimension();
	actualizar = false;
	textura = renderer -> textura(marco_mensajes.w, ALTO_TEXTURA);
}

void GUI_Chat::render(){
	std::lock_guard<std::mutex> lock(m);
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

	if(actualizar){
		actualizar = false;
		renderizarTexto();
	}
}

void GUI_Chat::actualizarDimension(){
	std::lock_guard<std::mutex> lock(m);
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
	renderizarTexto();
}

void GUI_Chat::renderizarTexto(){
	if (!textura) return;
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
	std::lock_guard<std::mutex> lock(m);
	mensajes.push_back(mensaje);
	if( mensajes.size() > MENSAJES_MAX) mensajes.pop_front();
	actualizar = true;
}


void GUI_Chat::scroll(Sint32& incremento){
	std::lock_guard<std::mutex> lock(m);
	if(incremento > 0){
		marco_textura.y -= 20;
		if (marco_textura.y < 0) marco_textura.y = 0;
		return;
	}

	marco_textura.y += 20;
	if (marco_textura.y > marco_textura.h) marco_textura.y = marco_textura.h;
}

GUI_Chat::~GUI_Chat(){
	// TODO: puede romper si el renderer se destruye antes
	// No es necesario destruir la textura a mano, SDL la detruye en el quit
	SDL_DestroyTexture(textura);
}
