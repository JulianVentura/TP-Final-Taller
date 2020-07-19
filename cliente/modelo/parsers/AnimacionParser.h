#ifndef ANIMACIONPARSER_H
#define ANIMACIONPARSER_H
#include <unordered_map>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

typedef std::unordered_map<std::string, std::vector<int>> animaciones_t;

class AnimacionParser {
public:
    AnimacionParser() = default;
    AnimacionParser(nlohmann::json& parser, const std::string& tipo);
    int getGuid(std::string& accion, std::string& direccion, 
                                                    int columna, bool quieto);
    int getColumnas();
    int getColumnas(std::string& accion, std::string& direccion);
    int getDirecciones() const;
    int getAncho() const;
    int getAlto() const;
    int getTiempoPorCuadro() const;
    int getTiempoEntreCiclo() const;
    std::string getDireccionInicial() const;
    std::string getEstadoInicial() const;

private:
    int ancho;
    int alto;
    int direcciones;
    int columnas;
    int tiempo_por_cuadro;
    int tiempo_entre_ciclo;
    std::string estado_inicial;
    std::string direccion_inicial;
    animaciones_t animaciones;
};

#endif
