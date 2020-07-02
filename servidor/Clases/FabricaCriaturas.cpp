#include "FabricaCriaturas.h"
#include <sstream>
#define LIMITE_CONTADOR 1000 //Podria ser otro numero

FabricaCriaturas::FabricaCriaturas(const std::map<std::string, std::unique_ptr<Criatura>> &listaCriaturas) : 
                                   criaturas(listaCriaturas),
                                   contador(0){}

std::unique_ptr<Criatura> FabricaCriaturas::obtenerCriaturaAleatoria(float x, float y){
    std::string id = ""; 
    bool continuar = true;
    if (contador > LIMITE_CONTADOR) contador = 0;
    while (continuar){
        std::stringstream temp;
        temp << "Criatura" << contador;
        contador++;
        if (idValido(id)){
            id = temp.str();
            continuar = false;
        }
    }
    return std::unique_ptr<Criatura>(new Criatura(x, y, id));
}


bool FabricaCriaturas::idValido(std::string &id) const{
    std::map<std::string, std::unique_ptr<Criatura>>::const_iterator it = criaturas.find(id);
    if (it == criaturas.end()) return true;
    return false;
}

/*
FabricaDeCriaturas::CrearArania(Posicion posicion){
    std::string id = "Arania";
    std::string idArma = config.obtenerIdArmaCriatura(id);
    std::unique_ptr<Criatura> criatura(new Criatura(id))
    std::unique_ptr<Arma> armaEncapsulada = std::move(fabricaItems.crearArma(idArma));
    Arma *arma = armaEncapsulada.get();
    criatura.almacenar(armaEncapsulada);
    criatura.equipar(arma);
}
*/