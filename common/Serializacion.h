#ifndef __SERIALIZACION_H__
#define __SERIALIZACION_H__
#include <cstdint>
#define TAM_ID 20

typedef struct PosicionEncapsulada{
    char  id[TAM_ID];
    float x;
    float y;
}posicion_t;


struct serializacionEstado{
    char     id[20];
    uint16_t idArmaEquipada;
    uint16_t idArmaduraEquipada;
    uint16_t idCascoEquipado;
    uint16_t idEscudoEquipado;
    uint16_t idRaza;
    uint16_t idClase;
    uint16_t idEstado;
};

#endif