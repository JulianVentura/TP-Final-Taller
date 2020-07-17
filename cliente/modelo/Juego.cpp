#include "Juego.h"
#include "EntidadParser.h"
#include "ServidorProxy.h"
#include <SDL2/SDL_mouse.h>
#include <string>
#include <unordered_set>

#define NPC_DELIMITADOR "#"

using json = nlohmann::json;

void Juego::actualizar(unsigned int delta_t) {
    std::lock_guard<std::mutex> l(mtx);
    escena.actualizar(delta_t);
}

void Juego::render() {
    std::lock_guard<std::mutex> l(mtx);
    escena.render();
}

bool Juego::manejarEvento(SDL_Event& evento) {
    if (evento.type == SDL_MOUSEBUTTONDOWN) {
        int x = evento.button.x;
        int y = evento.button.y;
        camara.transformar(x, y);
        auto boton = evento.button.button;
        for (auto& entidad: entidades) {
            if(entidad.first == datos_personaje.id) continue;
            bool consumido = entidad.second.second->contienePunto(x, y);
            if (!consumido) continue;
            if (boton == SDL_BUTTON_LEFT) 
                servidor.enviarInteraccion(entidad.first);
            else if (boton == SDL_BUTTON_RIGHT)
                servidor.enviarAtaque(entidad.first);
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
    if (entidades.count(id)) return;
    auto posicion_identificador = id.find(NPC_DELIMITADOR);
    if ((id.substr(0, posicion_identificador) == "FlechaMagica" || id.substr(0, posicion_identificador) == "Curar" || id.substr(0, posicion_identificador) == "Misil" || id.substr(0, posicion_identificador) == "Explosion" || id.substr(0, posicion_identificador) == "Cuerpo" || id.substr(0, posicion_identificador) == "Flechazo")) return;
    printf("%s \n", id.c_str());
    entidades[id] = std::move(crearEntidad(id, apariencia));
    capaFrontal.agregarObstruible(id, entidades[id].second);
    servidor.agregarPosicionable(id, entidades[id].first);
    if (id == datos_personaje.id) 
        camara.setObjetivo(entidades[id].second);    
}

Juego::~Juego() {
    for (auto& entidad: entidades) {
        delete entidad.second.first;
        delete entidad.second.second;
    }
}

void Juego::borrarEntidad(const std::string& id) {
    if (!entidades.count(id)) return;
    servidor.borrarPosicionable(id);
    capaFrontal.borrarObstruible(id);
    delete entidades[id].first;
    delete entidades[id].second;
    entidades[id].first = nullptr;
    entidades[id].second = nullptr;
    entidades.erase(id);
}

std::pair<IPosicionable*, EntidadVista*> Juego::crearEntidad(std::string& id, 
                                                DatosApariencia& apariencia) {
    std::pair<IPosicionable*, EntidadVista*> resultado;
    auto posicion_identificador = id.find(NPC_DELIMITADOR);
    resultado.first = new IPosicionable();
    resultado.second = new EntidadVista(entorno, resultado.first, 
                                                                entidadParser);
    if (posicion_identificador != std::string::npos) {
        apariencia.tipo = id.substr(0, posicion_identificador);
        resultado.second->actualizarApariencia(apariencia);
    }
    return resultado;
}


void Juego::actualizarPosiciones(std::unordered_map<std::string, std::pair<int, 
                                                            int>> posiciones) {
    std::lock_guard<std::mutex> l(mtx);
    for (auto& posicion: posiciones) {
		if (!entidades.count(posicion.first)) {
			std::string id(posicion.first);
            DatosApariencia apariencia;
            agregarEntidad(id, apariencia);
			// continue;
		}
		if (!entidades.count(posicion.first)) continue;
		auto& coordenadas = posicion.second;
		entidades[posicion.first].first->actualizarPosicion(coordenadas.first, 
															coordenadas.second);
	}
    std::unordered_set<std::string> paraBorrar;
    for (auto& entidad: entidades) {
        if (posiciones.count(entidad.first)) continue;
        paraBorrar.insert(entidad.first);
    }
    for (auto& entidad: paraBorrar)
        borrarEntidad(entidad);
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
        if (entidades.count(dibujado.id))
            entidades[dibujado.id].second->actualizarApariencia(apariencia);
    }
}
