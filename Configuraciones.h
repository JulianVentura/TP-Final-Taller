#ifndef __CONFIGURACIONES__
#define __CONFIGURACIONES__

class Configuraciones{
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
    unsigned int calcularVidaMax();
    unsigned int calcularRecuperacionVida();
    unsigned int calcularManaMax();
    unsigned int calcularRecupManaMeditacion();
    unsigned int calcularRecupManaTiempo();
    unsigned int calcularDropOro();
    unsigned int calcularMaxOroSeguro();
    unsigned int calcularLimiteParaSubir();
    unsigned int calcularExpPorGolpe();
    unsigned int calcularExpPorMatar();
    unsigned int calcularDanioAtaque();
    bool seEsquivaElGolpe();
    unsigned int calcularDefensa();


};


#endif