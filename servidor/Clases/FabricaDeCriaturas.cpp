#include "FabricaDeCriaturas.h"
#include <sstream>
#define LIMITE_CONTADOR 99999 //Podria ser otro numero

FabricaDeCriaturas::FabricaDeCriaturas(const std::unordered_map<std::string, Entidad*> &listaEntidades) : 
                                   entidades(listaEntidades),
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
    std::unordered_map<std::string, Entidad*>::const_iterator it = entidades.find(id);
    if (it == entidades.end()) return true;
    return false;
}
