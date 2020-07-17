#ifndef __PROXY_ENVIADOR_H__
#define __PROXY_ENVIADOR_H__

#include "../common/Thread.h"
#include "../common/ColaBloqueanteMensajes.h"
#include "../common/Mensaje.h"
#include "../common/commonSocket.h"

#define LIMITE_COLA_ENVIADOR 5000

class ProxyEnviador final : public Thread{
    private:
    ColaBloqueanteMensajes& colaMensajes;
    Socket& socket;

    public:
    ProxyEnviador(Socket &skt, ColaBloqueanteMensajes &cola);
    ProxyEnviador(ProxyEnviador &otro) = delete;
    ProxyEnviador(ProxyEnviador &&otro) = delete;
    ProxyEnviador& operator=(ProxyEnviador &otro) = delete;
    ProxyEnviador& operator=(ProxyEnviador &&otro) = delete;
    void procesar();
    ~ProxyEnviador();
};


#endif
