#ifndef __THREAD__
#define __THREAD__
#include <thread>

class Thread{
    private:
    std::thread thread;
    bool estaCorriendo;

    public:
    Thread();
    Thread(Thread &otro) = delete;
    Thread(Thread &&otro) = delete;
    Thread& operator=(Thread &&otro) = delete;
    /*
    Libera los recursos del thread utilizado tras la finalizacion
    de la ejecucion del mismo.
    */
    void recuperar();
    /*
    Comienza la ejecucion del thread llamando al metodo procesar()
    de la instancia actual.
    */
    void comenzar();
    /*
    Contiene el codigo a ejecutar por el thread.
    */
    void virtual procesar() = 0;
    virtual ~Thread();
};

#endif
