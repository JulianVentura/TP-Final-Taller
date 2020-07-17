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
}

void Juego::agregarEntidad(std::string& id, DatosApariencia& apariencia) {
    if (movibles.count(id)) return;
    printf("%s \n", id.c_str());
    movibles[id] = std::move(crearEntidad(id, apariencia));
    capaFrontal.agregarObstruible(movibles[id].second);
    servidor.agregarPosicionable(id, movibles[id].first);
    if (id == datos_personaje.id) 
        camara.setObjetivo(movibles[id].second);    
}

Juego::~Juego() {
    for (auto& movible: movibles) {
        borrarEntidad(movible.first);
        // delete movible.second.first;
        // delete movible.second.second;
    }
}

void Juego::borrarEntidad(const std::string& id) {
    if (!movibles.count(id)) return;
    servidor.borrarPosicionable(id);
    capaFrontal.borrarObstruible(movibles[id].second);
    delete movibles[id].first;
    delete movibles[id].second;
    movibles[id].first = nullptr;
    movibles[id].second = nullptr;
    movibles.erase(id);
}

std::pair<IPosicionable*, MovibleVista*> Juego::crearEntidad(std::string& id, 
                                                DatosApariencia& apariencia) {
    std::pair<IPosicionable*, MovibleVista*> resultado;
    resultado.first = new IPosicionable();
    resultado.second = new MovibleVista(entorno, resultado.first, 
                                                                entidadParser);
    auto posicion_identificador = id.find(NPC_DELIMITADOR);
    if (posicion_identificador != std::string::npos) {
        apariencia.tipo = id.substr(0, posicion_identificador);
        resultado.second->actualizarApariencia(apariencia);
    }
    return resultado;
}


void Juego::actualizarPosiciones(std::unordered_map<std::string, std::pair<int, 
                                                            int>> posiciones) {
    for (auto& posicion: posiciones) {
		if (!movibles.count(posicion.first)) {
			std::string id(posicion.first);
            DatosApariencia apariencia;
            agregarEntidad(id, apariencia);
			continue;
		}
		if (!movibles.count(posicion.first)) continue;
		auto& coordenadas = posicion.second;
		movibles[posicion.first].first->actualizarPosicion(coordenadas.first, 
															coordenadas.second);
	}
    std::vector<std::string> paraBorrar;
    for (auto& movible: movibles) {
        if (posiciones.count(movible.first)) continue;
        paraBorrar.push_back(movible.first);
    }
    for (auto& movible: paraBorrar)
        borrarEntidad(movible);
}

void Juego::actualizarEstados(std::vector<SerializacionDibujado> dibujados) {
    for (auto& dibujado: dibujados) {
        DatosApariencia apariencia;
        apariencia.raza = std::to_string(dibujado.idRaza);
        apariencia.clase = std::to_string(dibujado.idClase);
        apariencia.arma = std::to_string(dibujado.idArmaEquipada);
		apariencia.armadura = std::to_string(dibujado.idArmaduraEquipada);
		apariencia.casco = std::to_string(dibujado.idCascoEquipado);
		apariencia.escudo = std::to_string(dibujado.idEscudoEquipado);
		apariencia.estado = std::to_string(dibujado.idEstado);
        if (movibles.count(dibujado.id))
            movibles[dibujado.id].second->actualizarApariencia(apariencia);
    }
}