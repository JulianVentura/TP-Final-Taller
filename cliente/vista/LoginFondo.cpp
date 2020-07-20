#include "LoginFondo.h"
#include "../vista/GUI_Login.h"

LoginFondo::LoginFondo(EntornoGrafico& entorno, Colores& paleta,bool& conectado)
: paleta(paleta), conectado(conectado), fondo(entorno,"assets/gui/fondoLogin.png"),
logo(entorno,"assets/gui/logo.png"){
	entorno.agregarRendereable(this);
	fondo.setPosicion(0,0);
	logo.setPosicion(0, 0);
}

void LoginFondo::render(){
	fondo.renderExpandido();
	logo.render();
	renderer -> setColor(paleta.login_texto);
	if(conectado){
		renderer -> texto("Nombre", X_BASE_LOGIN, Y_BASE_LOGIN);
		renderer -> texto("Clave", X_BASE_LOGIN, Y_BASE_LOGIN + 56);
		renderer -> setColor(paleta.chat_texto);
		renderer -> texto("Nombre", X_BASE_LOGIN, Y_BASE_LOGIN - 2);
		renderer -> texto("Clave", X_BASE_LOGIN, Y_BASE_LOGIN + 56 - 2);
	}else{
		renderer -> texto("Direccion", X_BASE_LOGIN, Y_BASE_LOGIN);
		renderer -> texto("Puerto", X_BASE_LOGIN, Y_BASE_LOGIN + 56);
		renderer -> setColor(paleta.chat_texto);
		renderer -> texto("Direccion", X_BASE_LOGIN, Y_BASE_LOGIN - 2);
		renderer -> texto("Puerto", X_BASE_LOGIN, Y_BASE_LOGIN + 56 - 2);
	}
}
