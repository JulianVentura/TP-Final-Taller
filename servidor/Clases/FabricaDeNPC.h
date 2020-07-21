#ifndef __FABRICA_DE_NPC_H__
#define __FABRICA_DE_NPC_H__
#include "Entidad.h"
#include "Criatura.h"
#include <map>
#include <memory>

class FabricaDeNPC{
    private:
    const std::unordered_map<std::string, Entidad*> &entidades;
    unsigned long contador;

    bool idValido(std::string id) const;

    public:
    FabricaDeNPC(const std::unordered_map<std::string, Entidad*> &entidades);
    /*
    Devuelve un unique_ptr<Criatura> a una criatura generada aleatoriamente en base al id del mapa.
    Las posibles criaturas elegidas seran configuradas en el archivo de configuraciones y deberan
    ser indexadas segun el id del mapa.
    La criatura se inicializara con un diferenciador que evite conflictos entre las criaturas del mapa.
    Ademas se inicializara en la posicion solicitada, dada por las coordenadas x e y.
    */
    std::unique_ptr<Criatura> obtenerCriaturaAleatoria(float x, float y, const std::string &idMapa);
    /*
    Devuelve un unique_ptr<Entidad> que encapsula a un NPC pacifico, como puede ser un Sacerdote, Banquero,
    Comerciante o Portal.
    El idNPC sera el determinante de la entidad retornada, mientras que el id al mapa sera necesario para la
    inicializacion de Portal, si el idNPC corresponde al mismo.
    */
    std::unique_ptr<Entidad> obtenerNPCPasivo(const float x, 
                                              const float y, 
                                              const std::string &idNPC, 
                                              const std::string &idMapa);
};


#endif
