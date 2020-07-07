#ifndef IDIMENSIONABLE_H
#define IDIMENSIONABLE_H

class IDimensionable {
public:
    virtual int getAncho();
    virtual int getAlto();
    
protected:
    int ancho = 0;
    int alto = 0;
};
#endif
