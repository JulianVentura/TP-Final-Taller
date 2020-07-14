#include "FabricaDeNPC.h"
#include "Banquero.h"
#include "Comerciante.h"
#include "Sacerdote.h"
#include "Portal.h"
#include "Excepcion.h"
#include <sstream>
#define LIMITE_CONTADOR 99999 //Podria ser otro numero

FabricaDeNPC::FabricaDeNPC(const std::unordered_map<std::string, Entidad*> &listaEntidades) : 
                                   entidades(listaEntidades),
                                   contador(0){}

std::unique_ptr<Criatura> FabricaDeNPC::obtenerCriaturaAleatoria(float x, float y, const std::string &idMapa){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string idCriatura = config->obtenerMapaSpawnCriaturaAleatoria(idMapa);
    std::unique_ptr<Criatura> criaturaEncapsulada(new Criatura(x, y, idCriatura));
    bool continuar = true;
    if (contador >= LIMITE_CONTADOR) contador = 0;
    while (continuar){
        std::stringstream temp;
        temp << idCriatura << "#" << contador;
        if (idValido(temp.str())){
            criaturaEncapsulada.get()->agregarDiferenciador(contador);
            continuar = false;
        }
        contador++;
    }
    return criaturaEncapsulada;
}


bool FabricaDeNPC::idValido(std::string id) const{
    std::unordered_map<std::string, Entidad*>::const_iterator it = entidades.find(id);
    if (it == entidades.end()) return true;
    return false;
}


std::unique_ptr<Entidad> FabricaDeNPC::obtenerNPCPasivo(const float x, 
                                                        const float y, 
                                                        const std::string &idNPC, 
                                                        const std::string &idMapa){
    if (idNPC == "Banquero") return std::unique_ptr<Entidad>(new Banquero(x, y));
    if (idNPC == "Comerciante") return std::unique_ptr<Entidad>(new Comerciante(x, y));
    if (idNPC == "Sacerdote") return std::unique_ptr<Entidad>(new Sacerdote(x, y));
    std::string sub = idNPC.substr(idNPC.find("#"));
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string mapaATeletransportar = config->obtenerPortalMapaATeletransportar(idNPC, idMapa);
    if (sub == "Portal") return std::unique_ptr<Entidad>(new Portal(x, y, idNPC, mapaATeletransportar));
    throw Excepcion("Error FabricaDeNPC: No se pudo parsear el NPC de id %s", idNPC);
}