#include "../vista/GUI_Chat.h"
#include "../vista/Ventana.h"

#define MAX_ANCHO_CHAT 380

GUI_Chat::GUI_Chat(EntornoGrafico& entorno, Colores& paleta)
		: GUI_CajaTexto(entorno, paleta) {
	entorno.agregarRendereable(this);
	actualizarDimension();
	esta_actualizado = true;
	textura = renderer -> textura(marco_mensajes.w, ALTO_TEXTURA);
}

/*
*	Normalmente se renderiza una textura con el texto de los mensajes previamente
*	renderizado en ella. Cuando ingresa un nuevo mensaje, se cambia el valor
*	de "esta_actualizado" y esto provoca la actualizacion del contenido de
*	de la textura. renderizarTexto no puede ser llamado directamente en
*	agregarMensaje, pues el render es un recurso sujeto a condiciones de carrera.
*	Alternativamente pueden emplearse estrcturas de mutex más sofisticadas.
*/
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

	if(!esta_actualizado){
		esta_actualizado = true;
		renderizarTexto();
	}
	GUI_CajaTexto::render();
}

void GUI_Chat::actualizarDimension(){
	std::lock_guard<std::mutex> lock(m);
	int ventana_ancho = ventana -> getAncho();
	int ventana_alto = ventana -> getAlto();
	marco_mensajes.x = 0;
	marco_mensajes.y = ventana_alto*0.25;
	marco_mensajes.h = ventana_alto*0.4;
	marco_mensajes.w = std::min<float>(ventana_ancho*0.25, MAX_ANCHO_CHAT);
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

GUI_Chat::~GUI_Chat(){}
