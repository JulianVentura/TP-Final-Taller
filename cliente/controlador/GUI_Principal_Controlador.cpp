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
    tienda_controlador(vista_principal.tienda_vista, servidor),
    chat_controlador(vista_principal.chat_vista, servidor) {
        botones.push_back(&inventario_controlador);
        botones.push_back(&tienda_controlador);
        botones.push_back(&inventario_controlador);
        botones.push_back(&chat_controlador);
        servidor.salida = &chat_controlador;
    }

bool GUI_PrincipalControlador::manejarEvento(SDL_Event& evento) {
    if (evento.type == SDL_WINDOWEVENT) {
        vista_principal.actualizarDimension();
        boton_inventario_controlador.actualizarDimension();
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
        return chat_controlador.ingresarCaracter(evento);
    }
    return false;
}