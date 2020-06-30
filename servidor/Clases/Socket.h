#ifndef __SOCKET__
#define __SOCKET__
#include <string>
enum SHUTDOWN{READ, WRITE, READ_AND_WRITE};

class Socket{
    private:
    int skt;
    /*
    Construye un Socket a partir de un file descriptor ya inicializado.
    Solo se utilizara para devolver clientes inicializados dentro de
    aceptar()
    */
    explicit Socket(int skt);
    
    public:
    Socket();
    Socket(Socket &otro) = delete;
    Socket(Socket &&otro);
    Socket operator=(Socket &otro) = delete;
    Socket operator=(Socket &&otro) = delete;
    ~Socket();
    /*
    El socket sera conectado al host y puerto indicados.
    En caso de error se lanzara una instancia de ExcepcionSocket.
    En caso de exito devuelve 0.
    */
    int conectar(const char* host, const char* puerto);
    /*
    Cierra el canal de comunicacion indicado en flag_apagado.
    Se pueden cerrar los canales: READ, WRITE, READ_AND_WRITE.
    Esta funcion no falla.
    */
    void apagar(const int flag_apagado);
    /*
    El Socket sera enlazado a un host y puerto y se configuraran las 
    opciones SOL_SOCKET y SO_REUSEADDR.
    Lanza una instancia de ExcepcionSocket en caso de error.
    Devuelve 0 en caso de exito.
    */
    int bindYSetearOpciones(const char* host, const char* puerto);
    /*
    El Socket sera configurado en modo escucha y numeroDeConexionesEnEspera
    sera tomado como numero maximo de conexiones en espera para ser atendidas.
    Lanza una instancia de ExcepcionSocket en caso de error.
    Devuelve 0 en caso de exito.
    */
    int escuchar(const unsigned int numeroDeConexionesEnEspera);
    /*
    El Socket aceptara una conexion entrante, inicializara una nueva instancia
    de Socket con ella y la devolvera por movimiento.
    Lanza una instancia de ExcepcionSocket en caso de error.
    */
    Socket aceptar();
    /*
    El Socket recibira un mensaje de tamanio tamanioMensaje y lo almacenara en
    buffer.
    buffer debera ser solicitado por parte del usuario, este metodo
    no se encargara de solicitar memoria al S.O.
    Se espera que buffer tenga al menos un tamanio de tamanioMensaje, de
    otra forma van a ocurrir errores.
    Lanza una instancia de ExcepcionSocket en caso de error.
    Devuelve 0 en exito.
    */
    int recibirMensaje(char* buffer,
                       const unsigned int tamanioMensaje);
    /*
    El Socket enviara un mensaje de tamanio tamanioMensaje almacenado en
    el buffer mensaje.
    Se espera que mensaje tenga al menos un tamanio de tamanioMensaje, de
    otra forma van a ocurrir errores.
    Lanza una instancia de ExcepcionSocket en caso de error.
    Devuelve 0 en exito.
    */
    int enviarMensaje(const char* mensaje,
                      const unsigned int tamanioMensaje);
    /*
    Fuerza el cierre del socket.
    No falla.
    No realiza un apagado de los canales.
    No es necesario llamar a este metodo al finalizar la utilizacion del Socket
    ya que el cierre se realizara automaticamente en el destructor del mismo.
    Un Socket cerrado quedara invalidado.
    */
    void cerrar();
};

#endif
