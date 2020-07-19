#include "EquipableParser.h"
#include "EntidadParser.h"
Imagen* EquipableParser::getImagen() {
    return imagen;
}

EquipableParser::~EquipableParser() {
    delete imagen;
}
std::string EquipableParser::getReemplazaA() {
    return reemplaza_a;
}

void EquipableParser::parsear(EntornoGrafico& entorno, nlohmann::json& parser, 
                            const std::string& tipo, const std::string& id) {
    std::string imagen_s;
    std::string ruta_base;
    std::string ruta_equipables;
    parser["raiz"].get_to(ruta_base);
    parser["ruta_equipables"].get_to(ruta_equipables);
	parser["equipables"][tipo]["reemplaza"].get_to(reemplaza_a);
	parser["equipables"][tipo]["datos"][id]["imagen"].get_to(imagen_s);
    std::string ruta = ruta_base + ruta_equipables + imagen_s;
	animacion = ENTIDADPARSER_BASE;
	if (parser["equipables"][tipo]["datos"][id].count("animacion"))
		parser["equipables"][tipo]["datos"][id]["animacion"].get_to(animacion);
    imagen = new Imagen(entorno, ruta);
}
