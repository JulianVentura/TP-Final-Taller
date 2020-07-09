#include "Juego.h"
#include "EntidadParser.h"
#include "ServidorProxy.h"

using json = nlohmann::json;

void Juego::agregarObstruible(IObstruible* obstruible) {
    capaFrontal.agregarObstruible(obstruible);
}

void Juego::actualizar(unsigned int delta_t) {
    escena.actualizar(delta_t);
}

void Juego::render() {
    escena.render();
}

bool Juego::manejarEvento(SDL_Event& evento) {
    /*
    if (evento.type == SDL_MOUSEBUTTONDOWN) {
        bool consumido = false;
        for (auto& movible: movibles) {
            consumido = movible.second.second->manejarEvento(evento);
            if (consumido) {
                std::string id = movible.first;
                servidor.enviarInteraccion(id);
                break;
            }
        }
    }
    return personajeManejable.manejarEvento(evento);
    */
    return false;
}

Juego::Juego(EntornoGrafico& entorno, std::string& mapa_s, 
                    DatosPersonaje& datos_personaje, ServidorProxy& servidor):
        entorno(entorno),
        datos_personaje(datos_personaje),
        servidor(servidor),
        parser(json::parse(mapa_s.c_str())),
        libreriaConjuntoTileParser(parser),
        conjuntoTiles(entorno, libreriaConjuntoTileParser),
        capasParser(parser, conjuntoTiles),
        capaFrontal(capasParser, conjuntoTiles),
        mapaParser(parser),
        mapa(entorno, mapaParser, conjuntoTiles),
        camara(mapa),
        escena(entorno, camara, mapa, capaFrontal, conjuntoTiles),
        personajeManejable(servidor),
        entidadParser(entorno) {
    entorno.agregarRendereable(this);
    servidor.setJuego(this);
    camara.setMarco(ventana);

    DatosApariencia ap;
    ap.raza = "humano";
    ap.clase = "Mago";
    agregarEntidad(datos_personaje.id, ap);

    // ap.raza = "gnomo";
    // ap.clase = "Guerrero";
    // std::string jugador3("j3");
    // agregarEntidad(jugador3, ap);

    // ap.raza = "humano";
    // ap.clase = "Clerigo";
    // std::string jugador4("jugador4");
    // agregarEntidad(jugador4, ap);

    // ap.raza = "";
    // ap.clase = "";
    // ap.tipo = "Zombie";
    // std::string jugador5("j5");
    // agregarEntidad(jugador5, ap);
}

void Juego::agregarEntidad(std::string& id, DatosApariencia& apariencia) {
    if (movibles.count(id) > 0) {
        printf("ya existe, habría que actualizar\n");
        return;
    }
    movibles[id].first = new IPosicionable();
    movibles[id].second = new MovibleVista(entorno, movibles[id].first, 
                                                    entidadParser, apariencia);
    
    movibles[id].first->actualizarPosicion(400 + random() % 30, 150 + random() % 150);
    capaFrontal.agregarObstruible(movibles[id].second);
    servidor.agregarPosicionable(id, movibles[id].first);
    
    if (id == datos_personaje.id) {
        camara.setObjetivo(movibles[id].second);    
    }
}

Juego::~Juego() {
    for (auto& movible: movibles) {
        delete movible.second.first;
        delete movible.second.second;
    }
}

void Juego::agregarNuevo(std::string& id) {
    DatosApariencia apariencia;
    // TODO: hardcodeado
    apariencia.raza = "humano";
    apariencia.clase = "Clerigo";
    agregarEntidad(id, apariencia);
    printf("Se agrega jugador %s\n", id.c_str());
}
