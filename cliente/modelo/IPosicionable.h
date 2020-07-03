#ifndef IPOSICIONABLE_H
#define IPOSICIONABLE_H

class IPosicionable {
public:
    virtual void actualizarPosicion(int x, int y);

protected:
    int x = 0; 
    int y = 0;
    bool esta_actualizado = false;
};

#endif
