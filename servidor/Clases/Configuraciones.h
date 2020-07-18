#ifndef __CONFIGURACIONES_H__
#define __CONFIGURACIONES_H__
#include <nlohmann/json.hpp>
#include <unordered_set>
#include <vector>
#include <random>
#include <cstdint>

typedef enum ITEM {ARMA,
                   ARMADURA,
                   CASCO,
                   ESCUDO,
                   POCION} TipoItem;
typedef enum DROP {ITEM,
                   ORO,
                   NADA} TipoDrop;
class Entidad;
class Personaje;
class Criatura;
class Arma;
class ArmaCuracion;
class Configuraciones{
    private:
    nlohmann::json json;
    std::mt19937 motorAleatorio;

    const std::string obtenerItemRandom(const std::string &idCriatura, const std::string idItem) const;
    
    public:
    static Configuraciones* obtenerInstancia();
    static void crearInstancia(const char *nombreArchivo);

    /* GETTERS DEL JUEGO */
    //Salas
    const std::vector<std::string> obtenerSalas() const;
    //Aceptador
    const uint32_t obtenerAceptadorNumConexionesEnEspera() const;
    const std::string obtenerAceptadorPuerto() const;
    const std::string obtenerAceptadorHost() const;
    //GameLoop
    const uint32_t obtenerGameLoopMSdescanso() const;
    const uint32_t obtenerGameLoopMSporActualizacion() const;
    //Mapas
    const std::string obtenerMapaRuta(const std::string &id) const;
    const std::string obtenerMapaInicial() const;
    const std::pair<float, float> obtenerMapaPosicionSpawn(const std::string &id) const;
    const uint32_t obtenerMapaLimiteCriaturas(std::string &id) const;
    const double   obtenerMapaTiempoRespawn(std::string &id) const;
    //Personaje
    const uint32_t obtenerPersonajeNivelBase() const;
    const uint32_t obtenerPersonajeFuerzaBase() const;
    const uint32_t obtenerPersonajeInteligenciaBase() const;
    const uint32_t obtenerPersonajeAgilidadBase() const;
    const uint32_t obtenerPersonajeConstitucionBase() const;
    const float    obtenerPersonajeVelDesplazamiento() const;
    const uint32_t obtenerPersonajeAncho() const;
    const uint32_t obtenerPersonajeAlto() const;
    //Estados
    const uint16_t obtenerEstadoIDTCP(const std::string &id) const;
    //Portales
    const std::string obtenerPortalMapaATeletransportar(const std::string &idNPC, const std::string &idMapa);
    const uint32_t obtenerPortalAncho() const;
    const uint32_t obtenerPortalAlto() const;
    //Ciudadanos
    const uint32_t obtenerCiudadanoAncho(const std::string &id) const;
    const uint32_t obtenerCiudadanoAlto(const std::string &id) const;
    const std::vector<std::string> obtenerCiudadanoStockArmas(const std::string &id) const;
    const std::vector<std::string> obtenerCiudadanoStockArmaduras(const std::string &id) const;
    const std::vector<std::string> obtenerCiudadanoStockEscudos(const std::string &id) const;
    const std::vector<std::string> obtenerCiudadanoStockCascos(const std::string &id) const;
    const std::vector<std::string> obtenerCiudadanoStockPociones(const std::string &id) const;
    //Criaturas
    const uint32_t obtenerCriaturaVidaMax(const std::string &id) const;
    const uint32_t obtenerCriaturaManaMax(const std::string &id) const;
    const uint32_t obtenerCriaturaNivel(const std::string &id) const;
    const uint32_t obtenerCriaturaFuerza(const std::string &id) const;
    const uint32_t obtenerCriaturaInteligencia(const std::string &id) const;
    const uint32_t obtenerCriaturaAgilidad(const std::string &id) const;
    const uint32_t obtenerCriaturaConstitucion(const std::string &id) const;
    const float    obtenerCriaturaVelDesplazamiento(const std::string &id) const;
    const double   obtenerCriaturaTiempoDespawn(const std::string &id) const;
    const uint32_t obtenerCriaturaAncho(const std::string &id) const;
    const uint32_t obtenerCriaturaAlto(const std::string &id) const;
    const std::string obtenerCriaturaIdArma(const std::string &id) const;
    const float obtenerCriaturaRadioAgresividad(const std::string &id) const;
    const float obtenerCriaturaRadioVisibilidad(const std::string &id) const;
    //Clases
    const float    obtenerFClaseVida(const std::string &id) const;
    const float    obtenerFClaseMana(const std::string &id) const;
    const float    obtenerFClaseRecuperacion(const std::string &id) const;
    const float    obtenerFClaseMeditacion(const std::string &id) const;
    const uint32_t obtenerClaseMejoraFuerzaEnSubida(const std::string &id) const;
    const uint32_t obtenerClaseMejoraInteligenciaEnSubida(const std::string &id) const;
    const uint32_t obtenerClaseMejoraAgilidadEnSubida(const std::string &id) const;
    const uint32_t obtenerClaseMejoraConstitucionEnSubida(const std::string &id) const;
    const uint16_t obtenerClaseIDTCP(const std::string &id) const;
    //Razas
    const float    obtenerFRazaVida(const std::string &id) const;
    const float    obtenerFRazaMana(const std::string &id) const;
    const float    obtenerFRazaRecuperacion(const std::string &id) const;
    const float    obtenerFRazaMeditacion(const std::string &id) const;
    const uint32_t obtenerRazaMejoraFuerzaEnSubida(const std::string &id) const;
    const uint32_t obtenerRazaMejoraInteligenciaEnSubida(const std::string &id) const;
    const uint32_t obtenerRazaMejoraAgilidadEnSubida(const std::string &id) const;
    const uint32_t obtenerRazaMejoraConstitucionEnSubida(const std::string &id) const;
    const uint16_t obtenerRazaIDTCP(const std::string &id) const;
    //FabricaDeItems
    const uint32_t obtenerFabricaDeItemsLimiteArmas() const;
    const uint32_t obtenerFabricaDeItemsLimiteArmaduras() const;
    const uint32_t obtenerFabricaDeItemsLimiteCascos() const;
    const uint32_t obtenerFabricaDeItemsLimiteEscudos() const;
    const uint32_t obtenerFabricaDeItemsLimitePociones() const;
    const std::unordered_map<int, std::string> obtenerFabricaDeItemsConversor() const;
    const std::unordered_set<std::string> obtenerFabricaDeItemsArmasDeCuracion() const;
    //Items
    //Item Nulo
    const uint16_t obtenerItemNuloPrecio() const;
    const uint16_t obtenerItemNuloIDTCP() const;
    //Armas
    const uint32_t obtenerArmaDanioMax(const std::string &id) const;
    const uint32_t obtenerArmaDanioMin(const std::string &id) const;
    const uint32_t obtenerArmaCuracionMax(const std::string &id) const;
    const uint32_t obtenerArmaCuracionMin(const std::string &id) const;
    const float    obtenerArmaRangoAtaque(const std::string &id) const;
    const double   obtenerArmaTiempoAtaque(const std::string &id) const;
    const uint32_t obtenerArmaConsumoMana(const std::string &id) const;
    const uint32_t obtenerArmaPrecio(const std::string &id) const;
    const uint16_t obtenerArmaIDTCP(const std::string &id) const;
    const std::string obtenerArmaIDProyectil(const std::string &id) const;
    //Proyectiles
    const float    obtenerProyectilVelDesplazamiento(const std::string &id) const;
    const double   obtenerProyectilTiempoDespawn(const std::string &id) const;
    //Armaduras
    const uint32_t obtenerArmaduraDefensaMax(const std::string &id) const;
    const uint32_t obtenerArmaduraDefensaMin(const std::string &id) const;
    const uint32_t obtenerArmaduraPrecio(const std::string &id) const;
    const uint16_t obtenerArmaduraIDTCP(const std::string &id) const;
    //Escudos
    const uint32_t obtenerEscudoDefensaMax(const std::string &id) const;
    const uint32_t obtenerEscudoDefensaMin(const std::string &id) const;
    const uint32_t obtenerEscudoPrecio(const std::string &id) const;
    const uint16_t obtenerEscudoIDTCP(const std::string &id) const;
    //Cascos
    const uint32_t obtenerCascoDefensaMax(const std::string &id) const;
    const uint32_t obtenerCascoDefensaMin(const std::string &id) const;
    const uint32_t obtenerCascoPrecio(const std::string &id) const;
    const uint16_t obtenerCascoIDTCP(const std::string &id) const;
    //Pociones
    const uint32_t obtenerPocionCuracionVida(const std::string &id) const;
    const uint32_t obtenerPocionCuracionMana(const std::string &id) const;
    const uint32_t obtenerPocionPrecio(const std::string &id) const;
    const uint16_t obtenerPocionIDTCP(const std::string &id) const;
    //Varios
    const uint32_t obtenerBolsaDeDropAncho() const;
    const uint32_t obtenerBolsaDeDropAlto() const;
    const float    obtenerDistanciaMaximaDeInteraccion() const;
    const double   obtenerClienteTiempoActualizacionInventario() const;
    /* FORMULAS DEL JUEGO */ 
    unsigned int   calcularVidaMax(const Personaje *personaje);
    float          calcularRecuperacionVida(const Personaje *personaje, double tiempo);
    unsigned int   calcularManaMax(const Personaje *personaje);
    float          calcularRecupManaMeditacion(const Personaje *personaje, double tiempo);
    float          calcularRecupManaTiempo(const Personaje *personaje, double tiempo);
    const uint32_t calcularMaxOroSeguro(const Personaje *personaje);
    const uint32_t calcularLimiteParaSubir(const Personaje *personaje);
    const uint32_t calcularLimiteExpInferior(const Personaje *personaje);
    const uint32_t calcularExpPorGolpe(const Entidad *objetivo, const Entidad *atacante, unsigned int danio);
    const uint32_t calcularExpPorMatar(const Entidad *objetivo, const Entidad *atacante);
    const uint32_t calcularDanioAtaque(const Entidad *objetivo, const Entidad *atacante, const Arma *arma);
    const uint32_t calcularCuracion(const Entidad *objetivo, const Entidad *atacante, const ArmaCuracion *armaCuracion) const;
    const uint32_t calcularFuerza(const Personaje *personaje);
    const uint32_t calcularInteligencia(const Personaje *personaje);
    const uint32_t calcularAgilidad(const Personaje *personaje);
    const uint32_t calcularConstitucion(const Personaje *personaje);
    std::string    calcularDropArma(const std::string &idCriatura);
    std::string    calcularDropArmadura(const std::string &idCriatura);
    std::string    calcularDropEscudo(const std::string &idCriatura);
    std::string    calcularDropCasco(const std::string &idCriatura);
    std::string    calcularDropPocion(const std::string &idCriatura);
    const uint32_t calcularDropOro(const Entidad *entidad);
    const uint32_t calcularDefensa(Personaje *personaje);
    
    TipoDrop calcularDrop(const std::string &idCriatura) const;
    TipoItem calcularDropItem(const std::string &idCriatura);
    bool seEsquivaElGolpe(const Entidad *entidad);
    bool esGolpeCritico(const Entidad *atacante, const Entidad *oponente);
    const std::string obtenerMapaSpawnCriaturaAleatoria(const std::string &id) const;
    bool sePuedeAtacar(const Personaje *objetivo, const Personaje *atacante);

    protected:
    Configuraciones();
    void leerArchivo(const char* nombreArchivo);
    static Configuraciones instancia;
    static bool instanciaCreada;
};


#endif