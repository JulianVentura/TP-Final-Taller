#ifndef PERSONAJE_H
#define PERSONAJE_H

class MovibleVista;

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
    int velocidadX = 0; // TODO: Esto estaría en el servidor
    int velocidadY = 0; // TODO: Esto estaría en el servidor
    friend class PersonajeVista;
    friend class MovibleVista;
};

#endif
