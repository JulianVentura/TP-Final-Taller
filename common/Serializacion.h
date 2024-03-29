#ifndef __SERIALIZACION_H__
#define __SERIALIZACION_H__
#include <cstdint>
#include <string>
#define TAM_ID 20
#define TAM_INVENTARIO 18
#define TAM_TIENDA TAM_INVENTARIO
#define ID_NO_EQUIPADO 0

typedef struct PosicionEncapsulada{
    char  id[TAM_ID];
    float x;
    float y;
}posicion_t;


typedef struct serializacionDibujado{
    char     id[TAM_ID];
    uint16_t idArmaEquipada;
    uint16_t idArmaduraEquipada;
    uint16_t idCascoEquipado;
    uint16_t idEscudoEquipado;
    uint16_t idRaza;
    uint16_t idClase;
    uint16_t idEstado;
} SerializacionDibujado;


typedef struct serializacionEstado{
    uint16_t vidaActual; 
    uint16_t vidaMaxima;
    uint16_t manaActual;
    uint16_t manaMaximo;
    uint16_t experiencia;
    uint16_t limiteParaSubir;
    uint16_t limiteExpInferior;
    uint32_t nivel;
}SerializacionEstado;

typedef struct serializacionItem{
    uint16_t idTCP;
    uint16_t precio;
}SerializacionItem;

typedef struct serializacionEquipo{
    uint16_t armaEquipada;
    uint16_t armaduraEquipada;
    uint16_t cascoEquipado;
    uint16_t escudoEquipado;
    uint16_t oro;
    SerializacionItem items[TAM_INVENTARIO];
}SerializacionEquipo;


typedef struct serializacionContenedor{
    uint16_t oroContenedor;
    SerializacionItem items[TAM_TIENDA];
}SerializacionContenedor;


struct serializacionPersonaje{
    uint32_t x, y;
    uint32_t vidaActual;
    uint32_t manaActual;
    uint32_t experiencia;
    uint32_t nivel;
    uint32_t cantidadOro;
    uint32_t oroEnAlmacen;
    uint16_t inventario[18];
    uint16_t almacen[18];
    uint32_t equipados[4];
    uint32_t penalidad;
}__attribute__((packed, aligned(4)));

typedef struct serializacionCliente{
    std::string idCliente;
    std::string idSala;
    struct serializacionPersonaje infoPersonaje;
}SerializacionCliente;


#endif
