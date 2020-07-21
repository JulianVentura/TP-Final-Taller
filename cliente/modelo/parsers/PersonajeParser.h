#ifndef PERSONAJEPARSER_H
#define PERSONAJEPARSER_H
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "AnimacionParser.h"
#include "../Sprite.h"
#include "../../vista/EntornoGrafico.h"
#include "../../vista/Imagen.h"
#include "../../vista/Animacion.h"

class PersonajeParser {
public:
    ~PersonajeParser();
    void parsear(EntornoGrafico& entorno, nlohmann::json& parser, 
        std::string& raiz, const std::string& raza, const std::string& clase, 
                                        const imagenes_t setDeImagenesBase);
    void parsear(EntornoGrafico& entorno, nlohmann::json& parser, 
                std::string& raiz, const std::string& tipo, const imagenes_t 
                                                            setDeImagenesBase);
    int getAncho();
    int getAlto();
    float getFactor();
    bool esObstruible();

    const std::vector<Imagen*>& getImagenes(const std::string& parte);
    CapaSprite* getCapaSprite();
    void setAnimacion(std::unordered_map<std::string, AnimacionParser>& animaciones);
    AnimacionBase* getAnimacion();

private:
    void parsearImagen(EntornoGrafico& entorno, std::string& raiz, imagenes_t& 
        setDeImagenes, const std::string& tipo, const std::string& variante, std::string& color_fondo);
    imagenes_t setDeImagenes;
    std::vector<Imagen*> bufferImagenes;
    std::string id;
    CapaSprite* capa;
    std::string animacion_s;
    AnimacionBase* animacion;
    bool es_obstruible = true;
    float factor = 1.0f;
    int ancho;
    int alto;
};
#endif
