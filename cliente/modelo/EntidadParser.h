#ifndef ENTIDADPARSER_H
#define ENTIDADPARSER_H

#include <SDL2/SDL_rect.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <nlohmann/json.hpp>
#include "IPosicionable.h"

#include "../vista/Imagen.h"

struct DatosApariencia {
    std::string arma;
    std::string casco;
    std::string escudo;
    std::string armadura;
    std::string raza;
    std::string clase;
    std::string estado;
    std::string tipo;
};
typedef std::unordered_map<std::string, std::vector<Imagen*>> imagenes_t;
class PersonajeParser {
public:
    PersonajeParser() = default;
    ~PersonajeParser();
    void parsear(EntornoGrafico& entorno, nlohmann::json& parser, 
        std::string& raiz, const std::string& raza, const std::string& clase, 
                                        const imagenes_t setDeImagenesBase);
    void parsear(EntornoGrafico& entorno, nlohmann::json& parser, 
                std::string& raiz, const std::string& tipo, const imagenes_t 
                                                            setDeImagenesBase);
    std::string getId();
    const std::vector<Imagen*>& getImagenes(const std::string& parte);

private:
    void parsearImagen(EntornoGrafico& entorno, std::string& raiz, imagenes_t& 
        setDeImagenes, const std::string& tipo, const std::string& variante);
    imagenes_t setDeImagenes;
    std::vector<Imagen*> bufferImagenes;
    std::string id;
};

typedef std::unordered_map<std::string, std::vector<int>> animaciones_t;

class AnimacionParser {
public:
    AnimacionParser() = default;
    AnimacionParser(nlohmann::json& parser, const std::string& tipo);
    int getGuid(std::string& accion, std::string& direccion, 
                                                    int columna, bool quieto);
    int getColumnas();
    int getColumnas(std::string& accion, std::string& direccion);

private:
    int ancho;
    int alto;
    int columnas;
    animaciones_t animaciones;
};

class EquipableParser {
public:
    ~EquipableParser();
	void parsear(EntornoGrafico& entorno, nlohmann::json& parser, 
                            const std::string& tipo, const std::string& id);
    Imagen* getImagen();
    std::string getReemplazaA();
private:
	std::string reemplaza_a;
	Imagen* imagen;
	std::string animacion;
};

class EntidadParser {
public:
    EntidadParser(EntornoGrafico& entorno);
    ~EntidadParser();
    const std::vector<Imagen*>& getImagenes(DatosApariencia& apariencia, 
                                                    const std::string& parte);
    std::unordered_map<std::string, Imagen*> getEquipables(DatosApariencia& apariencia);

    int getGuid(DatosApariencia& apariencia, std::string& accion, std::string& direccion, 
                                                int columna, bool quieto=true);
    int getAncho(DatosApariencia& apariencia);
    int getAnchoReal(DatosApariencia& apariencia);
    int getAlto(DatosApariencia& apariencia);
    int getAltoReal(DatosApariencia& apariencia);
    int getAnimacionCantidadTipo(DatosApariencia& apariencia);
    int getAnimacionCantidad(DatosApariencia& apariencia, std::string& accion, 
                                                        std::string& direccion);

private:
    const std::vector<Imagen*>& getImagenes(const std::string& raza, 
                        const std::string& clase, const std::string& parte);
    const std::vector<Imagen*>& getImagenes(const std::string& tipo, 
                                                    const std::string& parte);
    void parsearRazas();
    void parsearNPCs();
    void parsearAnimaciones();
    void parsearImagen(imagenes_t& setDeImagenes, const std::string& tipo,
                                                const std::string& variante);
    int getAncho(std::string& raza, std::string& tipo);
    int getAlto(std::string& raza, std::string& tipo);
    int getAncho(std::string& tipo);
    int getAlto(std::string& tipo);
    EntornoGrafico& entorno;
    nlohmann::json parser;
    std::string raiz;
    static const imagenes_t aparienciaImagenesBase;
    std::unordered_map<std::string, PersonajeParser> personajes;
    std::unordered_map<std::string, AnimacionParser> animaciones;
    std::unordered_map<std::string, EquipableParser> equipables;
    std::vector<Imagen*> bufferImagenes;
};

#endif
