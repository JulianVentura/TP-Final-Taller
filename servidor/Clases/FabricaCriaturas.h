#ifndef __FABRICA_CRIATURAS_H__
#define __FABRICA_CRIATURAS_H__
#include "Criatura.h"
#include <map>
#include <memory>
class FabricaCriaturas{
    private:
    const std::map<std::string, std::unique_ptr<Criatura>> &criaturas;
    unsigned long contador;

    bool idValido(std::string &id) const;
    public:
    FabricaCriaturas(const std::map<std::string, std::unique_ptr<Criatura>> &criaturas);
    std::unique_ptr<Criatura> obtenerCriaturaAleatoria(float x, float y);
};


#endif
/*

Las criaturas:

No se diferencian entre ellas en nada, podriamos setearles algunos valores genericos como:

- id
- Vel mov
- Arma que llevan
- Vida max
- Agilidad
- Nivel

Estos datos van a estar en el archivo de configuraciones, por lo tanto por cada creacion de una
nueva criatura se le debera preguntar a que tipo pertenece y luego crear la criatura con esos datos segun corresponda.

La fabrica de criaturas se encarga de:

- Conocer a todas las criaturas del juego, leyendo de Configuraciones.
- Crear una criatura con los atributos que le corresponden.
- Almacenar una lista de las criaturas que un mapa puede spawnear.
- Tener acceso a las criaturas actuales en el mapa, a modo de poder crear un id unico para cada criatura.


*/