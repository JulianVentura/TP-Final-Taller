#ifndef __BUCLE_LOGIN_H__
#define __BUCLE_LOGIN_H__

#include <SDL2/SDL_timer.h>
#include <thread>
#include <vector>
#include <memory>

#include "Reloj.h"
#include "../vista/Ventana.h"
#include "../vista/GUI_Login.h"
#include "../modelo/BuclePrincipal.h"
#include "../modelo/ServidorProxy.h"
#include "../controlador/IInteractivo.h"
#include "../controlador/GUI_CajaTexto_Controlador.h"

class BucleLogin {
private:
    Ventana* ventana;
    GUI_Login& gui;
    ServidorProxy& servidor;
    bool salir = false;
    void despacharEventos(SDL_Event& event);
    std::vector<IInteractivo *> interactivos;
    Reloj reloj;

public:
    BucleLogin(Ventana& ventana, GUI_Login& gui, 
            ServidorProxy& servidor);
    void agregarInteractivo(IInteractivo* interactivo);
    void correr();
};

#endif /*__BUCLE_LOGIN_H__*/
