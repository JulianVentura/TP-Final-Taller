#include "ServidorSalidaAlerta.h"

ServidorSalidaAlerta::ServidorSalidaAlerta(EntornoGrafico& entorno,
 Colores& paleta) : paleta(paleta){
	entorno.agregarRendereable(this);
}

void ServidorSalidaAlerta::render(){
	if(mensaje.size() == 0) return;
	renderer -> setColor(paleta.login_alarma);
	renderer -> rectSolido(0, 0, ventana -> getAncho(), ventana -> getAlto()*0.1);
	renderer -> setColor(paleta.chat_texto);
	if(mensaje.size() > 58){
		renderer -> texto(mensaje.substr(0, 58));
		renderer -> texto(mensaje.substr(58, std::string::npos), 0, 14);
	}else{
		renderer -> texto(mensaje);
	}

}

void ServidorSalidaAlerta::agregarMensaje(std::string nuevo_mensaje,
 bool mensaje_publico){
	mensaje = nuevo_mensaje;
}
