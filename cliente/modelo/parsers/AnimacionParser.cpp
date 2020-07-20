#include "AnimacionParser.h"
#include "EntidadParser.h"
AnimacionParser::AnimacionParser(nlohmann::json& parser, 
                                                    const std::string& tipo) {
    columnas = parser["animacion"][tipo]["Columnas"];
    ancho = parser["animacion"][tipo]["Ancho"];
    alto = parser["animacion"][tipo]["Alto"];
    direcciones = parser["animacion"][tipo]["Direcciones"];
    estado_inicial = parser["animacion"][tipo]["Estado-Inicial"];
    direccion_inicial = parser["animacion"][tipo]["Direccion-Inicial"];
    tiempo_por_cuadro = parser["animacion"][tipo]["tiempo_por_cuadro"];
    tiempo_entre_ciclo = parser["animacion"][tipo]["tiempo_entre_ciclo"];
    int columna_inicial = parser["animacion"][tipo]["Columna"];
    for (auto& estado: parser["animacion"][tipo]["Estados"].items()) {
        std::string llave = estado.key();
        EntidadParser::aMinuscula(llave);
        std::string llave_quieto = llave + ENTIDADPARSER_DELIMITADOR + std::string(ENTIDADPARSER_QUIETO);
        EntidadParser::aMinuscula(llave_quieto);
        int cantidad = estado.value()["cantidad"];
        if (cantidad == 0) continue;
        int fila = estado.value()["fila"];
        animaciones[llave_quieto].push_back(fila * columnas + columna_inicial);
        for (int i = 0; i < cantidad; ++i) {
            int guid = fila * columnas + i + columna_inicial;
            animaciones[llave].push_back(guid);
        }
    }
    columnas -= columna_inicial;
}

int AnimacionParser::getGuid(std::string &accion, std::string &direccion, int columna, bool quieto) {
    std::string id;
    if (direccion.size())
        id = accion + ENTIDADPARSER_DELIMITADOR + direccion;
    else
        id = accion;
    EntidadParser::aMinuscula(id);
    if (!animaciones.count(id)) return 0;
    if (quieto || columna == 0) return animaciones[id][0];
    return animaciones[id][columna % animaciones[id].size()];
}

int AnimacionParser::getColumnas() { return columnas; }

int AnimacionParser::getAncho() const { return ancho; }
int AnimacionParser::getAlto() const { return alto; }
int AnimacionParser::getDirecciones() const { return direcciones; }

int AnimacionParser::getTiempoPorCuadro() const {
    return tiempo_por_cuadro;
}

int AnimacionParser::getTiempoEntreCiclo() const {
    return tiempo_entre_ciclo;
}

std::string AnimacionParser::getDireccionInicial() const { 
    return direccion_inicial; 
}

std::string AnimacionParser::getEstadoInicial() const { 
    return estado_inicial; 
}

int AnimacionParser::getColumnas(std::string& accion, std::string& direccion) {
    std::string id = accion + ENTIDADPARSER_DELIMITADOR + direccion;
    if (!direccion.size()) id = accion;
    EntidadParser::aMinuscula(id);
    return animaciones.at(id).size();
}
