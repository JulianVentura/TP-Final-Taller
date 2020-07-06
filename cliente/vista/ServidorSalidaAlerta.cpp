#include "ServidorSalidaAlerta.h"

ServidorSalidaAlerta::ServidorSalidaAlerta(EntornoGrafico& entorno,
 Colores& paleta) : paleta(paleta){
	entorno.agregarRendereable(this);
}

void ServidorSalidaAlerta::render(){
	if(mensaje.size() == 0) return;
	renderer -> setColor(paleta.login_alarma);
	renderer -> rectSolido(0,ventana -> getAlto()*0.9,
		ventana -> getAncho(), ventana -> getAlto()*0.1);
	renderer -> setColor(paleta.chat_texto);
	renderer -> texto( mensaje, 0, ventana -> getAlto()*0.9);
}

void ServidorSalidaAlerta::agregarMensaje(std::string nuevo_mensaje,
 bool mensaje_publico){
	mensaje = nuevo_mensaje;
}
