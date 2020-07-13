#ifndef __CONFIGURACIONES_H__
#define __CONFIGURACIONES_H__
#include <nlohmann/json.hpp>
#include <vector>
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
class Arma;
class Configuraciones{
    private:
    nlohmann::json json;
    std::string obtenerItemRandom(std::string &idCriatura, std::string idItem);
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
    const std::string obtenerMapaRuta(std::string &id) const;
    const std::string obtenerMapaInicial() const;
    const std::pair<float, float> obtenerMapaPosicionSpawn(std::string &id) const;
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
    const uint16_t obtenerEstadoIDTCP(std::string &id) const;
    //Ciudadanos
    const uint32_t obtenerCiudadanoAncho(std::string &id) const;
    const uint32_t obtenerCiudadanoAlto(std::string &id) const;
    //Criaturas
    const uint32_t obtenerCriaturaVidaMax(std::string &id) const;
    const uint32_t obtenerCriaturaManaMax(std::string &id) const;
    const uint32_t obtenerCriaturaNivel(std::string &id) const;
    const uint32_t obtenerCriaturaFuerza(std::string &id) const;
    const uint32_t obtenerCriaturaInteligencia(std::string &id) const;
    const uint32_t obtenerCriaturaAgilidad(std::string &id) const;
    const uint32_t obtenerCriaturaConstitucion(std::string &id) const;
    const float    obtenerCriaturaVelDesplazamiento(std::string &id) const;
    const double   obtenerCriaturaTiempoDespawn(std::string &id) const;
    const uint32_t obtenerCriaturaAncho(std::string &id) const;
    const uint32_t obtenerCriaturaAlto(std::string &id) const;
    const std::string obtenerCriaturaIdArma(std::string &id) const;
    const float obtenerCriaturaRadioAgresividad(std::string &id) const;
    const float obtenerCriaturaRadioVisibilidad(std::string &id) const;
    //Clases
    const float    obtenerFClaseVida(std::string &id) const;
    const float    obtenerFClaseMana(std::string &id) const;
    const float    obtenerFClaseRecuperacion(std::string &id) const;
    const float    obtenerFClaseMeditacion(std::string &id) const;
    const uint32_t obtenerClaseMejoraFuerzaEnSubida(std::string &id) const;
    const uint32_t obtenerClaseMejoraInteligenciaEnSubida(std::string &id) const;
    const uint32_t obtenerClaseMejoraAgilidadEnSubida(std::string &id) const;
    const uint32_t obtenerClaseMejoraConstitucionEnSubida(std::string &id) const;
    const uint16_t obtenerClaseIDTCP(std::string &id) const;
    //Razas
    const float    obtenerFRazaVida(std::string &id) const;
    const float    obtenerFRazaMana(std::string &id) const;
    const float    obtenerFRazaRecuperacion(std::string &id) const;
    const float    obtenerFRazaMeditacion(std::string &id) const;
    const uint32_t obtenerRazaMejoraFuerzaEnSubida(std::string &id) const;
    const uint32_t obtenerRazaMejoraInteligenciaEnSubida(std::string &id) const;
    const uint32_t obtenerRazaMejoraAgilidadEnSubida(std::string &id) const;
    const uint32_t obtenerRazaMejoraConstitucionEnSubida(std::string &id) const;
    const uint16_t obtenerRazaIDTCP(std::string &id) const;
    //Armas
    const int32_t  obtenerArmaDanioMax(std::string &id) const;
    const int32_t  obtenerArmaDanioMin(std::string &id) const;
    const float    obtenerArmaRangoAtaque(std::string &id) const;
    const double   obtenerArmaTiempoAtaque(std::string &id) const;
    const uint32_t obtenerArmaConsumoMana(std::string &id) const;
    const uint32_t obtenerArmaPrecio(std::string &id) const;
    const uint16_t obtenerArmaIDTCP(std::string &id) const;
    const std::string obtenerArmaIDProyectil(std::string &id) const;
    //Proyectiles
    const float    obtenerProyectilVelDesplazamiento(std::string &id) const;
    const double   obtenerProyectilTiempoDespawn(std::string &id) const;
    //Armaduras
    const uint32_t obtenerArmaduraDefensaMax(std::string &id) const;
    const uint32_t obtenerArmaduraDefensaMin(std::string &id) const;
    const uint32_t obtenerArmaduraPrecio(std::string &id) const;
    const uint16_t obtenerArmaduraIDTCP(std::string &id) const;
    //Escudos
    const uint32_t obtenerEscudoDefensaMax(std::string &id) const;
    const uint32_t obtenerEscudoDefensaMin(std::string &id) const;
    const uint32_t obtenerEscudoPrecio(std::string &id) const;
    const uint16_t obtenerEscudoIDTCP(std::string &id) const;
    //Cascos
    const uint32_t obtenerCascoDefensaMax(std::string &id) const;
    const uint32_t obtenerCascoDefensaMin(std::string &id) const;
    const uint32_t obtenerCascoPrecio(std::string &id) const;
    const uint16_t obtenerCascoIDTCP(std::string &id) const;
    //Pociones
    const uint32_t obtenerPocionCuracionVida(std::string &id) const;
    const uint32_t obtenerPocionCuracionMana(std::string &id) const;
    const uint32_t obtenerPocionPrecio(std::string &id) const;
    const uint16_t obtenerPocionIDTCP(std::string &id) const;
    //Varios
    const uint32_t obtenerBolsaDeDropAncho() const;
    const uint32_t obtenerBolsaDeDropAlto() const;
    const uint32_t obtenerTamanioTienda() const;
    const float    obtenerDistanciaMaximaDeInteraccion() const;
    /* FORMULAS DEL JUEGO */ 
    unsigned int calcularVidaMax(Personaje *personaje);
    float        calcularRecuperacionVida(Personaje *personaje, double tiempo);
    unsigned int calcularManaMax(Personaje *personaje);
    float        calcularRecupManaMeditacion(Personaje *personaje, double tiempo);
    float        calcularRecupManaTiempo(Personaje *personaje, double tiempo);
    unsigned int calcularDropOro(Entidad *entidad);
    unsigned int calcularMaxOroSeguro(Personaje *personaje);
    unsigned int calcularLimiteParaSubir(Personaje *personaje);
    unsigned int calcularExpPorGolpe(Entidad *objetivo, Entidad *atacante, unsigned int danio);
    unsigned int calcularExpPorMatar(Entidad *objetivo, Entidad *atacante);
    unsigned int calcularDanioAtaque(Entidad *objetivo, Entidad *atacante, Arma *arma);
    unsigned int calcularFuerza(Personaje *personaje);
    unsigned int calcularInteligencia(Personaje *personaje);
    unsigned int calcularAgilidad(Personaje *personaje);
    unsigned int calcularConstitucion(Personaje *personaje);
    std::string calcularDropArma(std::string &idCriatura);
    std::string calcularDropArmadura(std::string &idCriatura);
    std::string calcularDropEscudo(std::string &idCriatura);
    std::string calcularDropCasco(std::string &idCriatura);
    std::string calcularDropPocion(std::string &idCriatura);
    unsigned int calcularDropOro(std::string &idCriatura);
    unsigned int calcularDefensa(Personaje *personaje);
    
    TipoDrop calcularDrop(std::string &idCriatura);
    TipoItem calcularDropItem(std::string &idCriatura);
    bool seEsquivaElGolpe(Entidad *entidad);
    const std::string obtenerMapaSpawnCriaturaAleatoria(const std::string &id) const;
    bool sePuedeAtacar(Personaje *objetivo, Personaje *atacante);

    protected:
    Configuraciones();
    void leerArchivo(const char* nombreArchivo);
    static Configuraciones instancia;
    static bool instanciaCreada;
};


#endif