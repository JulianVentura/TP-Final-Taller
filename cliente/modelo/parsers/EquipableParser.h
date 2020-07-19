#ifndef EQUIPABLEPARSER_H
#define EQUIPABLEPARSER_H
#include <nlohmann/json.hpp>
#include <string>
#include "../../vista/EntornoGrafico.h"
#include "../../vista/Imagen.h"

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

#endif