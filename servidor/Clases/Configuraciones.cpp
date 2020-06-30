#include "Configuraciones.h"
#include "Entidad.h"
#include "Personaje.h"
#include "Arma.h"
#include "Excepcion.h"
#include <random>
#include <algorithm>
#include <ctime>

#define MILI_A_SEG 0.001

Configuraciones Configuraciones::instancia;
bool Configuraciones::instanciaCreada = false;

void Configuraciones::leerArchivo(const char* nombreArchivo){
    //Se levanta el archivo
}

Configuraciones::Configuraciones(){
    //Se crea
}

void Configuraciones::crearInstancia(const char* nombreArchivo){
    //Luego hay que levantar el archivo llamando al constructor
    Configuraciones::instancia.leerArchivo(nombreArchivo);
    Configuraciones::instanciaCreada = true;
}

Configuraciones* Configuraciones::obtenerInstancia(){
    if (!Configuraciones::instanciaCreada){
        throw Excepcion
        ("Se intento obtener la instancia de Configuraciones, pero esta no fue creada.");
    }
    return &Configuraciones::instancia;
}


unsigned int Configuraciones::calcularVidaMax(Personaje *personaje){
    //return Constitucion * FClaseVida * FRazaVida * Nivel
    return 100; //Cambiar
}
unsigned int Configuraciones::calcularRecuperacionVida(Personaje *personaje, double tiempo){
    //return FRazaRecuperacion * segundos * MILI_A_SEG
    return 20; //Cambiar
}
unsigned int Configuraciones::calcularManaMax(Personaje *personaje){
    //return Inteligencia * FClaseMana * FRazaMana * Nivel
    return 150; //Cambiar
}
unsigned int Configuraciones::calcularRecupManaMeditacion(Personaje *personaje, double tiempo){
    //return FClaseMeditacion * Inteligencia * segundos * MILI_A_SEG
    return 40; //Cambiar 
}
unsigned int Configuraciones::calcularRecupManaTiempo(Personaje *personaje, double tiempo){
    //return FRazaRecuperacion * segundos * MILI_A_SEG
    return 0;
}
unsigned int Configuraciones::calcularDropOro(Entidad *entidad){
    //return rand(0, 0.2) * VidaMaxNPC
    std::mt19937 rng(std::time(0));
    std::uniform_int_distribution<unsigned int> dist(0, 200);
    float suerte = dist(rng) / 1000;
    return suerte * entidad->vidaMaxima;
}
unsigned int Configuraciones::calcularMaxOroSeguro(Personaje *personaje){
    return 100 * std::pow(personaje->nivel, 1.1);
}
unsigned int Configuraciones::calcularLimiteParaSubir(Personaje *personaje){
    return 1000 * std::pow(personaje->nivel, 1.8);
}
unsigned int Configuraciones::calcularExpPorGolpe(Entidad *objetivo, Entidad *atacante, unsigned int danio){
    //return Danio * max(NivelDelOtro - Nivel + 10, 0)
    return danio * std::max(objetivo->nivel - atacante->nivel + 10, (unsigned int)0);
}
unsigned int Configuraciones::calcularExpPorMatar(Entidad *objetivo, Entidad *atacante){
    //return rand(0, 0.1) * VidaMaxDelOtro * max(NivelDelOtro - Nivel + 10, 0)
    std::mt19937 rng(std::time(0));
    std::uniform_int_distribution<unsigned int> dist(0, 100);
    float suerte = dist(rng) / 1000;
    return suerte * objetivo->vidaMaxima * std::max(objetivo->nivel - atacante->nivel + 10, (unsigned int)0);
}
unsigned int Configuraciones::calcularDanioAtaque(Entidad *objetivo, Entidad *atacante, Arma *arma){
    //return Fuerza * rand(DanioArmaMin, DanioArmaMax)
    std::mt19937 rng(std::time(0));
    std::uniform_int_distribution<unsigned int> dist(arma->danioMin, arma->danioMax);
    unsigned int danio = dist(rng);
    return danio;
}
bool Configuraciones::seEsquivaElGolpe(Entidad *entidad){
    //return rand(0, 1) ^ Agilidad < 0.001
    std::mt19937 rng(std::time(0));
    std::uniform_int_distribution<unsigned int> dist(0, 1000);
    float suerte = dist(rng) / 1000;
    return std::pow(suerte, entidad->agilidad) < 0.001;
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