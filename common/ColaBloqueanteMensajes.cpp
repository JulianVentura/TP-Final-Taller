#include "ColaBloqueanteMensajes.h"
#include "ExcepcionColaCerrada.h"
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
            throw ExcepcionColaCerrada();
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
    this->cola.push(std::move(mensaje));
    tamanioBytesAlmacenados += mensaje.obtenerTamanio();
    conditionVariable.notify_all();
}

void ColaBloqueanteMensajes::cerrarCola(){
    std::unique_lock<std::mutex> lock(this->mutex);
    this->colaCerrada = true;
    this->conditionVariable.notify_all();
}

uint32_t ColaBloqueanteMensajes::obtenerTamBytesAlmacenados(){
    return tamanioBytesAlmacenados;
}