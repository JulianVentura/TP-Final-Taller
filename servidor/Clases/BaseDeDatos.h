#ifndef __BASE_DE_DATOS_H__
#define __BASE_DE_DATOS_H__
#include <memory>
class Personaje;
class BaseDeDatos{
    //Por el momento esta clase es un mock
    private:
    int numero;

    public:
    BaseDeDatos();
    void nuevoCliente(std::pair<std::string, std::string> &credenciales, 
                      std::string &mapaActual,
                      Personaje *personaje);
    void actualizarDatos(std::string &id);
    //Necesito el id del mapa y el Personaje
    std::pair<std::string, std::unique_ptr<Personaje>> recuperarInformacion(std::pair<std::string, std::string> &credenciales);
    //Chequea que el id exista y la contraseña sea valida
    bool idExistente(std::pair<std::string, std::string> &credenciales);
};


#endif
