#include "Configuraciones.h"

unsigned int Configuraciones::calcularVidaMax(){
    //return Constitucion * FClaseVida * FRazaVida * Nivel
    return 0;
}
unsigned int Configuraciones::calcularRecuperacionVida(){
    //return FRazaRecuperacion * segundos
    return 0;
}
unsigned int Configuraciones::calcularManaMax(){
    //return Inteligencia * FClaseMana * FRazaMana * Nivel
    return 0;
}
unsigned int Configuraciones::calcularRecupManaMeditacion(){
    //return FClaseMeditacion * Inteligencia * segundos
    return 0;
}
unsigned int Configuraciones::calcularRecupManaTiempo(){
    //return FRazaRecuperacion * segundos
    return 0;
}
unsigned int Configuraciones::calcularDropOro(){
    //return rand(0, 0.2) * VidaMaxNPC
    return 0;
}
unsigned int Configuraciones::calcularMaxOroSeguro(){
    //return 100 * Nivel^1.1
    return 0;
}
unsigned int Configuraciones::calcularLimiteParaSubir(){
    //return 1000 * Nivel^1.8
    return 0;
}
unsigned int Configuraciones::calcularExpPorGolpe(){
    //return Danio * max(NivelDelOtro - Nivel + 10, 0)
    return 0;
}
unsigned int Configuraciones::calcularExpPorMatar(){
    //return rand(0, 0.1) * VidaMaxDelOtro * max(NivelDelOtro - Nivel + 10, 0)
    return 0;
}
unsigned int Configuraciones::calcularDanioAtaque(){
    //return Fuerza * rand(DanioArmaMin, DanioArmaMax)
    return 0;
}
bool Configuraciones::seEsquivaElGolpe(){
    //return rand(0, 1) ^ Agilidad < 0.001
    return 0;
}
unsigned int Configuraciones::calcularDefensa(){
    //return rand(ArmaduraMin, ArmaduraMax) + rand(EscudoMin, EscudoMax) + rand(CascoMin, CascoMax)
    return 0;
}

/*
Ver como implementar la probabilidad de drop
0.8 Nada
0.1 Oro
0.05 Pocio de vida o mana al azar
0.05 Cualquier otro objeto al azar
*/