#ifndef __PROXY_ENVIADOR_H__
#define __PROXY_ENVIADOR_H__

#include "../common/Thread.h"
#include "../common/ColaBloqueanteMensajes.h"
#include "../common/Mensaje.h"
#include "../common/commonSocket.h"

#define LIMITE_COLA_ENVIADOR 20000
#define MUESTRAS 20

class ProxyEnviador final : public Thread{
    private:
    int contador;
    ColaBloqueanteMensajes& colaMensajes;
    Socket& socket;

    public:
    ProxyEnviador(Socket &skt, ColaBloqueanteMensajes &cola);
    ProxyEnviador(ProxyEnviador &otro) = delete;
    ProxyEnviador(ProxyEnviador &&otro) = delete;
    ProxyEnviador& operator=(ProxyEnviador &otro) = delete;
    ProxyEnviador& operator=(ProxyEnviador &&otro) = delete;
    bool envioBloqueado();
    void procesar();
    ~ProxyEnviador();
};


#endif
