#include "../vista/GUI_Chat.h"
#include "../vista/Ventana.h"

enum margen_cursor : int {
	izquierda = 3,
	arriba = 2,
	derecha = 0,
	abajo = 3
};
#define ANCHO_CURSOR 1
#define MS_CURSOR 300

GUI_Chat::GUI_Chat(EntornoGrafico& entorno, Colores& paleta)
: paleta(paleta), tiempo(MS_CURSOR), mostrar_cursor(false), en_foco(false) {
	entorno.agregarRendereable(this);
	actualizarDimension();
	esta_actualizado = true;
	textura = renderer -> textura(marco_mensajes.w, ALTO_TEXTURA);
}

void GUI_Chat::darFoco(bool en_foco) {
	this->en_foco = en_foco;
}

void GUI_Chat::actualizar(unsigned int delta_t) {
	tiempo -= delta_t;
	if (tiempo <= 0) {
		mostrar_cursor = !mostrar_cursor;
		tiempo = MS_CURSOR;
	}
}

void GUI_Chat::render() {
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
	std::string texto_a_mostrar = entrada;
	if(entrada.size() > 0){
		if(entrada.size() > caracteres_max){
			texto_a_mostrar = entrada.substr(entrada.size() -caracteres_max,
				entrada.size());
		}
		renderer->texto(
			texto_a_mostrar, 
			marco_entrada.x + margen_cursor::izquierda, 
			marco_entrada.y + margen_cursor::arriba);
	}
	int ancho;
	renderer->calcularDimensionTexto(texto_a_mostrar, &ancho, NULL);
	if(!esta_actualizado){
		esta_actualizado = true;
		renderizarTexto();
	}

	renderer->setColor(paleta.chat_texto);
	if (en_foco && mostrar_cursor) {
		renderer->rectSolido(
			marco_entrada.x + margen_cursor::izquierda + ancho,
			marco_entrada.y + margen_cursor::arriba, 
			ANCHO_CURSOR, 
			marco_entrada.h - margen_cursor::arriba - margen_cursor::abajo);
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
	textura = renderer -> textura(marco_mensajes.w, ALTO_TEXTURA);
	renderizarTexto();
}

void GUI_Chat::renderizarTexto(){
	if (!textura) return;
	unsigned int i;
	renderer -> limpiarTextura(textura);
	marco_textura.y = 0;

	for(auto& mensaje : mensajes){
		renderer -> setColor((std::get<1>(mensaje)) ?
		 paleta.chat_texto : paleta.chat_texto_privado);
		i = 0;
		while(i < std::get<0>(mensaje).size()){
			renderer -> textoATextura(textura,
			 std::get<0>(mensaje).substr(i, caracteres_max), 0,
			  marco_textura.y);
			i += caracteres_max;
			marco_textura.y += ALTO_CARACTER;
		}
	}

	marco_textura.y -= marco_textura.h - 2*ALTO_CARACTER;
	if (marco_textura.y < 0) marco_textura.y = 0;
}

void GUI_Chat::agregarMensaje(std::string mensaje, bool mensaje_publico){
	std::lock_guard<std::mutex> lock(m);
	mensajes.push_back(std::make_pair(std::move(mensaje), mensaje_publico));
	if( mensajes.size() > MENSAJES_MAX) mensajes.pop_front();
	esta_actualizado = false;
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
