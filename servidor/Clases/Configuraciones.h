#ifndef __CONFIGURACIONES_H__
#define __CONFIGURACIONES_H__
class Entidad;
class Personaje;
class Arma;
class Configuraciones{
    private:

    //Atributos publicos
    public:
    //Vida de razas
    unsigned int FHumanoVida;
    unsigned int FElfoVida;
    unsigned int FEnanoVida;
    unsigned int FGnomoVida;
    //Vida de clases
    unsigned int FMagoVida;
    unsigned int FClerigoVida;
    unsigned int FPaladinVida;
    unsigned int FGuerreroVida;
    //Mana de razas
    unsigned int FHumanoMana;
    unsigned int FElfoMana;
    unsigned int FEnanoMana;
    unsigned int FGnomoMana;
    //Mana de clases
    unsigned int FMagoMana;
    unsigned int FClerigoMana;
    unsigned int FPaladinMana;
    unsigned int FGuerreroMana;
    //Recuperacion de raza
    unsigned int FHumanoRecuperacion;
    unsigned int FElfoRecuperacion;
    unsigned int FEnanoRecuperacion;
    unsigned int FGnomoRecuperacion;
    //Recuperacion de clase
    unsigned int FMagoRecuperacion;
    unsigned int FClerigoRecuperacion;
    unsigned int FPaladinRecuperacion;
    unsigned int FGuerreroRecuperacion;
    //Meditacion de clase
    unsigned int FMagoMeditacion;
    unsigned int FClerigoMeditacion;
    unsigned int FPaladinMeditacion;
    unsigned int FGuerreroMeditacion;
    //Metodos
    static Configuraciones* obtenerInstancia();
    static void crearInstancia(const char *nombreArchivo);


    unsigned int calcularVidaMax(Personaje *personaje);
    unsigned int calcularRecuperacionVida(Personaje *personaje, double tiempo);
    unsigned int calcularManaMax(Personaje *personaje);
    unsigned int calcularRecupManaMeditacion(Personaje *personaje, double tiempo);
    unsigned int calcularRecupManaTiempo(Personaje *personaje, double tiempo);
    unsigned int calcularDropOro(Entidad *entidad);
    unsigned int calcularMaxOroSeguro(Personaje *personaje);
    unsigned int calcularLimiteParaSubir(Personaje *personaje);
    unsigned int calcularExpPorGolpe(Entidad *objetivo, Entidad *atacante, unsigned int danio);
    unsigned int calcularExpPorMatar(Entidad *objetivo, Entidad *atacante);
    unsigned int calcularDanioAtaque(Entidad *objetivo, Entidad *atacante, Arma *arma);
    bool seEsquivaElGolpe(Entidad *entidad);
    unsigned int calcularDefensa();

    protected:
    Configuraciones(const char* nombreArchivo);
    static Configuraciones instancia;
    static bool instanciaCreada;

};


#endif