#ifndef PERSONAJE_H
#define PERSONAJE_H

class Personaje/*Mock*/ {
public:
    void actualizar();
    void moverDerecha();
    void moverIzquierda();
    void moverArriba();
    void moverAbajo();
    void detenerse();

private:
    int x = 0;
    int y = 0;
    int velocidadX = 0; // Esto estaría en el servidor
    int velocidadY = 0; // Esto estaría en el servidor
    friend class PersonajeVista;
};

#endif
