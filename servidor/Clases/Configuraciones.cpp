#include "Configuraciones.h"
#include "Entidad.h"
#include "Personaje.h"
#include "Raza.h"
#include "Clase.h"
#include "Arma.h"
#include "Armadura.h"
#include "Escudo.h"
#include "Casco.h"
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
    srand(time(NULL));
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

/* METODOS AUXILIARES */

static bool floatComp(float a, float b, float epsilon = 0.0001){
    return fabs(a - b) < epsilon;
}

static unsigned int numeroRandom(unsigned int a, unsigned int b){
    return rand() % (b - a) + a + 1;
}


/* GETTERS DEL JUEGO */
//Salas
const std::vector<std::string> Configuraciones::obtenerSalas() const{
    return json.at("Salas").get<std::vector<std::string>>();
}
//Aceptador
const uint32_t Configuraciones::obtenerAceptadorNumConexionesEnEspera() const{
    return json.at("Aceptador").at("NUM_CONEXIONES_EN_ESPERA").get<uint32_t>();
}
const std::string Configuraciones::obtenerAceptadorPuerto() const{
    return json.at("Aceptador").at("Puerto").get<std::string>();
}
const std::string Configuraciones::obtenerAceptadorHost() const{
    return json.at("Aceptador").at("Host").get<std::string>();
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
const uint32_t Configuraciones::obtenerMapaLimiteCriaturas(std::string &id) const{
    return json.at("Mapas").at(id).at("LimiteCriaturas").get<uint32_t>();
}
const std::string Configuraciones::obtenerMapaInicial() const{
    return json.at("MapaInicial").get<std::string>();
}
const std::pair<float, float> Configuraciones::obtenerMapaPosicionSpawn(std::string &id) const{
    return json.at("Mapas").at(id).at("PosicionSpawnInicial").get<std::pair<float, float>>();
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
const uint32_t Configuraciones::obtenerPersonajeConstitucionBase() const{
    return json.at("Personaje").at("ConstitucionBase").get<uint32_t>();
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
    return json.at("Criaturas").at(id).at("Vida").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaManaMax(std::string &id) const{
    return json.at("Criaturas").at(id).at("Mana").get<uint32_t>();
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
const std::string Configuraciones::obtenerCriaturaIdArma(std::string &id) const{
    return json.at("Criaturas").at(id).at("IdArma").get<std::string>();
}
//Clases
const float Configuraciones::obtenerFClaseVida(std::string &id) const{
    return json.at("Clases").at(id).at("FClaseVida").get<float>();
}
const float Configuraciones::obtenerFClaseMana(std::string &id) const{
    return json.at("Clases").at(id).at("FClaseMana").get<float>();
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
const float Configuraciones::obtenerFRazaMana(std::string &id) const{
    return json.at("Razas").at(id).at("FRazaMana").get<float>();
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
const float Configuraciones::obtenerArmaRangoAtaque(std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("Rango").get<float>();
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
const uint32_t  Configuraciones::obtenerPocionCuracionVida(std::string &id) const{
    return json.at("Items").at("Pociones").at(id).at("CuracionVida").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerPocionCuracionMana(std::string &id) const{
    return json.at("Items").at("Pociones").at(id).at("CuracionMana").get<uint32_t>();
}




/* FORMULAS DEL JUEGO */


unsigned int Configuraciones::calcularVidaMax(Personaje *personaje){
    return personaje->constitucion * personaje->clase.FClaseVida * personaje->raza.FRazaVida * personaje->nivel;
}

unsigned int Configuraciones::calcularRecuperacionVida(Personaje *personaje, double tiempo){
    return personaje->raza.FRazaRecuperacion * tiempo * MILI_A_SEG;
}

unsigned int Configuraciones::calcularManaMax(Personaje *personaje){
    return personaje->inteligencia * personaje->clase.FClaseMana * personaje->raza.FRazaMana * personaje->nivel;
}

unsigned int Configuraciones::calcularRecupManaMeditacion(Personaje *personaje, double tiempo){
    return personaje->clase.FClaseMeditacion * personaje->inteligencia * tiempo * MILI_A_SEG;
}

unsigned int Configuraciones::calcularRecupManaTiempo(Personaje *personaje, double tiempo){
    return personaje->raza.FRazaRecuperacion * tiempo * MILI_A_SEG;
}

unsigned int Configuraciones::calcularDropOro(Entidad *entidad){
    //return rand(0, 0.2) * VidaMaxNPC
    float suerte = numeroRandom(0, 2000) / 10000;
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
    float suerte = numeroRandom(0, 1000) / 10000;
    return suerte * objetivo->vidaMaxima * std::max(objetivo->nivel - atacante->nivel + 10, (unsigned int)0);
}

unsigned int Configuraciones::calcularDanioAtaque(Entidad *objetivo, Entidad *atacante, Arma *arma){
    //return Fuerza * rand(DanioArmaMin, DanioArmaMax)
    return atacante->fuerza * numeroRandom(arma->danioMin, arma->danioMax);
}

bool Configuraciones::seEsquivaElGolpe(Entidad *entidad){
    //return rand(0, 1) ^ Agilidad < 0.001
    float suerte = rand()/RAND_MAX;
    return std::pow(suerte, entidad->agilidad) < 0.001;
}

unsigned int Configuraciones::calcularDefensa(Personaje *personaje){
    unsigned int temp = 0;
    if (personaje->armadura)
        temp = numeroRandom(personaje->armadura->defensaMin, personaje->armadura->defensaMin);
    if (personaje->escudo)
        temp += numeroRandom(personaje->escudo->defensaMin, personaje->escudo->defensaMin);
    if (personaje->casco)
        temp += numeroRandom(personaje->casco->defensaMin, personaje->casco->defensaMin);
    return temp;
}

unsigned int Configuraciones::calcularFuerza(Personaje *personaje){
    unsigned int fuerzaBase = this->obtenerPersonajeFuerzaBase();
    return fuerzaBase + personaje->nivel * personaje->raza.mejoraFuerzaEnSubida * personaje->clase.mejoraFuerzaEnSubida;
}

unsigned int Configuraciones::calcularInteligencia(Personaje *personaje){
    unsigned int inteligenciaBase = this->obtenerPersonajeInteligenciaBase();
    return inteligenciaBase + personaje->nivel * personaje->raza.mejoraInteligenciaEnSubida * personaje->clase.mejoraInteligenciaEnSubida;
}
unsigned int Configuraciones::calcularAgilidad(Personaje *personaje){
    unsigned int agilidadBase = this->obtenerPersonajeAgilidadBase();
    return agilidadBase + personaje->nivel * personaje->raza.mejoraAgilidadEnSubida * personaje->clase.mejoraAgilidadEnSubida;
}
unsigned int Configuraciones::calcularConstitucion(Personaje *personaje){
    unsigned int constitucionBase = this->obtenerPersonajeConstitucionBase();
    return constitucionBase + personaje->nivel * personaje->raza.mejoraConstitucionEnSubida * personaje->clase.mejoraConstitucionEnSubida;
}

/* DROPS */

std::string Configuraciones::calcularDropArma(std::string &idCriatura){
    return obtenerItemRandom(idCriatura, "Armas");
}

std::string Configuraciones::calcularDropArmadura(std::string &idCriatura){
    return obtenerItemRandom(idCriatura, "Armaduras");
}

std::string Configuraciones::calcularDropEscudo(std::string &idCriatura){
    return obtenerItemRandom(idCriatura, "Escudos");
}

std::string Configuraciones::calcularDropCasco(std::string &idCriatura){
    return obtenerItemRandom(idCriatura, "Cascos");
}

std::string Configuraciones::calcularDropPocion(std::string &idCriatura){
    return obtenerItemRandom(idCriatura, "Pociones");
}


unsigned int Configuraciones::calcularDropOro(std::string &idCriatura){
    unsigned int dropMax = json.at("Criaturas").at(idCriatura).at("Drops").at("Oro").at("DropMax").get<unsigned int>();
    unsigned int dropMin = json.at("Criaturas").at(idCriatura).at("Drops").at("Oro").at("DropMin").get<unsigned int>();
    return numeroRandom(dropMin, dropMax);
}

std::string Configuraciones::obtenerItemRandom(std::string &idCriatura, std::string idItem){
    std::vector<std::pair<std::string, float>> posibles = json.at("Criaturas").at(idCriatura).at("Drops").at(idItem).at("Posibles").get<std::vector<std::pair<std::string, float>>>();
    if (posibles.size() == 0){
        //Represento un no-drop como una cadena vacia.
        return "";
    }
    std::vector<float> probas;
    for (std::size_t i=0; i<posibles.size(); i++){
        if (i == 0){
            probas.push_back(posibles[0].second);
            continue;
        }
        probas.push_back(posibles[i].second + probas[i-1]);
    }
    if (!floatComp(probas[probas.size()-1], 1)){
        throw Excepcion
        ("Error: Se ha solicitado el calculo de una probabilidad para el item %s de la criatura %s, "
        "pero las probabilidades no suman 1");
    }
    float resultado = (float) rand()/RAND_MAX;

    if (resultado < probas[0]) return posibles[0].first;   //Devuelvo el id que le corresponde a 0
    for (std::size_t i=1; i<probas.size(); i++){
        if (resultado <= probas[i] && resultado >= probas[i-1]) return posibles[i].first;
    }
    //Le pifio al 1
    return posibles[posibles.size()-1].first;
}

TipoItem Configuraciones::calcularDrop(std::string &idCriatura){
    float probaArma = json.at("Criaturas").at(idCriatura).at("Drops").at("Armas").at("Probabilidad").get<float>();
    float probaArmadura = json.at("Criaturas").at(idCriatura).at("Drops").at("Armaduras").at("Probabilidad").get<float>() + probaArma;
    float probaEscudo = json.at("Criaturas").at(idCriatura).at("Drops").at("Escudos").at("Probabilidad").get<float>() + probaArmadura;
    float probaCasco = json.at("Criaturas").at(idCriatura).at("Drops").at("Cascos").at("Probabilidad").get<float>() + probaEscudo;
    float probaPocion = json.at("Criaturas").at(idCriatura).at("Drops").at("Pociones").at("Probabilidad").get<float>() + probaCasco;
    float probaOro = json.at("Criaturas").at(idCriatura).at("Drops").at("Oro").at("Probabilidad").get<float>() + probaPocion;
    //Tiro el dado
    float numero = (float) rand()/RAND_MAX;
    //Calculo el drop
    if (numero < probaArma && numero >= 0) return ARMA;
    if (numero < probaArmadura && numero >= probaArma) return ARMADURA;
    if (numero < probaEscudo && numero >= probaArmadura) return ESCUDO;
    if (numero < probaCasco && numero >= probaEscudo) return CASCO;
    if (numero < probaPocion && numero >= probaCasco) return POCION;
    if (numero < probaOro && numero >= probaPocion) return ORO;
    return NADA;
}


const std::string Configuraciones::obtenerMapaSpawnCriaturaAleatoria(const std::string &id) const{
    std::vector<std::string> posibles = json.at("Mapas").at(id).at("SpawnCriaturas").get<std::vector<std::string>>();
    std::vector<std::string>::iterator elegido = posibles.begin();
    unsigned int desplazamiento = numeroRandom(0, std::distance(elegido, posibles.end()) - 1);
    std::advance(elegido, desplazamiento);
    return (*elegido);
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