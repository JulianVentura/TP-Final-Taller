#include "main_login.h"

int main_login(EntornoGrafico& entorno, Ventana& ventana,
 ServidorProxy& servidor, Colores& paleta){
	EntornoMusical::obtenerInstancia() -> reproducirMusica("musicaMenu");
    GUI_Login gui_login(entorno, paleta, servidor);
    BucleLogin bucle_login(ventana, gui_login, servidor);
    ventana.agregarRendereable(&gui_login);
    bucle_login.correr();
    ventana.borrarRendereables();
    return 0;
}
