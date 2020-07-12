#ifndef __CODIGOS_OPERACION_H__
#define __CODIGOS_OPERACION_H__
#include <cstdint>

#define TAM_CONTRASENIA 20

enum CODIGOS : uint32_t {
                         CODIGO_POSICIONES,
                         CODIGO_ID,
                         CODIGO_CARGA_MAPA,
                         CODIGO_MOVIMIENTO,
                         CODIGO_MENSAJE_CHAT,
                         CODIGO_DESCONECTAR,
			             CODIGO_NUEVO_PERSONAJE,
                         CODIGO_CONFIRMACION,
                         CODIGO_ERROR,
                         OP_INFO_JUGADOR,
                         CODIGO_INTERACCION,
                         CODIGO_COMPRA,
                         CODIGO_VENTA,
                         CODIGO_UTILIZACION,
                         CODIGO_TIRADO,
                         CODIGO_ATAQUE,
                         CODIGO_INVENTARIO,
                         CODIGO_TIENDA,
                         CODIGO_ESTADISTICAS,
			             CODIGO_ESTADOS
};

enum MOVIMIENTO : uint32_t {
                         ARRIBA,
                         ABAJO,
                         DERECHA,
                         IZQUIERDA,
                         DETENERSE
};

#endif
