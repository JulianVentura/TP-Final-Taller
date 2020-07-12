#include "Juego.h"
#include "EntidadParser.h"
#include "ServidorProxy.h"
#include <SDL2/SDL_mouse.h>
#include <string>
#define NPC_DELIMITADOR "#"


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
        int x = evento.button.x;
        int y = evento.button.y;
        camara.transformar(x, y);
        auto boton = evento.button.button;
        for (auto& movible: movibles) {
            if(movible.first == datos_personaje.id) continue;
            bool consumido = movible.second.second->contienePunto(x, y);
            if (!consumido) continue;
            printf("id %s\n", movible.first.c_str());
            if (boton == SDL_BUTTON_LEFT) 
                servidor.enviarInteraccion(movible.first);
            else if (boton == SDL_BUTTON_RIGHT)
                servidor.enviarAtaque(movible.first);
            else 
                break;
            return true;
        }
    } else if (evento.type == SDL_KEYDOWN || evento.type == SDL_KEYUP) {
        return personajeManejable.manejarEvento(evento);
    }
    return false;
}

Juego::Juego(EntornoGrafico& entorno, DatosPersonaje& datos_personaje, 
                                                    ServidorProxy& servidor):
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
    ap.clase = "mago";
    agregarEntidad(datos_personaje.id, ap);

    // std::string id = "asdsd";
    // std::vector<std::string> razas = {
    //     "humano",
    //     "elfo",
    //     "enano",
    //     "gnomo"
    // };
    // std::vector<std::string> clases = {
    //     "mago",
    //     "clerigo",
    //     "guerrero",
    //     "paladin"
    // };

    // std::vector<std::string> npcs = {
    //     "goblin",
    //     "esqueleto",
    //     "zombie",
    //     "arania"
    // };
    // for (auto& raza: razas) {
    //     for (auto& clase: clases) {
    //         ap.raza = raza;
    //         ap.clase = clase;
    //         id = raza + clase;
    //         agregarEntidad(id, ap);
    //     }
    // }
    // for (auto& npc: npcs) {
    //     id = npc + NPC_DELIMITADOR;
    //     agregarEntidad(id, ap);
    // }
}

void Juego::agregarEntidad(std::string& id, DatosApariencia& apariencia) {
    if (movibles.count(id) > 0) {
        printf("ya existe, habría que actualizar\n");
        return;
    }
    movibles[id] = crearEntidad(id, apariencia);
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

std::pair<IPosicionable*, MovibleVista*> Juego::crearEntidad(std::string& id, 
                                                DatosApariencia& apariencia) {
    std::pair<IPosicionable*, MovibleVista*> resultado;
    auto posicion_identificador = id.find(NPC_DELIMITADOR);
    if (posicion_identificador != std::string::npos) {
        // printf("este tiene el numeral %s\n", id.c_str());
        apariencia.tipo = id.substr(0, posicion_identificador);
        // apariencia.tipo = "";
        // apariencia.tipo = "zombie";
    } else {
        // Preguntarle al servidor la apariencia correcta
        // apariencia.raza = ...
        // apariencia.clase = ...
    }
    resultado.first = new IPosicionable();
    resultado.first->actualizarPosicion(rand() % 400 + 500, rand()% 500 + 200);
    resultado.second = new MovibleVista(entorno, resultado.first, 
                                                    entidadParser, apariencia);
    return resultado;
}

void Juego::agregarEntidad(std::string& id) {
    DatosApariencia apariencia;
    // TODO: hardcodeado
    // apariencia.raza = "humano";
    // apariencia.clase = "Mago";
    printf("%s\n", id.c_str());
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
