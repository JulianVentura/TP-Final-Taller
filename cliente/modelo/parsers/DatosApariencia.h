#ifndef DATOSABARIENCIA_H
#define DATOSABARIENCIA_H
#include <string>
#include <unordered_map>
#include <vector>

typedef struct DatosApariencia {
    std::string arma;
    std::string casco;
    std::string escudo;
    std::string armadura;
    std::string raza;
    std::string clase;
    std::string estado;
    std::string tipo;
    bool operator==(const DatosApariencia &otro) const;
} DatosApariencia;
class Imagen;
typedef std::unordered_map<std::string, std::vector<Imagen*>> imagenes_t;

#endif
