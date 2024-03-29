#include "LibreriaConjuntoTileParser.h"
#include <nlohmann/json.hpp>
#include <utility>
using json = nlohmann::json;

int LibreriaConjuntoTileParser::getAnchoTile() const { return ancho_tile; }
int LibreriaConjuntoTileParser::getAltoTile() const { return alto_tile; }
int LibreriaConjuntoTileParser::getColumnas() const { return columnas; }

std::vector<InformacionConjuntoTile> 
                    LibreriaConjuntoTileParser::getInformacionLibreria() const {
    return std::move(this->conjuntosTiles);
}

void LibreriaConjuntoTileParser::parse(nlohmann::json& parser) {
    conjuntosTiles.clear();
    parser["tileheight"].get_to(alto_tile);
    parser["tilewidth"].get_to(ancho_tile);
    parser["width"].get_to(columnas);
    for (auto& conjunto_tile: parser["tilesets"]) {
        InformacionConjuntoTile info;
        conjunto_tile["columns"].get_to(info.columnas);
        conjunto_tile["firstgid"].get_to(info.primer_id);
        conjunto_tile["image"].get_to(info.ruta);
        conjunto_tile["tilecount"].get_to(info.cantidad_tiles);
        conjunto_tile["tileheight"].get_to(info.alto_tile);
        conjunto_tile["tilewidth"].get_to(info.ancho_tile);
        if (conjunto_tile.count("transparentcolor")) {
            conjunto_tile["transparentcolor"].get_to(info.color_transparente);
        }
        conjuntosTiles.push_back(std::move(info));
    }
}

LibreriaConjuntoTileParser::LibreriaConjuntoTileParser(nlohmann::json& parser) {
    parse(parser);    
}
