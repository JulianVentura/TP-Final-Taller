#include "Configuraciones.h"

unsigned int Configuraciones::calcularVidaMax(){
    //return Constitucion * FClaseVida * FRazaVida * Nivel
}
unsigned int Configuraciones::calcularRecuperacionVida(){
    //return FRazaRecuperacion * segundos
}
unsigned int Configuraciones::calcularManaMax(){
    //return Inteligencia * FClaseMana * FRazaMana * Nivel
}
unsigned int Configuraciones::calcularRecupManaMeditacion(){
    //return FClaseMeditacion * Inteligencia * segundos
}
unsigned int Configuraciones::calcularRecupManaTiempo(){
    //return FRazaRecuperacion * segundos
}
unsigned int Configuraciones::calcularDropOro(){
    //return rand(0, 0.2) * VidaMaxNPC
}
unsigned int Configuraciones::calcularMaxOroSeguro(){
    //return 100 * Nivel^1.1
}
unsigned int Configuraciones::calcularLimiteParaSubir(){
    //return 1000 * Nivel^1.8
}
unsigned int Configuraciones::calcularExpPorGolpe(){
    //return Danio * max(NivelDelOtro - Nivel + 10, 0)
}
unsigned int Configuraciones::calcularExpPorMatar(){
    //return rand(0, 0.1) * VidaMaxDelOtro * max(NivelDelOtro - Nivel + 10, 0)
}
unsigned int Configuraciones::calcularDanioAtaque(){
    //return Fuerza * rand(DanioArmaMin, DanioArmaMax)
}
bool Configuraciones::seEsquivaElGolpe(){
    //return rand(0, 1) ^ Agilidad < 0.001
}
unsigned int Configuraciones::calcularDefensa(){
    //return rand(ArmaduraMin, ArmaduraMax) + rand(EscudoMin, EscudoMax) + rand(CascoMin, CascoMax)
}

/*
Ver como implementar la probabilidad de drop
0.8 Nada
0.1 Oro
0.05 Pocio de vida o mana al azar
0.05 Cualquier otro objeto al azar
*/