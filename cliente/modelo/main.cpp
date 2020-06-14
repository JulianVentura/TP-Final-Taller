#include <iostream>
#include <string>

#include "BuclePrincipal.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/Ventana.h"
#include "../vista/Escena.h"
#include "../vista/GUI_Principal.h"
#include "../vista/GUI_BotonInventario.h"
#include "../controlador/GUI_BotonInventario_Controlador.h"

int main(int argc, const char* argv[]) {
    try {
        EntornoGrafico entorno;
        Ventana ventana(entorno, "Ejemplo");
        Renderer renderer(entorno);
        GUI_Principal gui(entorno); 

        BuclePrincipal bucle(ventana);
        std::string fuente_ruta("assets/DejaVuSansMono.ttf"); 
        entorno.cargarFuente(fuente_ruta, 15);
        Escena escena(entorno);

        ventana.agregarInteractivo(&escena);
        ventana.agregarRendereable(&escena);
        ventana.agregarRendereable(&gui);

        //Perdida monumental de memoria
        GUI_BotonInventario boton_inventario(entorno, 50, 50);
        bucle.botones.push_back(new GUI_BotonInventarioControlador(boton_inventario,50, 50, 50, 50));
        ventana.agregarRendereable(&boton_inventario);


        bucle.correr();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}