#include "ItemNulo.h"

ItemNulo::ItemNulo(std::string id, uint16_t idTCP, unsigned int unPrecio) :
Item(id, idTCP, unPrecio){}

void ItemNulo::utilizar(Personaje *personaje, unsigned int pos){}

void ItemNulo::desequipar(Personaje *personaje, unsigned int pos){}

ItemNulo::~ItemNulo(){}