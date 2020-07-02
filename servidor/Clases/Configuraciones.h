#ifndef __CONFIGURACIONES_H__
#define __CONFIGURACIONES_H__
#include <nlohmann/json.hpp>
#include <vector>
#include <cstdint>
class Entidad;
class Personaje;
class Arma;
class Configuraciones{
    private:
    nlohmann::json json;

    public:
    static Configuraciones* obtenerInstancia();
    static void crearInstancia(const char *nombreArchivo);

    /* GETTERS DEL JUEGO */
    //Aceptador
    const uint32_t obtenerAceptadorNumConexionesEnEspera() const;
    //GameLoop
    const uint32_t obtenerGameLoopMSdescanso() const;
    const uint32_t obtenerGameLoopMSporActualizacion() const;
    //Mapas
    const std::string obtenerMapaRuta(std::string &id) const;
    const std::vector<std::string> obtenerMapaSpawnCriaturas(std::string &id) const;
    const uint32_t obtenerMapaLimiteCriaturas(std::string &id) const;
    //Personaje
    const uint32_t obtenerPersonajeNivelBase() const;
    const uint32_t obtenerPersonajeFuerzaBase() const;
    const uint32_t obtenerPersonajeInteligenciaBase() const;
    const uint32_t obtenerPersonajeAgilidadBase() const;
    const uint32_t obtenerPersonajeComposicionBase() const;
    const float    obtenerPersonajeVelDesplazamiento() const;
    const uint32_t obtenerPersonajeAncho() const;
    const uint32_t obtenerPersonajeAlto() const;
    //Ciudadanos
    const uint32_t obtenerCiudadanoAncho(std::string &id) const;
    const uint32_t obtenerCiudadanoAlto(std::string &id) const;
    //Criaturas
    const uint32_t obtenerCriaturaVidaMax(std::string &id) const;
    const uint32_t obtenerCriaturaNivel(std::string &id) const;
    const uint32_t obtenerCriaturaFuerza(std::string &id) const;
    const uint32_t obtenerCriaturaInteligencia(std::string &id) const;
    const uint32_t obtenerCriaturaAgilidad(std::string &id) const;
    const uint32_t obtenerCriaturaConstitucion(std::string &id) const;
    const float    obtenerCriaturaVelDesplazamiento(std::string &id) const;
    const uint32_t obtenerCriaturaAncho(std::string &id) const;
    const uint32_t obtenerCriaturaAlto(std::string &id) const;
    //Clases
    const float    obtenerFClaseVida(std::string &id) const;
    const float    obtenerFClaseRecuperacion(std::string &id) const;
    const float    obtenerFClaseMeditacion(std::string &id) const;
    const uint32_t obtenerClaseMejoraFuerzaEnSubida(std::string &id) const;
    const uint32_t obtenerClaseMejoraInteligenciaEnSubida(std::string &id) const;
    const uint32_t obtenerClaseMejoraAgilidadEnSubida(std::string &id) const;
    const uint32_t obtenerClaseMejoraConstitucionEnSubida(std::string &id) const;
    //Razas
    const float    obtenerFRazaVida(std::string &id) const;
    const float    obtenerFRazaRecuperacion(std::string &id) const;
    const float    obtenerFRazaMeditacion(std::string &id) const;
    const uint32_t obtenerRazaMejoraFuerzaEnSubida(std::string &id) const;
    const uint32_t obtenerRazaMejoraInteligenciaEnSubida(std::string &id) const;
    const uint32_t obtenerRazaMejoraAgilidadEnSubida(std::string &id) const;
    const uint32_t obtenerRazaMejoraConstitucionEnSubida(std::string &id) const;
    //Armas
    const int32_t  obtenerArmaDanioMax(std::string &id) const;
    const int32_t  obtenerArmaDanioMin(std::string &id) const;
    const uint32_t obtenerArmaRangoAtaque(std::string &id) const;
    const uint32_t obtenerArmaConsumoMana(std::string &id) const;
    //Armaduras
    const uint32_t obtenerArmaduraDefensaMax(std::string &id) const;
    const uint32_t obtenerArmaduraDefensaMin(std::string &id) const;
    //Escudos
    const uint32_t obtenerEscudoDefensaMax(std::string &id) const;
    const uint32_t obtenerEscudoDefensaMin(std::string &id) const;
    //Cascos
    const uint32_t obtenerCascoDefensaMax(std::string &id) const;
    const uint32_t obtenerCascoDefensaMin(std::string &id) const;
    //Oro
    const uint32_t obtenerOroCantidadMax() const;
    //Pociones
    const uint32_t obtenerCuracionVida(std::string &id) const;
    const uint32_t obtenerCuracionMana(std::string &id) const;
    /* FORMULAS DEL JUEGO */ 
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
    Configuraciones();
    void leerArchivo(const char* nombreArchivo);
    static Configuraciones instancia;
    static bool instanciaCreada;
};


#endif