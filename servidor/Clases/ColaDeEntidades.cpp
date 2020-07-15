#include "ColaDeEntidades.h"

ColaDeEntidades::ColaDeEntidades() : cola(),
                                     mutex(){}

Entidad* ColaDeEntidades::pop(){
    std::unique_lock<std::mutex> lock(this->mutex);
    if (this->cola.empty()){
        return nullptr;
    }
    Entidad* entidad = this->cola.front();
    this->cola.pop();
    return entidad;
}
void ColaDeEntidades::push(Entidad* entidad){
    std::unique_lock<std::mutex> lock(this->mutex);
    this->cola.push(entidad);
}

ColaDeEntidades::~ColaDeEntidades(){}