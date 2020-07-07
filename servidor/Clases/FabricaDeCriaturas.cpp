#include "FabricaDeCriaturas.h"
#include <sstream>
#define LIMITE_CONTADOR 99999 //Podria ser otro numero

FabricaDeCriaturas::FabricaDeCriaturas(const std::map<std::string, std::unique_ptr<Criatura>> &listaCriaturas) : 
                                   criaturas(listaCriaturas),
                                   contador(0){}

std::unique_ptr<Criatura> FabricaDeCriaturas::obtenerCriaturaAleatoria(float x, float y, const std::string &idMapa){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string idCriatura = config->obtenerMapaSpawnCriaturaAleatoria(idMapa);
    std::unique_ptr<Criatura> criaturaEncapsulada(new Criatura(x, y, idCriatura));
    bool continuar = true;
    if (contador > LIMITE_CONTADOR) contador = 0;
    while (continuar){
        std::stringstream temp;
        temp << idCriatura << "#" << contador;
        contador++;
        if (idValido(temp.str())){
            criaturaEncapsulada.get()->agregarDiferenciador(contador);
            continuar = false;
        }
    }
    return criaturaEncapsulada;
}


bool FabricaDeCriaturas::idValido(std::string id) const{
    std::map<std::string, std::unique_ptr<Criatura>>::const_iterator it = criaturas.find(id);
    if (it == criaturas.end()) return true;
    return false;
}
