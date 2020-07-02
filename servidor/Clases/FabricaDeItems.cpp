#include "FabricaDeItems.h"
#include "Item.h"
#include "Arma.h"
//#include "Pocion.h"

FabricaDeItems::FabricaDeItems(){
    //Do nothing
}
std::unique_ptr<Item> FabricaDeItems::obtenerItemAleatorio(){
    //Implementar bien
    return std::unique_ptr<Arma>(new Arma(5,5,5,5));
}
//std::unique_ptr<Pocion> obtenerPocionDeVida();
//Armas
std::unique_ptr<Arma> FabricaDeItems::obtenerEspadaDeHierro(){
    return std::unique_ptr<Arma>(new Arma(5,5,5,5));
}

/*
Se podria tener una lista de 

*/
