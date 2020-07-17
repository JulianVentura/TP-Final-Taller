#ifndef __CLIENTE_PROXY_ENVIADOR_H__
#define __CLIENTE_PROXY_ENVIADOR_H__
#include "Thread.h"
#include "../../common/ColaBloqueanteMensajes.h"
#include "../../common/Mensaje.h"
#include "../../common/commonSocket.h"

class ClienteProxyEnviador : public Thread{
    private:
    ColaBloqueanteMensajes& colaMensajes;
    Socket& socket;
    public:
    ClienteProxyEnviador(Socket &skt, ColaBloqueanteMensajes &cola);
    ClienteProxyEnviador(ClienteProxyEnviador &otro) = delete;
    ClienteProxyEnviador(ClienteProxyEnviador &&otro) = delete;
    ClienteProxyEnviador& operator=(ClienteProxyEnviador &otro) = delete;
    ClienteProxyEnviador& operator=(ClienteProxyEnviador &&otro) = delete;
    void procesar();

};


#endif
