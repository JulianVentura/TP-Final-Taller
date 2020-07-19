#include "ColaBloqueanteMensajes.h"
#include "Excepcion.h"
#include <utility> //Me lo pide el SERCOM para usar std::move

ColaBloqueanteMensajes::ColaBloqueanteMensajes() : 
                        conditionVariable(), 
                        cola(), 
                        mutex(),
                        colaCerrada(false),
                        tamanioBytesAlmacenados(0){}

Mensaje ColaBloqueanteMensajes::pop(){
    std::unique_lock<std::mutex> lock(this->mutex);
    while (this->cola.empty()){
        if (this->colaCerrada){
            throw Excepcion("Cola cerrada");
        }
        conditionVariable.wait(lock);
    }
    Mensaje unMensaje = std::move(this->cola.front());
    tamanioBytesAlmacenados -= unMensaje.obtenerTamanio();
    this->cola.pop();
    return unMensaje;
}
void ColaBloqueanteMensajes::push(Mensaje mensaje){
    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->colaCerrada){
        throw Excepcion("No se pueden encolar mas mensajes, la cola ha sido cerrada");
    }
    tamanioBytesAlmacenados += mensaje.obtenerTamanio();
    this->cola.push(std::move(mensaje));
    conditionVariable.notify_all();
}

void ColaBloqueanteMensajes::cerrarCola(){
    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->colaCerrada) return;
    this->colaCerrada = true;
    this->conditionVariable.notify_all();
}

uint32_t ColaBloqueanteMensajes::obtenerTamBytesAlmacenados(){
    return tamanioBytesAlmacenados;
}