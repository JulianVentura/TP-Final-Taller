#ifndef __RECTANGULO_H__
#define __RECTANGULO_H__

class Rectangulo{
    private:
    float inicioX;
    float inicioY;
    float ancho;
    float alto;
    public:
    /*
    El constructor sin parametros me permite parsear con JSON
    */
    Rectangulo();
    Rectangulo(const float inicioX, 
               const float inicioY, 
               const float ancho, 
               const float alto);
    Rectangulo(Rectangulo &&otro);
    Rectangulo(Rectangulo &otro) = delete;
    Rectangulo& operator=(Rectangulo &&otro);
    bool seSuperponeCon(Rectangulo &rectangulo);
    bool contieneA(Rectangulo &rectangulo);
    float obtenerX();
    float obtenerY();
    float obtenerAncho();
    float obtenerAlto();
    /*
    Me permite parsear con JSON
    */
    void set(float x, float y, float ancho, float alto);
};


#endif
