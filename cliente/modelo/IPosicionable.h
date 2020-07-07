#ifndef IPOSICIONABLE_H
#define IPOSICIONABLE_H

class IPosicionable {
public:
    void actualizarPosicion(int x, int y);
    int getX() const;
    int getY() const;
    bool esta_actualizado() const;
    void consumirActualizacion();

private:
    int x = 0; 
    int y = 0;
    bool _esta_actualizado = false;
};

#endif
