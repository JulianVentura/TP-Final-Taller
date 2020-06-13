#ifndef __RECTANGULO_H__
#define __RECTANGULO_H__

class Rectangulo{
    private:
    const float inicioX;
    const float inicioY;
    const float ancho;
    const float alto;
    public:
    Rectangulo(const float inicioX, 
               const float inicioY, 
               const float ancho, 
               const float alto);
    Rectangulo(Rectangulo &&otro);
    Rectangulo(Rectangulo &otro) = delete;
    bool seSuperponeCon(Rectangulo &rectangulo);
    bool contieneA(Rectangulo &rectangulo);
    float obtenerX();
    float obtenerY();
    float obtenerAncho();
    float obtenerAlto();

};


#endif
