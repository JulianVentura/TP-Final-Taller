#include "Thread.h"


Thread::Thread() : estaCorriendo(false){}

void  Thread::recuperar(){
    if (estaCorriendo){
        this->thread.join();
        estaCorriendo = false;
    }
}
void  Thread::comenzar(){
    if (estaCorriendo) return;
    this->thread = std::thread(&Thread::procesar, this);
    estaCorriendo = true;
}
Thread::~Thread(){
    recuperar();
}

