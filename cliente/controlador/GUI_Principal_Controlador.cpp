#include "GUI_Principal_Controlador.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include "../vista/GUI_Principal.h"

GUI_PrincipalControlador::GUI_PrincipalControlador(ServidorProxy& servidor, 
    GUI_Principal& vista_principal) : 
    vista_principal(vista_principal),
    inventario_controlador(vista_principal.inventario_vista, servidor),
    boton_inventario_controlador(vista_principal.boton_inventario_vista, 
            vista_principal.inventario_vista),
    boton_meditar_controlador(vista_principal.boton_meditar_vista, 
            servidor),
    boton_resucitar_controlador(vista_principal.boton_resucitar_vista, 
            servidor),
    boton_oro_controlador(vista_principal.boton_oro_vista, servidor),
    tienda_controlador(vista_principal.tienda_vista, servidor),
    chat_controlador(vista_principal.chat_vista, servidor) {
        botones.push_back(&boton_oro_controlador);
        botones.push_back(&inventario_controlador);
        botones.push_back(&chat_controlador);
        botones.push_back(&boton_inventario_controlador);
        botones.push_back(&boton_meditar_controlador);
        botones.push_back(&boton_resucitar_controlador);
        botones.push_back(&tienda_controlador);

        servidor.salida = &chat_controlador;
}

bool GUI_PrincipalControlador::manejarEvento(SDL_Event& evento) {
    if (evento.type == SDL_WINDOWEVENT) {
        vista_principal.actualizarDimension();
        boton_inventario_controlador.actualizarDimension();
        boton_meditar_controlador.actualizarDimension();
        boton_resucitar_controlador.actualizarDimension();
        boton_oro_controlador.actualizarDimension();
        inventario_controlador.actualizarDimension();
        chat_controlador.actualizarDimension();
        tienda_controlador.actualizarDimension();
    } else if (evento.type == SDL_MOUSEBUTTONDOWN) {
        bool evento_consumido = false;
        for (auto& boton: botones) {
            evento_consumido = (*boton)(evento);
            if (evento_consumido) break;
        }
        return evento_consumido;
    } else if (evento.type == SDL_MOUSEWHEEL) {
        return chat_controlador.scroll(evento);
    } else if (evento.type == SDL_TEXTINPUT 
            || evento.type == SDL_KEYDOWN) {
        return chat_controlador.manejarEvento(evento);
    }
    return false;
}