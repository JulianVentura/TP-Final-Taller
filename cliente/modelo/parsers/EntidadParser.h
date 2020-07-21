#ifndef ENTIDADPARSER_H
#define ENTIDADPARSER_H

#include <SDL2/SDL_rect.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <nlohmann/json.hpp>

#include "AnimacionParser.h"
#include "EquipableParser.h"
#include "DatosApariencia.h"
#include "PersonajeParser.h"
#include "../IPosicionable.h"
#include "../../vista/Imagen.h"

#define ENTIDADPARSER_DELIMITADOR "-"
#define ENTIDADPARSER_DELIMITADOR_RUTA "/"
#define ENTIDADPARSER_BASE "base"
#define ENTIDADPARSER_NPC "npc"
#define ENTIDADPARSER_IMAGEN "imagen"
#define ENTIDADPARSER_QUIETO "quieto"
#define ENTIDADPARSER_QUIETO_VALOR -1

class CapaSprite;
class EntidadParser {
public:
    EntidadParser(EntornoGrafico& entorno);
    ~EntidadParser();
    const std::vector<Imagen*>& getImagenes(DatosApariencia& apariencia, 
                                                    const std::string& parte);
    
    const std::vector<Imagen*>& getImagenes(DatosApariencia& apariencia);
    std::unordered_map<std::string, Imagen*> getEquipables(DatosApariencia& apariencia);
    int getAnchoReal(DatosApariencia& apariencia);
    int getAltoReal(DatosApariencia& apariencia);
    bool esObstruible(DatosApariencia& apariencia);
    CapaSprite* getCapaSprite(DatosApariencia& apariencia);
    CapaSprite* getCapaSprite(std::string& id);
    static void aMinuscula(std::string& cadena);
    
private:
    std::string idReal(DatosApariencia& apariencia);
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
    std::unordered_map<std::string, PersonajeParser> entidades;
    std::unordered_map<std::string, AnimacionParser> animaciones;
    std::unordered_map<std::string, EquipableParser> equipables;
    std::vector<Imagen*> bufferImagenes;
};

#endif
