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
    if (evento.type == SDL_MOUSEBUTTONDOWN) {
        bool consumido = false;
        for (auto& movible: movibles) {
            if(movible.first == datos_personaje.id) continue;
            consumido = movible.second.second->manejarEvento(evento);
            if (consumido) {
                switch(SDL_GetMouseState(NULL, NULL)) {
                    case SDL_BUTTON_LEFT:
                        servidor.enviarInteraccion(movible.first);
                    break;

                    default:
                        printf("Esta bien\n");
                        servidor.enviarAtaque(movible.first);
                    break;
                }
                return true;
            }
        }
    } else if (evento.type == SDL_KEYDOWN || evento.type == SDL_KEYUP) {
        return personajeManejable.manejarEvento(evento);
    }
    return false;
}

Juego::Juego(EntornoGrafico& entorno, /* std::string& mapa_s, */
                    DatosPersonaje& datos_personaje, ServidorProxy& servidor):
        entorno(entorno),
        datos_personaje(datos_personaje),
        servidor(servidor),
        mapa_s(std::move(servidor.obtenerMapa())),
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
    ap.clase = "Guerrero";
    agregarEntidad(datos_personaje.id, ap);
}

void Juego::agregarEntidad(std::string& id, DatosApariencia& apariencia) {
    if (movibles.count(id) > 0) {
        printf("ya existe, habría que actualizar\n");
        return;
    }
    movibles[id].first = new IPosicionable();
    movibles[id].second = new MovibleVista(entorno, movibles[id].first, 
                                                    entidadParser, apariencia);
    
    // movibles[id].first->actualizarPosicion(400 + random() % 30, 150 + random() % 150);
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

void Juego::borrarEntidad(std::string& id) {
    if (movibles.count(id) == 0) return;
    servidor.borrarPosicionable(id);
    capaFrontal.borrarObstruible(movibles[id].second);
    delete movibles[id].first;
    delete movibles[id].second;
    movibles.erase(id);
}

void Juego::agregarEntidad(std::string& id) {
    DatosApariencia apariencia;
    // TODO: hardcodeado
    apariencia.raza = "humano";
    apariencia.clase = "Mago";
    agregarEntidad(id, apariencia);
}

void Juego::actualizarPosiciones(std::unordered_map<std::string, std::pair<int, 
                                                            int>> posiciones) {
    for (auto& posicion: posiciones) {
		if (movibles.count(posicion.first) == 0) {
			std::string id(posicion.first);
			agregarEntidad(id);
			continue;
		}
		if (movibles.count(posicion.first) == 0) continue;
		auto& coordenadas = posicion.second;
		movibles[posicion.first].first->actualizarPosicion(coordenadas.first, 
															coordenadas.second);
	}
    std::vector<std::string> paraBorrar;
    for (auto& movible: movibles) {
        if (posiciones.count(movible.first) > 0) continue;
        paraBorrar.push_back(movible.first);
    }
    for (auto& movible: paraBorrar)
        borrarEntidad(movible);
}
