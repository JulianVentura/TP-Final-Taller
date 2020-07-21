#include "Configuraciones.h"
#include "Mapa.h"
#include "Entidad.h"
#include "Personaje.h"
#include "Criatura.h"
#include "Raza.h"
#include "Clase.h"
#include "Arma.h"
#include "ArmaCuracion.h"
#include "Armadura.h"
#include "Escudo.h"
#include "Casco.h"
#include "../../common/Excepcion.h"
#include "Mapa.h"
#include "Posicion.h"
#include <random>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <cmath>

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

Configuraciones::Configuraciones() : motorAleatorio(std::time(0)){
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

static bool floatComp(float a, float b, float epsilon = 0.01){
    return fabs(a - b) < epsilon;
}

/*
Devuelve un numero pseudo aleatorio perteneciente a [a, b]

*/
static unsigned int numeroRandom(unsigned int a, unsigned int b){
    if (b == a) return a;
    return rand() % (b - a + 1) + a;
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
const uint32_t Configuraciones::obtenerBuclePrincipalMSdescanso() const{
    return json.at("GameLoop").at("MS_DESCANSO").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerBuclePrincipalMSporActualizacion() const{
    return json.at("GameLoop").at("MS_POR_ACTUALIZACION").get<uint32_t>();
}
//Mapas
const std::string Configuraciones::obtenerMapaRuta(const std::string &id) const{
    return json.at("Mapas").at(id).at("Ruta").get<std::string>();
}
const uint32_t Configuraciones::obtenerMapaLimiteCriaturas(std::string &id) const{
    return json.at("Mapas").at(id).at("LimiteCriaturas").get<uint32_t>();
}
const std::string Configuraciones::obtenerMapaInicial() const{
    return json.at("MapaInicial").get<std::string>();
}
Posicion Configuraciones::obtenerMapaPosicionSpawn(const std::string &id) const{
    float x = json.at("Mapas").at(id).at("PosicionSpawnInicial")[0].get<float>();
    float y = json.at("Mapas").at(id).at("PosicionSpawnInicial")[1].get<float>();
    return Posicion(x, y, 0, 0);
}

const double  Configuraciones::obtenerMapaTiempoRespawn(std::string &id) const{
    return json.at("Mapas").at(id).at("TiempoRespawn").get<double>();
}
const bool Configuraciones::elMapaEsSeguro(std::string &id) const{
    return json.at("Mapas").at(id).at("EsSeguro").get<bool>();
}
const std::string Configuraciones::obtenerCiudadMasCercana(const std::string &id) const{
    return json.at("Mapas").at(id).at("CiudadMasCercana").get<std::string>();
}
Posicion Configuraciones::obtenerPuntoSpawnResurreccion(const std::string &id) const{
    float x = json.at("Mapas").at(id).at("PosicionSpawnResurreccion")[0].get<float>();
    float y = json.at("Mapas").at(id).at("PosicionSpawnResurreccion")[1].get<float>();
    return Posicion(x, y, 0, 0);
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
//Estados
const uint16_t Configuraciones::obtenerEstadoIDTCP(const std::string &id) const{
    return json.at("Estados").at(id).at("idTCP").get<uint16_t>();
}
//Ciudadanos
const uint32_t Configuraciones::obtenerCiudadanoAncho(const std::string &id) const{
    return json.at("Ciudadanos").at(id).at("Ancho").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCiudadanoAlto(const std::string &id) const{
    return json.at("Ciudadanos").at(id).at("Alto").get<uint32_t>();
}
const std::vector<std::string> Configuraciones::obtenerCiudadanoStockArmas(const std::string &id) const{
    return json.at("Ciudadanos").at(id).at("StockVenta").at("Armas").get<std::vector<std::string>>();
}
const std::vector<std::string> Configuraciones::obtenerCiudadanoStockArmaduras(const std::string &id) const{
    return json.at("Ciudadanos").at(id).at("StockVenta").at("Armaduras").get<std::vector<std::string>>();
}
const std::vector<std::string> Configuraciones::obtenerCiudadanoStockEscudos(const std::string &id) const{
    return json.at("Ciudadanos").at(id).at("StockVenta").at("Escudos").get<std::vector<std::string>>();
}
const std::vector<std::string> Configuraciones::obtenerCiudadanoStockCascos(const std::string &id) const{
    return json.at("Ciudadanos").at(id).at("StockVenta").at("Cascos").get<std::vector<std::string>>();
}
const std::vector<std::string> Configuraciones::obtenerCiudadanoStockPociones(const std::string &id) const{
    return json.at("Ciudadanos").at(id).at("StockVenta").at("Pociones").get<std::vector<std::string>>();
}
const uint32_t Configuraciones::obtenerBanqueroLimiteTransaccion() const{
    return json.at("Ciudadanos").at("Banquero").at("LimiteTransaccion").get<uint32_t>();
}
const double Configuraciones::obtenerBanqueroFraccionTransaccion() const{
    return json.at("Ciudadanos").at("Banquero").at("FraccionTransaccion").get<double>();
}
//Portales
const std::string Configuraciones::obtenerPortalMapaATeletransportar(const std::string &idNPC, 
                                                                     const std::string &idMapa){
    return json.at("Mapas").at(idMapa).at("SpawnPortales").at(idNPC).get<std::string>();
}   
const uint32_t Configuraciones::obtenerPortalAncho() const{
    return json.at("Portales").at("Ancho").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerPortalAlto() const{
    return json.at("Portales").at("Alto").get<uint32_t>();
}
//Criaturas
const uint32_t Configuraciones::obtenerCriaturaVidaMax(const std::string &id) const{
    return json.at("Criaturas").at(id).at("Vida").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaManaMax(const std::string &id) const{
    return json.at("Criaturas").at(id).at("Mana").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaNivel(const std::string &id) const{
    return json.at("Criaturas").at(id).at("Nivel").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaFuerza(const std::string &id) const{
    return json.at("Criaturas").at(id).at("Fuerza").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaInteligencia(const std::string &id) const{
    return json.at("Criaturas").at(id).at("Inteligencia").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaAgilidad(const std::string &id) const{
    return json.at("Criaturas").at(id).at("Agilidad").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaConstitucion(const std::string &id) const{
    return json.at("Criaturas").at(id).at("Constitucion").get<uint32_t>();
}
const double   Configuraciones::obtenerCriaturaTiempoDespawn(const std::string &id) const{
    return json.at("Criaturas").at(id).at("TiempoDespawn").get<double>();
}
const float Configuraciones::obtenerCriaturaVelDesplazamiento(const std::string &id) const{
    return json.at("Criaturas").at(id).at("VelDesplazamiento").get<float>();
}
const uint32_t Configuraciones::obtenerCriaturaAncho(const std::string &id) const{
    return json.at("Criaturas").at(id).at("Ancho").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerCriaturaAlto(const std::string &id) const{
    return json.at("Criaturas").at(id).at("Alto").get<uint32_t>();
}
const std::string Configuraciones::obtenerCriaturaIdArma(const std::string &id) const{
    return json.at("Criaturas").at(id).at("IdArma").get<std::string>();
}
const float Configuraciones::obtenerCriaturaRadioAgresividad(const std::string &id) const{
    return json.at("Criaturas").at(id).at("RadioAgresividad").get<float>();
}
const float Configuraciones::obtenerCriaturaRadioVisibilidad(const std::string &id) const{
    return json.at("Criaturas").at(id).at("RadioVisibilidad").get<float>();
}
//Clases
const float Configuraciones::obtenerFClaseVida(const std::string &id) const{
    return json.at("Clases").at(id).at("FClaseVida").get<float>();
}
const float Configuraciones::obtenerFClaseMana(const std::string &id) const{
    return json.at("Clases").at(id).at("FClaseMana").get<float>();
}
const float Configuraciones::obtenerFClaseRecuperacion(const std::string &id) const{
    return json.at("Clases").at(id).at("FClaseRecuperacion").get<float>();
}
const float Configuraciones::obtenerFClaseMeditacion(const std::string &id) const{
    return json.at("Clases").at(id).at("FClaseMeditacion").get<float>();
}
const uint32_t Configuraciones::obtenerClaseMejoraFuerzaEnSubida(const std::string &id) const{
    return json.at("Clases").at(id).at("MejoraFuerzaEnSubida").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerClaseMejoraInteligenciaEnSubida(const std::string &id) const{
    return json.at("Clases").at(id).at("MejoraInteligenciaEnSubida").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerClaseMejoraAgilidadEnSubida(const std::string &id) const{
    return json.at("Clases").at(id).at("MejoraAgilidadEnSubida").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerClaseMejoraConstitucionEnSubida(const std::string &id) const{
    return json.at("Clases").at(id).at("MejoraConstitucionEnSubida").get<uint32_t>();
}
const uint16_t Configuraciones::obtenerClaseIDTCP(const std::string &id) const{
    return json.at("Clases").at(id).at("idTCP").get<uint16_t>();
}
//Razas
const float Configuraciones::obtenerFRazaVida(const std::string &id) const{
    return json.at("Razas").at(id).at("FRazaVida").get<float>();
}
const float Configuraciones::obtenerFRazaMana(const std::string &id) const{
    return json.at("Razas").at(id).at("FRazaMana").get<float>();
}
const float Configuraciones::obtenerFRazaRecuperacion(const std::string &id) const{
    return json.at("Razas").at(id).at("FRazaRecuperacion").get<float>();
}
const float Configuraciones::obtenerFRazaMeditacion(const std::string &id) const{
    return json.at("Razas").at(id).at("FRazaMeditacion").get<float>();
}
const uint32_t Configuraciones::obtenerRazaMejoraFuerzaEnSubida(const std::string &id) const{
    return json.at("Razas").at(id).at("MejoraFuerzaEnSubida").get<float>();
}
const uint32_t Configuraciones::obtenerRazaMejoraInteligenciaEnSubida(const std::string &id) const{
    return json.at("Razas").at(id).at("MejoraInteligenciaEnSubida").get<float>();
}
const uint32_t Configuraciones::obtenerRazaMejoraAgilidadEnSubida(const std::string &id) const{
    return json.at("Razas").at(id).at("MejoraAgilidadEnSubida").get<float>();
}
const uint32_t Configuraciones::obtenerRazaMejoraConstitucionEnSubida(const std::string &id) const{
    return json.at("Razas").at(id).at("MejoraConstitucionEnSubida").get<float>();
}
const uint16_t Configuraciones::obtenerRazaIDTCP(const std::string &id) const{
    return json.at("Razas").at(id).at("idTCP").get<uint16_t>();
}
//FabricaDeItems
const uint32_t Configuraciones::obtenerFabricaDeItemsLimiteArmas() const{
    return json.at("FabricaDeItems").at("LimiteDeArmas").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerFabricaDeItemsLimiteArmaduras() const{
    return json.at("FabricaDeItems").at("LimiteDeArmaduras").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerFabricaDeItemsLimiteCascos() const{
    return json.at("FabricaDeItems").at("LimiteDeCascos").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerFabricaDeItemsLimiteEscudos() const{
    return json.at("FabricaDeItems").at("LimiteDeEscudos").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerFabricaDeItemsLimitePociones() const{
    return json.at("FabricaDeItems").at("LimiteDePociones").get<uint32_t>();
}
const std::unordered_map<int, std::string> Configuraciones::obtenerFabricaDeItemsConversor() const{
    std::unordered_map<int, std::string> resultado;
    for (auto& item: json["Items"].items()){
        for (auto& it: item.value().items()) {
            for (auto& a: it.value().items()) {
                if (a.key() == "idTCP"){
                    resultado[a.value().get<int>()] = it.key();
                }
            }
        }
    }
    
    return resultado;
}
const std::unordered_set<std::string> Configuraciones::obtenerFabricaDeItemsArmasDeCuracion() const{
    return json.at("FabricaDeItems").at("ArmasDeCuracion").get<std::unordered_set<std::string>>();
}
//Items
//Item Nulo
const uint16_t Configuraciones::obtenerItemNuloPrecio() const{
    return json.at("Items").at("ItemNulo").at("Precio").get<uint16_t>();
}
const uint16_t Configuraciones::obtenerItemNuloIDTCP() const{
    return json.at("Items").at("ItemNulo").at("idTCP").get<uint16_t>();
}
//Armas
const uint32_t  Configuraciones::obtenerArmaDanioMax(const std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("DanioMax").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerArmaDanioMin(const std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("DanioMin").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerArmaCuracionMax(const std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("CuracionMax").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerArmaCuracionMin(const std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("CuracionMin").get<uint32_t>();
}
const float Configuraciones::obtenerArmaRangoAtaque(const std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("Rango").get<float>();
}
const double   Configuraciones::obtenerArmaTiempoAtaque(const std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("TiempoAtaque").get<double>();
}
const uint32_t Configuraciones::obtenerArmaConsumoMana(const std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("ConsumoMana").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerArmaPrecio(const std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("Precio").get<uint32_t>();
}
const uint16_t Configuraciones::obtenerArmaIDTCP(const std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("idTCP").get<uint16_t>();
}
const std::string Configuraciones::obtenerArmaIDProyectil(const std::string &id) const{
    return json.at("Items").at("Armas").at(id).at("Proyectil").get<std::string>();
}
//Proyectiles
const float Configuraciones::obtenerProyectilVelDesplazamiento(const std::string &id) const{
    return json.at("Proyectiles").at(id).at("VelDesplazamiento").get<float>();
}
const double Configuraciones::obtenerProyectilTiempoDespawn(const std::string &id) const{
    return json.at("Proyectiles").at(id).at("TiempoDespawn").get<double>();
}
//Armaduras
const uint32_t  Configuraciones::obtenerArmaduraDefensaMax(const std::string &id) const{
    return json.at("Items").at("Armaduras").at(id).at("DefensaMax").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerArmaduraDefensaMin(const std::string &id) const{
    return json.at("Items").at("Armaduras").at(id).at("DefensaMin").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerArmaduraPrecio(const std::string &id) const{
    return json.at("Items").at("Armaduras").at(id).at("Precio").get<uint32_t>();
}
const uint16_t Configuraciones::obtenerArmaduraIDTCP(const std::string &id) const{
    return json.at("Items").at("Armaduras").at(id).at("idTCP").get<uint16_t>();
}
//Escudos
const uint32_t  Configuraciones::obtenerEscudoDefensaMax(const std::string &id) const{
    return json.at("Items").at("Escudos").at(id).at("DefensaMax").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerEscudoDefensaMin(const std::string &id) const{
    return json.at("Items").at("Escudos").at(id).at("DefensaMin").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerEscudoPrecio(const std::string &id) const{
    return json.at("Items").at("Escudos").at(id).at("Precio").get<uint32_t>();
}
const uint16_t Configuraciones::obtenerEscudoIDTCP(const std::string &id) const{
    return json.at("Items").at("Escudos").at(id).at("idTCP").get<uint16_t>();
}
//Cascos
const uint32_t  Configuraciones::obtenerCascoDefensaMax(const std::string &id) const{
    return json.at("Items").at("Cascos").at(id).at("DefensaMax").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerCascoDefensaMin(const std::string &id) const{
    return json.at("Items").at("Cascos").at(id).at("DefensaMin").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerCascoPrecio(const std::string &id) const{
    return json.at("Items").at("Cascos").at(id).at("Precio").get<uint32_t>();
}
const uint16_t Configuraciones::obtenerCascoIDTCP(const std::string &id) const{
    return json.at("Items").at("Cascos").at(id).at("idTCP").get<uint16_t>();
}
//Pociones
const uint32_t  Configuraciones::obtenerPocionCuracionVida(const std::string &id) const{
    return json.at("Items").at("Pociones").at(id).at("CuracionVida").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerPocionCuracionMana(const std::string &id) const{
    return json.at("Items").at("Pociones").at(id).at("CuracionMana").get<uint32_t>();
}
const uint32_t  Configuraciones::obtenerPocionPrecio(const std::string &id) const{
    return json.at("Items").at("Pociones").at(id).at("Precio").get<uint32_t>();
}
const uint16_t Configuraciones::obtenerPocionIDTCP(const std::string &id) const{
    return json.at("Items").at("Pociones").at(id).at("idTCP").get<uint16_t>();
}
//Varios
const uint32_t Configuraciones::obtenerBolsaDeDropAncho() const{
    return json.at("Varios").at("BolsaDeDrop").at("Ancho").get<uint32_t>();
}
const uint32_t Configuraciones::obtenerBolsaDeDropAlto() const{
    return json.at("Varios").at("BolsaDeDrop").at("Alto").get<uint32_t>();
}
const float    Configuraciones::obtenerDistanciaMaximaDeInteraccion() const{
    return json.at("Varios").at("DistanciaInteraccion").get<float>();
}
const double   Configuraciones::obtenerClienteTiempoActualizacionInventario() const{
    return json.at("Varios").at("ClienteTiempoActualizacionInventario").get<double>();
}
const double   Configuraciones::obtenerPenalizacionRevivir(Mapa *mapaActual, Personaje *personaje) const{
    Posicion posPersonaje = personaje->obtenerPosicion();
    std::string idMapaActual = mapaActual->obtenerId();
    std::string ciudadDestino = obtenerCiudadMasCercana(idMapaActual);
    if (ciudadDestino == idMapaActual){
        return 10000;
    }
    std::string idPortal;
    for (auto& a: json["Mapas"][idMapaActual]["SpawnPortales"].items()){
        if (a.value() == ciudadDestino){
            idPortal = a.key();
            break;
        }
    }
    Entidad *portalDestino = mapaActual->obtener(idPortal);
    double distancia = posPersonaje.calcularDistancia(portalDestino->obtenerPosicion());
    return 10000 + distancia * 6;
}
const double   Configuraciones::obtenerSalaTiempoPersistencia() const{
    return json.at("Varios").at("SalaTiempoPersistencia").get<double>();
}


/* FORMULAS DEL JUEGO */


unsigned int Configuraciones::calcularVidaMax(const Personaje *personaje){
    uint32_t vidaBase = json.at("Personaje").at("VidaBase").get<uint32_t>();
    return vidaBase + personaje->constitucion * personaje->clase.FClaseVida * 
           personaje->raza.FRazaVida * personaje->nivel;
}

float Configuraciones::calcularRecuperacionVida(const Personaje *personaje, double tiempo){
    return personaje->raza.FRazaRecuperacion * tiempo * MILI_A_SEG;
}

unsigned int Configuraciones::calcularManaMax(const Personaje *personaje){
    //Esto sirve para que los guerreros tengan mana cero.
    if (personaje->clase.FClaseMana == 0) return 0;
    uint32_t manaBase = json.at("Personaje").at("ManaBase").get<uint32_t>();
    return manaBase + personaje->inteligencia * personaje->clase.FClaseMana * 
           personaje->raza.FRazaMana * personaje->nivel;
}

float Configuraciones::calcularRecupManaMeditacion(const Personaje *personaje, double tiempo){
    return personaje->clase.FClaseMeditacion * personaje->inteligencia * tiempo * MILI_A_SEG;
}

float Configuraciones::calcularRecupManaTiempo(const Personaje *personaje, double tiempo){
    return personaje->raza.FRazaRecuperacion * tiempo * MILI_A_SEG;
}

const uint32_t Configuraciones::calcularMaxOroSeguro(const Personaje *personaje){
    return 100 * std::pow(personaje->nivel, 1.1);
}

const uint32_t Configuraciones::calcularLimiteParaSubir(const Personaje *personaje){
    return 1000 * std::pow(personaje->nivel, 1.8);
}

const uint32_t Configuraciones::calcularLimiteExpInferior(const Personaje *personaje){
    return 1000 * std::pow(personaje->nivel - 1, 1.8);
}

const uint32_t Configuraciones::calcularExpPorGolpe(const Entidad *objetivo, const Entidad *atacante, unsigned int danio){
    //return Danio * max(NivelDelOtro - Nivel + 10, 0)
    return danio * std::max(objetivo->nivel - atacante->nivel + 10, (unsigned int)0);
}

const uint32_t Configuraciones::calcularExpPorMatar(const Entidad *objetivo, const Entidad *atacante){
    //return rand(0, 0.1) * VidaMaxDelOtro * max(NivelDelOtro - Nivel + 10, 0)
    float suerte = numeroRandom(0, 1000) / 10000;
    return suerte * objetivo->vidaMaxima * std::max(objetivo->nivel - atacante->nivel + 10, (unsigned int)0);
}

const uint32_t Configuraciones::calcularDanioAtaque(const Entidad *objetivo, const Entidad *atacante, const Arma *arma){
    return atacante->fuerza * numeroRandom(arma->danioMin, arma->danioMax);
}

const uint32_t Configuraciones::calcularCuracion(const Entidad *objetivo, 
                                                 const Entidad *lanzador, 
                                                 const ArmaCuracion *armaCuracion) const{
    return numeroRandom(armaCuracion->danioMin, armaCuracion->danioMax);
} 

bool Configuraciones::seEsquivaElGolpe(const Entidad *entidad){
    //return rand(0, 1) ^ Agilidad < 0.001
    double suerte = numeroRandom(0, 1000);
    suerte /= 1000;
    double temp = std::pow(suerte, entidad->agilidad);
    return temp < 1e-12;
}

bool Configuraciones::esGolpeCritico(const Entidad *atacante, const Entidad *oponente){
    double suerte = numeroRandom(0, 1000);
    suerte /= 1000;
    double temp = std::pow(suerte, atacante->agilidad);
    return temp < 1e-16;
}

const uint32_t Configuraciones::calcularDefensa(Personaje *personaje){
    uint32_t temp = 0;
    Armadura *armadura = nullptr;
    Casco *casco = nullptr;
    Escudo *escudo = nullptr;
    
    if (personaje->armadura != NO_EQUIPADO){
        armadura = (Armadura*)personaje->inventario.obtenerItem(personaje->armadura);
        temp = numeroRandom(armadura->defensaMin, armadura->defensaMax);
    }
    if (personaje->escudo != NO_EQUIPADO){
        escudo = (Escudo*)personaje->inventario.obtenerItem(personaje->escudo);
        temp += numeroRandom(escudo->defensaMin, escudo->defensaMax);
    }
    if (personaje->casco != NO_EQUIPADO){
        casco = (Casco*)personaje->inventario.obtenerItem(personaje->casco);
        temp += numeroRandom(casco->defensaMin, casco->defensaMax);
    }
    return temp;
}

const uint32_t Configuraciones::calcularFuerza(const Personaje *personaje){
    uint32_t fuerzaBase = this->obtenerPersonajeFuerzaBase();
    return fuerzaBase + personaje->nivel * personaje->raza.mejoraFuerzaEnSubida * personaje->clase.mejoraFuerzaEnSubida;
}

const uint32_t Configuraciones::calcularInteligencia(const Personaje *personaje){
    uint32_t inteligenciaBase = this->obtenerPersonajeInteligenciaBase();
    return inteligenciaBase + personaje->nivel * personaje->raza.mejoraInteligenciaEnSubida * personaje->clase.mejoraInteligenciaEnSubida;
}
const uint32_t Configuraciones::calcularAgilidad(const Personaje *personaje){
    uint32_t agilidadBase = this->obtenerPersonajeAgilidadBase();
    return agilidadBase + personaje->nivel * personaje->raza.mejoraAgilidadEnSubida * personaje->clase.mejoraAgilidadEnSubida;
}
const uint32_t Configuraciones::calcularConstitucion(const Personaje *personaje){
    uint32_t constitucionBase = this->obtenerPersonajeConstitucionBase();
    return constitucionBase + personaje->nivel * personaje->raza.mejoraConstitucionEnSubida * personaje->clase.mejoraConstitucionEnSubida;
}

bool Configuraciones::sePuedeAtacar(const Personaje *objetivo, const Personaje *atacante){
    if (objetivo == atacante) return true;
    uint32_t nivelDiferenciaMaximo = json.at("Varios").at("FairPlay").
                                        at("NivelDiferenciaMaximo").get<uint32_t>();
    uint32_t nivelNewbie = json.at("Varios").at("FairPlay").at("NivelNewbie").get<uint32_t>();
    if (objetivo->nivel <= nivelNewbie || atacante->nivel <= nivelNewbie) return false;
    if (abs(objetivo->nivel - atacante->nivel) > abs(nivelDiferenciaMaximo)) return false;
    return true;
}

/* DROPS */

std::string Configuraciones::calcularDropArma(const std::string &idCriatura){
    return obtenerItemRandom(idCriatura, "Armas");
}

std::string Configuraciones::calcularDropArmadura(const std::string &idCriatura){
    return obtenerItemRandom(idCriatura, "Armaduras");
}

std::string Configuraciones::calcularDropEscudo(const std::string &idCriatura){
    return obtenerItemRandom(idCriatura, "Escudos");
}

std::string Configuraciones::calcularDropCasco(const std::string &idCriatura){
    return obtenerItemRandom(idCriatura, "Cascos");
}

std::string Configuraciones::calcularDropPocion(const std::string &idCriatura){
    return obtenerItemRandom(idCriatura, "Pociones");
}

const uint32_t Configuraciones::calcularDropOro(const Entidad *entidad){
    //return rand(0, 0.2) * VidaMaxNPC
    float suerte = numeroRandom(0, 2000);
    suerte /= 10000;
    return suerte * entidad->vidaMaxima;
}

const std::string Configuraciones::obtenerItemRandom(const std::string &idCriatura, const std::string idItem) const{
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
        "pero las probabilidades no suman 1", idItem.c_str(), idCriatura.c_str());
    }
    float resultado = (float) rand() / (float) RAND_MAX;

    if (resultado < probas[0]) return posibles[0].first;   //Devuelvo el id que le corresponde a 0
    for (std::size_t i=1; i<probas.size(); i++){
        if (resultado <= probas[i] && resultado >= probas[i-1]) return posibles[i].first;
    }
    //Le pifio al 1
    return posibles[posibles.size()-1].first;
}

TipoDrop Configuraciones::calcularDrop(const std::string &idCriatura) const{
    float probaItem = json.at("Criaturas").at(idCriatura).at("Drops").at("Tipo").at("Item").get<float>();
    float probaOro = json.at("Criaturas").at(idCriatura).at("Drops").at("Tipo").at("Oro").get<float>() + probaItem;

    //Tiro el dado
    float numero = (float) rand()/ (float) RAND_MAX;
    //Calculo el drop
    if (numero < probaItem && numero >= 0) return ITEM;
    if (numero < probaOro && numero >= probaItem) return ORO;
    return NADA;
}

TipoItem Configuraciones::calcularDropItem(const std::string &idCriatura){
    float probaArma = json.at("Criaturas").at(idCriatura).at("Drops").at("Armas").at("Probabilidad").get<float>();
    float probaArmadura = json.at("Criaturas").at(idCriatura).at("Drops").at("Armaduras").at("Probabilidad").get<float>() + probaArma;
    float probaEscudo = json.at("Criaturas").at(idCriatura).at("Drops").at("Escudos").at("Probabilidad").get<float>() + probaArmadura;
    float probaCasco = json.at("Criaturas").at(idCriatura).at("Drops").at("Cascos").at("Probabilidad").get<float>() + probaEscudo;
    float probaPocion = json.at("Criaturas").at(idCriatura).at("Drops").at("Pociones").at("Probabilidad").get<float>() + probaCasco;
    //Tiro el dado
    float numero = (float) rand()/ (float) RAND_MAX;
    //Calculo el drop
    if (numero < probaArma && numero >= 0) return ARMA;
    if (numero < probaArmadura && numero >= probaArma) return ARMADURA;
    if (numero < probaEscudo && numero >= probaArmadura) return ESCUDO;
    if (numero < probaCasco && numero >= probaEscudo) return CASCO;
    if (numero <= probaPocion && numero >= probaCasco) return POCION;
    //Si se llego a este punto las probabilidades no suman 1
    throw Excepcion("Las probabilidades de drop de items de %s no suman 1", idCriatura.c_str());
}


const std::string Configuraciones::obtenerMapaSpawnCriaturaAleatoria(const std::string &id) const{
    std::vector<std::string> posibles = json.at("Mapas").at(id).at("SpawnCriaturas").get<std::vector<std::string>>();
    if (posibles.size() == 1) return posibles[0];
    unsigned int desp = numeroRandom(0, posibles.size() - 1);
    return posibles[desp];
}
