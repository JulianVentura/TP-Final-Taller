#include "ProxyEnviador.h"

ProxyEnviador::ProxyEnviador(Socket &skt, 
                                           ColaBloqueanteMensajes &cola) :
                                           contador(0), 
                                           colaMensajes(cola),
                                           socket(skt){}

void ProxyEnviador::procesar(){
    bool continuar = true;
    while (continuar){
        try{
            Mensaje mensaje = std::move(colaMensajes.pop());
            socket.enviar(mensaje.obtenerBytes().data(), mensaje.obtenerTamanio());
        }catch(...){
            //Cualquier excepcion o error que salte es motivo suficiente como para finalizar.
            //No me interesa reportar el error.
            continuar = false;
	        colaMensajes.cerrarCola();
        }
    }
}

bool ProxyEnviador::envioBloqueado(){
  contador++;
  if(contador > MUESTRAS && colaMensajes.obtenerTamBytesAlmacenados()
   >=  LIMITE_COLA_ENVIADOR){
     return true;
  }
  return false;
}

ProxyEnviador::~ProxyEnviador(){}
