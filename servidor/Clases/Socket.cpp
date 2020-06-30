#include "Socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <utility> //Para std::move
#include "ExcepcionSocket.h"
#define NO_INICIALIZADO -1
#define EXITO 0
#define ERROR -1


//////////Metodos privados///////////////

/*
Se obtendra una lista de direcciones posibles para la conexion que sera
almacenada en resultado.
La lista filtrara las posibles direcciones al host y puerto indicados,
devolviendo unicamente las que cumplan con las opciones AF_INET y SOCK_STREAM
Lanza una instancia de Excepcion en caso de error.
Devuelve 0 en caso de exito.
*/
int obtenerResultadoPorDominioYPuerto(const char* host, 
                                      const char* puerto,
                                      const int flag,
                                      struct addrinfo **resultado){
    struct addrinfo hints;
    std::memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = flag;
    int estado = getaddrinfo(host, puerto, &hints, resultado);
    if (estado != EXITO){
        throw ExcepcionSocket
        ("Error al intentar crear lista de conexiones en Socket. ");
    }
    return EXITO;
}


/////////Metodos publicos////////////////


Socket::Socket() : skt(NO_INICIALIZADO){
    /*
    No le encuentro sentido a crear un skt que luego
    debere destruir al momento de llamar a connect o bind.
    Prefiero setear el valor del skt a un estado reconocible
    dentro de los metodos que pueden ser invocados.
    Hacer esto me permite lanzar una excepcion mucho mas
    descriptiva si el usuario no hace el correcto connect/bind
    antes de llamar a los demas metodos de la clase.
    */
}

Socket::Socket(Socket &&otro) : skt(otro.skt){
    skt = otro.skt;
    otro.skt = NO_INICIALIZADO;
}

Socket::Socket(int skt) : skt(skt){}

Socket::~Socket(){
    if (skt != NO_INICIALIZADO){
        shutdown(skt, SHUT_RDWR);
        close(skt);
        skt = NO_INICIALIZADO;
    }
}

int Socket::conectar(const char* host, const char* puerto){
    struct addrinfo *resultado = NULL; 
    struct addrinfo *actual = NULL;
    int estado = ERROR;
    obtenerResultadoPorDominioYPuerto(host, puerto, 0, &resultado);
    for (actual=resultado; 
        (actual != NULL && estado == ERROR); 
         actual = resultado->ai_next){
        skt = socket(actual->ai_family,
                     actual->ai_socktype,
                     actual->ai_protocol);
        if (skt == ERROR) continue;
        estado = connect(skt, actual->ai_addr, actual->ai_addrlen);
        if (estado == ERROR) close(skt);
    }
    freeaddrinfo(resultado);
    if (estado == ERROR){
        throw ExcepcionSocket(
              "Error al conectar con el host %s en puerto %s. ", 
               host, puerto);
    }
    return EXITO;
}

void Socket::apagar(const int flag_apagado){
    if (skt == NO_INICIALIZADO) return;
    if (flag_apagado == READ){
        shutdown(skt, SHUT_RD);
    }else if (flag_apagado == WRITE){
        shutdown(skt, SHUT_WR);
    }else{
        shutdown(skt, SHUT_RDWR);
    }
}

int Socket::bindYSetearOpciones(const char* host, const char* puerto){
    struct addrinfo *resultado = nullptr;
    struct addrinfo *actual = nullptr;
    int opciones = 1;
    obtenerResultadoPorDominioYPuerto(host, puerto, AI_PASSIVE, &resultado);
    int estado = ERROR;
    for (actual=resultado; 
        (actual != nullptr && estado == ERROR); 
         actual = resultado->ai_next){
         skt = socket(actual->ai_family,
                      actual->ai_socktype,
                      actual->ai_protocol);
        if (skt == ERROR) continue;
        estado = setsockopt(skt,
                            SOL_SOCKET,
                            SO_REUSEADDR,
                            &opciones,
                            sizeof(opciones));
        if (estado == ERROR){
            close(skt);
            continue;
        } 
        estado = bind(skt, actual->ai_addr, actual->ai_addrlen);
        if (estado == ERROR) continue;
    }
    freeaddrinfo(resultado);
    if (estado == ERROR){
        throw ExcepcionSocket
        ("Error al bindear al host %s y puerto %s. ", host, puerto);
    }
    return EXITO;
}
int Socket::escuchar(const unsigned int numeroDeConexionesEnEspera){
    if (skt == NO_INICIALIZADO){
        throw ExcepcionSocket
        ("El Socket no se encuentra conectado/bindeado a ninguna "
        "direccion y puerto. ");
    }
    int estado = listen(skt, numeroDeConexionesEnEspera);
    if (estado == ERROR){
        throw ExcepcionSocket
        ("Error al configurar una cola de %d conexiones en espera en Socket. ",
        numeroDeConexionesEnEspera);
    }
    return EXITO;
}
Socket Socket::aceptar(){
    if (skt == NO_INICIALIZADO){
        throw ExcepcionSocket
        ("El Socket no se encuentra conectado/bindeado a ninguna "
        "direccion y puerto. ");
    }
    int cliente = accept(skt, NULL, NULL);
    if (cliente == ERROR){
        throw ExcepcionSocket(
              "Error al aceptar una conexion entrante en Socket. ");
    }
    return std::move(Socket(cliente));
}
int Socket::recibirMensaje(char* buffer,
                           const unsigned int tamanioMensaje){
    if (skt == NO_INICIALIZADO){
        throw ExcepcionSocket
        ("El Socket no se encuentra conectado/bindeado a ninguna "
        "direccion y puerto. ");
    }
    unsigned int bytesRecibidos = 0;
    int estado = 1;
    while (estado > 0 && bytesRecibidos < tamanioMensaje){
        estado = recv(skt, buffer,
                      tamanioMensaje - bytesRecibidos,
                      MSG_WAITALL);
        if (estado > 0) bytesRecibidos += estado;
    }
    if (estado <= 0){
        throw ExcepcionSocket
            ("Error al intentar recibir un mensaje desde Socket. ");
    }
    return EXITO;
}
int Socket::enviarMensaje(const char* mensaje,
                          const unsigned int tamanioMensaje){
    if (skt == NO_INICIALIZADO){
        throw ExcepcionSocket
        ("El Socket no se encuentra conectado/bindeado a ninguna "
        "direccion y puerto. ");
    }
    unsigned int bytesEnviados = 0;
    int estado = 0;
    while (estado >= 0 && bytesEnviados < tamanioMensaje){
        estado = send(skt,
                      mensaje,
                      tamanioMensaje - bytesEnviados,
                      MSG_NOSIGNAL);
        if (estado >= 0) bytesEnviados += estado;
    }
    if (estado < 0){
        throw ExcepcionSocket
            ("Error al intentar enviar un mensaje desde Socket. ");
    }
    return EXITO;
}

void Socket::cerrar(){
    if (skt != NO_INICIALIZADO) close(skt);
    skt = NO_INICIALIZADO;
}
