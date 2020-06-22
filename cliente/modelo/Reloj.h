#ifndef RELOJ_H
#define RELOJ_H
#include <chrono>

typedef std::chrono::high_resolution_clock reloj_t;
class Reloj {
public:
    explicit Reloj();
    double medir();
private:
    std::chrono::time_point<reloj_t> comienzo;
    std::chrono::time_point<reloj_t> fin;
};

#endif
