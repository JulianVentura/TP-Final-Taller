#ifndef OBSTACULO_H
#define OBSTACULO_H
#include <vector>
#include <SDL2/SDL_rect.h>
#include "IObstruible.h"
#include "LibreriaConjuntoTiles.h"

class Obstaculo: public IObstruible {
public:
    Obstaculo(SDL_Rect& dimension, std::vector<int>& guids, 
                                    LibreriaConjuntoTiles& conjuntoTiles);
    void render() override;

private:
    int columna;
    int fila;
    int ultima_columna;
    int ultima_fila;
    std::vector<int>& guids;
    LibreriaConjuntoTiles& conjuntoTiles;
};

#endif
