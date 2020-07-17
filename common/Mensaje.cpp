#include "Mensaje.h"
#include <cstring>
#include <utility>

Mensaje::Mensaje() : buffer(0){}
Mensaje::Mensaje(Mensaje &&otro) : Mensaje(std::move(otro.buffer)){
    otro.buffer.clear();
}

Mensaje::Mensaje(std::vector<char> &&buf) : buffer(std::move(buf)){}

void Mensaje::agregarBytes(const char* mensaje, uint32_t tamanio){
    const char* final = mensaje + tamanio;
    buffer.insert(buffer.end(), mensaje, final);
}
uint32_t Mensaje::obtenerTamanio(){
    return buffer.size();
}
std::vector<char>& Mensaje::obtenerBytes(){
    return buffer;
}