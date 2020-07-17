#ifndef __MENSAJE_H__
#define __MENSAJE_H__
#include <vector>
#include <cstdint>

class Mensaje{
    private:
    std::vector<char> buffer;
    Mensaje(std::vector<char> &&buffer);
    public:
    Mensaje();
    Mensaje(Mensaje &otro) = delete;
    Mensaje(Mensaje &&otro);
    Mensaje& operator=(Mensaje &otro) = delete;
    Mensaje& operator=(Mensaje &&otro) = delete;
    void agregarBytes(const char* mensaje, uint32_t tamanio);
    uint32_t obtenerTamanio();
    std::vector<char>& obtenerBytes();
};

#endif
