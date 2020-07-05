#include "ServidorSalidaAlerta.h"

ServidorSalidaAlerta::ServidorSalidaAlerta(EntornoGrafico& entorno,
 Colores& paleta) : paleta(paleta){
	entorno.agregarRendereable(this);
}

void ServidorSalidaAlerta::render(){
	if(mensaje.size() == 0) return;
	renderer -> setColor(paleta.login_alarma);
	renderer -> rectSolido(ventana -> getAlto()*0.9, 0,
		ventana -> getAncho(), ventana -> getAlto()*0.1);
	renderer -> setColor(paleta.chat_texto);
	renderer -> texto( mensaje, ventana -> getAlto()*0.9, 0);
}

void ServidorSalidaAlerta::agregarMensaje(std::string nuevo_mensaje,
 bool mensaje_publico){
	mensaje = nuevo_mensaje;
}