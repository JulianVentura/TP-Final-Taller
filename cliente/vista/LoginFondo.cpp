#include "LoginFondo.h"

LoginFondo::LoginFondo(EntornoGrafico& entorno, Colores& paleta,bool& conectado)
: paleta(paleta), conectado(conectado), imagen(entorno,"assets/fondoLogin.png"){
	entorno.agregarRendereable(this);
}

void LoginFondo::render(){
	int ventana_ancho  = ventana -> getAncho();
	int ventana_alto = ventana -> getAlto();
	imagen.setPosicion(0,(ventana_alto - imagen.getAlto())/2);
	imagen.renderExpandido();
	renderer -> setColor(paleta.login_texto);
	if(conectado){
		renderer -> texto("Nombre", ventana_ancho*0.1,ventana_alto*0.2);
		renderer -> texto("Clave", ventana_ancho*0.1,ventana_alto*0.2 + 56);
		renderer -> setColor(paleta.chat_texto);
		renderer -> texto("Nombre", ventana_ancho*0.1,ventana_alto*0.2 - 2);
		renderer -> texto("Clave", ventana_ancho*0.1,ventana_alto*0.2 + 54);
	}else{
		renderer -> texto("Direccion", ventana_ancho*0.1,ventana_alto*0.2);
		renderer -> texto("Puerto", ventana_ancho*0.1,ventana_alto*0.2 + 56);
		renderer -> setColor(paleta.chat_texto);
		renderer -> texto("Direccion", ventana_ancho*0.1,ventana_alto*0.2 - 2);
		renderer -> texto("Puerto", ventana_ancho*0.1,ventana_alto*0.2 + 54);
	}
}
