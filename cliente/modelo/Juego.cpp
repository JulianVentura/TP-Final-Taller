#include "Juego.h"
#include "parsers/EntidadParser.h"
#include "ServidorProxy.h"
#include <SDL2/SDL_mouse.h>
#include <string>
#include <unordered_set>

#define NPC_DELIMITADOR "#"
using json = nlohmann::json;

void Juego::agregarEntidad(std::string& id) {
    if (!id.size()) return;
    auto posicion_identificador = id.find(NPC_DELIMITADOR);
    DatosApariencia apariencia;
    if (posicion_identificador != std::string::npos) 
        apariencia.tipo = id.substr(0, posicion_identificador);
    if (entidadParser.esObstruible(apariencia)) 
        capaFrontal.agregarObstruible(id, entidades[id].second);
    else
        mapa.agregarRendereable(id, entidades[id].second);
    if (id == datos_personaje.id) 
        camara.setObjetivo(entidades[id].second);    
    entidades[id].second->actualizarApariencia(apariencia);
}

void Juego::borrarEntidad(const std::string& id) {
    if (!entidades.count(id)) return;
    capaFrontal.borrarObstruible(id);
    delete entidades[id].first;
    delete entidades[id].second;
    entidades[id].first = nullptr;
    entidades[id].second = nullptr;
    entidades.erase(id);
}

std::pair<IPosicionable*, EntidadVista*> Juego::crearEntidad(std::string& id) {
    std::pair<IPosicionable*, EntidadVista*> resultado;
    resultado.first = new IPosicionable();
    resultado.second = new EntidadVista(entorno, resultado.first, 
                                                                entidadParser);
    return resultado;
}

void Juego::actualizarPosciones() {
    if (!posiciones_temp.size()) return;
    for (auto& posicion: posiciones_temp) {
        if (!entidades.count(posicion.first) && !entidades.count(posicion.first)) {
            std::string id(posicion.first);
            entidades[id] = std::move(crearEntidad(id));
            agregarEntidad(id);
        }
        if (!entidades.count(posicion.first)) continue;
        auto& coordenadas = posicion.second;
        entidades[posicion.first].first->actualizarPosicion(coordenadas.first, 
                                                            coordenadas.second);
    }
    std::unordered_set<std::string> paraBorrar;
    for (auto& entidad: entidades) {
        if (posiciones_temp.count(entidad.first)) continue;
        if (entidad.first == datos_personaje.id) continue;
        paraBorrar.insert(entidad.first);
    }
    for (auto& entidad: paraBorrar)
        borrarEntidad(entidad);
    posiciones_temp.clear();
}

void Juego::actualizar(unsigned int delta_t) {
    std::lock_guard<std::mutex> l(mtx);
    if (hay_que_actualizar_mapa) actualizarMapa();
    actualizarPosciones();
    for (auto& dibujado: dibujados_temp) {
        if (!entidades.count(dibujado.first)) continue;
        entidades[dibujado.first].second->actualizarApariencia(dibujado.second);
    }
    escena.actualizar(delta_t);
}

void Juego::actualizarMapa() {
    parser = json::parse(mapa_s.c_str());
    libreriaConjuntoTileParser.parse(parser);
    conjuntoTiles.parse(entorno, libreriaConjuntoTileParser);
    capasParser.parse(parser, conjuntoTiles);
    capaFrontal.parse(capasParser, conjuntoTiles);
    mapaParser.parse(parser);
    mapa.parse(mapaParser, conjuntoTiles);
    camara.setContenedor(mapa);
    for (auto& entidad: entidades) {
        std::string id(entidad.first); 
        agregarEntidad(id);
    }
    hay_que_actualizar_mapa = false;
}

void Juego::render() {
    if (hay_que_actualizar_mapa) return;
    for (auto& entidad: entidades) {
        entidad.second.second->reproducirSonido(entidades.at(datos_personaje.id).first);
    }
    escena.render();
}

bool Juego::despacharEventoClick(SDL_Event& evento) {
    int x = evento.button.x;
    int y = evento.button.y;
    camara.transformar(x, y);
    auto boton = evento.button.button;
    for (auto& entidad: entidades) {
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
    return false;
}

bool Juego::manejarEvento(SDL_Event& evento) {
    if (evento.type == SDL_MOUSEBUTTONDOWN) {
        std::lock_guard<std::mutex> l(mtx);
        if (hay_que_actualizar_mapa) return false;
        return despacharEventoClick(evento);
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

void Juego::cambiarMapa(const std::string& mapa_s) {
    std::lock_guard<std::mutex> l(mtx);
    this->mapa_s = std::move(mapa_s);
    hay_que_actualizar_mapa = true;
}


Juego::~Juego() {
    std::lock_guard<std::mutex> l(mtx);
    servidor.terminarJuego();
    for (auto& entidad: entidades) {
        delete entidad.second.first;
        delete entidad.second.second;
    }
}

void Juego::actualizarPosiciones(const std::unordered_map<std::string, std::pair<int, 
                                                            int>> posiciones) {
    std::lock_guard<std::mutex> l(mtx);
    if (hay_que_actualizar_mapa) return;
    for (const auto& posicion: posiciones) {
        posiciones_temp[posicion.first] = posicion.second;
    }
}

void Juego::actualizarEstados(const std::vector<SerializacionDibujado> dibujados) {
    std::lock_guard<std::mutex> l(mtx);
    if (hay_que_actualizar_mapa) return;
    for (const auto& dibujado: dibujados) {
        if (!entidades.count(dibujado.id)) continue;
        DatosApariencia apariencia;
        apariencia.raza = std::to_string(dibujado.idRaza);
        apariencia.clase = std::to_string(dibujado.idClase);
        apariencia.arma = std::to_string(dibujado.idArmaEquipada);
		apariencia.armadura = std::to_string(dibujado.idArmaduraEquipada);
		apariencia.casco = std::to_string(dibujado.idCascoEquipado);
		apariencia.escudo = std::to_string(dibujado.idEscudoEquipado);
		apariencia.estado = std::to_string(dibujado.idEstado);
        dibujados_temp[dibujado.id] = std::move(apariencia);
    }
}
