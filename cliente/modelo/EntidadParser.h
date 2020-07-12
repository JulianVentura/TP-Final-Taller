#ifndef ENTIDADPARSER_H
#define ENTIDADPARSER_H

#include <SDL2/SDL_rect.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <nlohmann/json.hpp>
#include "IPosicionable.h"

#include "../vista/Imagen.h"

// TODO provisorio, esto serían ids
// - arma, casco, escudo, armadura, raza, clase, estado.
struct DatosApariencia {
    std::string arma;
    std::string casco;
    std::string escudo;
    std::string armadura;
    std::string raza;
    std::string clase;
    std::string estado;
    std::string tipo; // arania, zombie, etc
};

typedef std::unordered_map<std::string, std::vector<Imagen*>> imagenes_t;
typedef std::unordered_map<std::string, std::vector<int>> animaciones_t;


class EntidadParser {
public:
    EntidadParser(EntornoGrafico& entorno);
    ~EntidadParser();
    imagenes_t getImagenes(std::string& raza, std::string& clase);
    imagenes_t getImagenes(std::string& tipo);
    int getAncho(std::string& raza, std::string& tipo);
    int getAlto(std::string& raza, std::string& tipo);
    int getAncho(std::string& tipo);
    int getAlto(std::string& tipo);
    int getGuid(std::string& tipo, std::string& accion, std::string& direccion, 
                                                int columna, bool quieto=true);
    int getAnimacionCantidadTipo(std::string& tipo);
    int getAnimacionCantidad(std::string& tipo, std::string& accion, 
                                                        std::string& direccion);

private:
    void parsearRazas();
    void parsearNPCs();
    void parsearAnimaciones();
    void parsearImagen(imagenes_t& setDeImagenes, const std::string& tipo,
                                                const std::string& variante);
    EntornoGrafico& entorno;
    nlohmann::json parser;
    std::string raiz;
    static const imagenes_t aparienciaImagenesBase;
    std::unordered_map<std::string, imagenes_t> imagenes;
    std::unordered_map<std::string, animaciones_t> animaciones;
    std::unordered_map<std::string, int> columnas;
};

#endif
