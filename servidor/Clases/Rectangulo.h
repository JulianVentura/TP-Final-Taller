#ifndef __RECTANGULO_H__
#define __RECTANGULO_H__

class Rectangulo{
    private:
    float inicioX = 0; // Lo agrego porque con el constr sin parametros
    float inicioY = 0; // quede sin inicializarse y valgrind jode
    float ancho = 0;
    float alto = 0;
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
