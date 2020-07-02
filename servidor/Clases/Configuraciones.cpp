#include "Configuraciones.h"
#include "Entidad.h"
#include "Personaje.h"
#include "Arma.h"
#include "Excepcion.h"
#include <random>
#include <algorithm>
#include <ctime>
#include <fstream>

#define MILI_A_SEG 0.001

Configuraciones Configuraciones::instancia;
bool Configuraciones::instanciaCreada = false;

void Configuraciones::leerArchivo(const char* nombreArchivo){
    std::ifstream archivoEntrada(nombreArchivo);
    if (!archivoEntrada.is_open()){
        throw Excepcion
        ("Error: No se ha podido abrir el archivo de nombre %s", nombreArchivo);
    }
    archivoEntrada >> json;
}

Configuraciones::Configuraciones(){
    //Se crea
}

void Configuraciones::crearInstancia(const char* nombreArchivo){
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

/* GETTERS DEL JUEGO */

//Aceptador
const uint32_t Configuraciones::obtenerAceptadorNumConexionesEnEspera() const{
    return json.at("Aceptador").at("NUM_CONEXIONES_EN_ESPERA").get<uint32_t>();
}
//GameLoop
const uint32_t Configuraciones::obtenerGameLoopMSdescanso() const{
    return json.at("GameLoop").at("MS_DESCANSO").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerGameLoopMSporActualizacion() const{
    return json.at("GameLoop").at("MS_POR_ACTUALIZACION").get<uint32_t>();
}
//Mapas
const std::string Configuraciones::obtenerMapaRuta(std::string &id) const{
    return json.at("Mapas").at(id).at("Ruta").get<std::string>();
}
const std::vector<std::string> Configuraciones::obtenerMapaSpawnCriaturas(std::string &id) const{
    return json.at("Mapas").at(id).at("SpawnCriaturas").get<std::vector<std::string>>();
}
const uint32_t Configuraciones::obtenerMapaLimiteCriaturas(std::string &id) const{
    return json.at("Mapas").at(id).at("LimiteCriaturas").get<uint32_t>();
}
//Personaje
const uint32_t Configuraciones::obtenerPersonajeNivelBase() const{
    return json.at("Personaje").at("NivelBase").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerPersonajeFuerzaBase() const{
    return json.at("Personaje").at("FuerzaBase").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerPersonajeInteligenciaBase() const{
    return json.at("Personaje").at("InteligenciaBase").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerPersonajeAgilidadBase() const{
    return json.at("Personaje").at("AgilidadBase").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerPersonajeComposicionBase() const{
    return json.at("Personaje").at("ComposicionBase").get<uint32_t>();
}
const float Configuraciones::obtenerPersonajeVelDesplazamiento() const{
    return json.at("Personaje").at("VelDesplazamiento").get<float>();
}
const uint32_t Configuraciones::obtenerPersonajeAncho() const{
    return json.at("Personaje").at("Ancho").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerPersonajeAlto() const{
    return json.at("Personaje").at("Alto").get<uint32_t>();
}
//Ciudadanos
const uint32_t Configuraciones::obtenerCiudadanoAncho(std::string &id) const{
    return json.at("Ciudadanos").at(id).at("Ancho").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCiudadanoAlto(std::string &id) const{
    return json.at("Ciudadanos").at(id).at("Alto").get<uint32_t>();
}
//Criaturas
const uint32_t Configuraciones::obtenerCriaturaVidaMax(std::string &id) const{
    return json.at("Criaturas").at(id).at("VidaMax").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaNivel(std::string &id) const{
    return json.at("Criaturas").at(id).at("Nivel").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaFuerza(std::string &id) const{
    return json.at("Criaturas").at(id).at("Fuerza").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaInteligencia(std::string &id) const{
    return json.at("Criaturas").at(id).at("Inteligencia").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaAgilidad(std::string &id) const{
    return json.at("Criaturas").at(id).at("Agilidad").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaConstitucion(std::string &id) const{
    return json.at("Criaturas").at(id).at("Constitucion").get<uint32_t>();
}
const float Configuraciones::obtenerCriaturaVelDesplazamiento(std::string &id) const{
    return json.at("Criaturas").at(id).at("VelDesplazamiento").get<float>();
}
const uint32_t Configuraciones::obtenerCriaturaAncho(std::string &id) const{
    return json.at("Criaturas").at(id).at("Ancho").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaAlto(std::string &id) const{
    return json.at("Criaturas").at(id).at("Alto").get<uint32_t>();
}
//Clases
const float Configuraciones::obtenerFClaseVida(std::string &id) const{
    return json.at("Clases").at(id).at("FClaseVida").get<float>();
}
const float Configuraciones::obtenerFClaseRecuperacion(std::string &id) const{
    return json.at("Clases").at(id).at("FClaseRecuperacion").get<float>();
}
const float Configuraciones::obtenerFClaseMeditacion(std::string &id) const{
    return json.at("Clases").at(id).at("FClaseMeditacion").get<float>();
}
const uint32_t Configuraciones::obtenerClaseMejoraFuerzaEnSubida(std::string &id) const{
    return json.at("Clases").at(id).at("MejoraFuerzaEnSubida").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerClaseMejoraInteligenciaEnSubida(std::string &id) const{
    return json.at("Clases").at(id).at("MejoraInteligenciaEnSubida").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerClaseMejoraAgilidadEnSubida(std::string &id) const{
    return json.at("Clases").at(id).at("MejoraAgilidadEnSubida").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerClaseMejoraConstitucionEnSubida(std::string &id) const{
    return json.at("Clases").at(id).at("MejoraConstitucionEnSubida").get<uint32_t>();
}
//Razas
const float Configuraciones::obtenerFRazaVida(std::string &id) const{
    return json.at("Razas").at(id).at("FRazaVida").get<float>();
}
const float Configuraciones::obtenerFRazaRecuperacion(std::string &id) const{
    return json.at("Razas").at(id).at("FRazaRecuperacion").get<float>();
}
const float Configuraciones::obtenerFRazaMeditacion(std::string &id) const{
    return json.at("Razas").at(id).at("FRazaMeditacion").get<float>();
}
const uint32_t Configuraciones::obtenerRazaMejoraFuerzaEnSubida(std::string &id) const{
    return json.at("Razas").at(id).at("MejoraFuerzaEnSubida").get<float>();
}
const uint32_t Configuraciones::obtenerRazaMejoraInteligenciaEnSubida(std::string &id) const{
    return json.at("Razas").at(id).at("MejoraInteligenciaEnSubida").get<float>();
}
const uint32_t Configuraciones::obtenerRazaMejoraAgilidadEnSubida(std::string &id) const{
    return json.at("Razas").at(id).at("MejoraAgilidadEnSubida").get<float>();
}
const uint32_t Configuraciones::obtenerRazaMejoraConstitucionEnSubida(std::string &id) const{
    return json.at("Razas").at(id).at("MejoraConstitucionEnSubida").get<float>();
}
//Armas
const int32_t  Configuraciones::obtenerArmaDanioMax(std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("DanioMax").get<int32_t>();
}
const int32_t  Configuraciones::obtenerArmaDanioMin(std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("DanioMin").get<int32_t>();
}
const uint32_t Configuraciones::obtenerArmaRangoAtaque(std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("Rango").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerArmaConsumoMana(std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("ConsumoMana").get<uint32_t>();
}
//Armaduras
const uint32_t  Configuraciones::obtenerArmaduraDefensaMax(std::string &id) const{
    return json.at("Items").at("Armaduras").at(id).at("DefensaMax").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerArmaduraDefensaMin(std::string &id) const{
    return json.at("Items").at("Armaduras").at(id).at("DefensaMin").get<uint32_t>();
}
//Escudos
const uint32_t  Configuraciones::obtenerEscudoDefensaMax(std::string &id) const{
    return json.at("Items").at("Escudos").at(id).at("DefensaMax").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerEscudoDefensaMin(std::string &id) const{
    return json.at("Items").at("Escudos").at(id).at("DefensaMin").get<uint32_t>();
}
//Cascos
const uint32_t  Configuraciones::obtenerCascoDefensaMax(std::string &id) const{
    return json.at("Items").at("Cascos").at(id).at("DefensaMax").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerCascoDefensaMin(std::string &id) const{
    return json.at("Items").at("Cascos").at(id).at("DefensaMin").get<uint32_t>();
}
//Oro
const uint32_t  Configuraciones::obtenerOroCantidadMax() const{
    return json.at("Items").at("Oro").at("CantidadMaxima").get<uint32_t>();
}
//Pociones
const uint32_t  Configuraciones::obtenerCuracionVida(std::string &id) const{
    return json.at("Items").at("Pociones").at(id).at("CuracionVida").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerCuracionMana(std::string &id) const{
    return json.at("Items").at("Pociones").at(id).at("CuracionMana").get<uint32_t>();
}




/* FORMULAS DEL JUEGO */


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

/*

Criatura::actualizarEstado(Mapa *mapa){
    if (enPersecucion){
        perseguirObjetivo(mapa);
        return;
    }
    //objetivo es un puntero a Entidad, atributo de la instancia ->> Entidad *objetivo;
    float distMenor = 0;
    float distActual = 0;
    std::vector<Entidad*> resultado = mapa.obtenerCercanos(this);
    for (auto entidad : resultado){
        distActual = this->posicion.calcularDistancia(entidad->obtenerPosicion());
        if (distActual < distMenor){
            objetivo = entidad;
            distMenor = distActual;
        }
    }
    perseguirObjetivo(mapa);
}

Criatura::perseguirObjetivo(Mapa *mapa){
    Posicion nuevaPosicion = this->posicion.perseguir(objetivo->obtenerPosicion());
    mapa->actualizarPosicion(this, nuevaPosicion);
}

*/




/*

Operacion:

Delega el comportamiento en el NPC, pasandole un puntero a Cliente.




NPCS:

Interactuar

Banquero:           Primero se obtiene los items de la ventana en la operacion "interactuar", luego se le pide comprar con una posicion determinada
Comerciante:        
BolsaDeItems:       


Sacerdote:          
Teletransportador:



*/