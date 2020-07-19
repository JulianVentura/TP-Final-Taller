#include "Banquero.h"
#include "Cliente.h"
#include "Estado.h"
#include "Personaje.h"
#include "FabricaDeItems.h"
#include "Configuraciones.h"
#include "../../common/Serializacion.h"
#include "Excepcion.h"

Banquero::Banquero(float x, float y) : Entidad("Banquero#"), limiteTransaccion(0), fraccionTransaccion(0){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    std::string id_base = "Banquero";
    uint32_t ancho = config->obtenerCiudadanoAncho(id_base);
    uint32_t alto = config->obtenerCiudadanoAlto(id_base);
    posicion = std::move(Posicion(x, y, ancho, alto));
    limiteTransaccion = config->obtenerBanqueroLimiteTransaccion();
    fraccionTransaccion = config->obtenerBanqueroFraccionTransaccion();

    FabricaDeItems *fabrica = FabricaDeItems::obtenerInstancia();
    itemNulo = fabrica -> crearItemNulo();
}

void Banquero::interactuar(Estado *estado, Cliente *cliente){
    estado->pedirListado(this, cliente);
}

void Banquero::comprar(unsigned int pos, Estado *estado, Cliente *cliente){
    estado->pedirCompra(pos, this, cliente);
}

void Banquero::vender(unsigned int pos, Estado *estado, Cliente *cliente){
    estado->pedirVenta(pos, this, cliente);
}

void Banquero::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarMensaje(mensaje, false);
        return;
    }
    std::vector<Item*>& almacen = personaje->obtenerAlmacen();
    if (pos >= TAM_TIENDA || almacen[pos] == itemNulo){
        //No hay nada que entregarle
        return;
    }
    Item *temp = almacen[pos];
    personaje->almacenar(almacen[pos]);
    almacen[pos] = itemNulo;
    uint32_t &oroEnAlmacen = personaje->obtenerOroAlmacen();
    cliente -> enviarInventario();
    cliente->enviarContenedor(std::move(serializarAlmacen(almacen, oroEnAlmacen)));
    
    std::string mensaje = "Se recibio " + temp->obtenerId();
    cliente->enviarMensaje(mensaje, false);
}

void Banquero::vender(Item* item, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarMensaje(mensaje, false);
        personaje->almacenar(item);
        return;
    }
    //Comprarle el item que pide y notificarle a cliente
    std::vector<Item*>& almacen = personaje->obtenerAlmacen();
    bool almacenado = false;
    for (std::size_t i=0; i<TAM_TIENDA; i++){
        if (almacen[i] == itemNulo){
            almacen[i] = item;
            almacenado = true;
            break;
        }
    }
    if (!almacenado){
        std::string mensaje = "No hay espacio para almacenar mas items en el banquero";
        personaje->almacenar(item);
        cliente->enviarMensaje(mensaje, false);
        return;
    }
    uint32_t &oroEnAlmacen = personaje->obtenerOroAlmacen();
    cliente -> enviarInventario();
    cliente->enviarContenedor(std::move(serializarAlmacen(almacen, oroEnAlmacen)));
    
    std::string mensaje = "Se almaceno " + item->obtenerId();
    cliente->enviarMensaje(mensaje, false);
}
void Banquero::listar(Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarMensaje(mensaje, false);
        return;
    }
    uint32_t &oroEnAlmacen = personaje->obtenerOroAlmacen();
    std::vector<Item*>& almacen = personaje->obtenerAlmacen();
    cliente->enviarContenedor(std::move(serializarAlmacen(almacen, oroEnAlmacen)));
    
}

void Banquero::transaccion(bool esDeposito, Estado *estado, Cliente *cliente){
    estado->pedirTransaccion(esDeposito, cliente, this);
}

void Banquero::transaccion(bool esDeposito, Personaje *personaje, Cliente *cliente){
    uint32_t &oroEnAlmacen = personaje->obtenerOroAlmacen();
    uint32_t oroEncima = personaje->obtenerOro();
    std::vector<Item*>& almacen = personaje->obtenerAlmacen();
    uint32_t monto = 0;
    std::stringstream mensaje;
    if (esDeposito){
        if (oroEncima == 0) return;
        monto = oroEncima * fraccionTransaccion;
    }else{
        if (oroEnAlmacen == 0) return;
        monto = oroEnAlmacen * fraccionTransaccion;
    }
    if (monto < limiteTransaccion) monto = limiteTransaccion;
    if (esDeposito){
        if (oroEncima < monto) monto = oroEncima;
        personaje->restarOro(monto);
        oroEnAlmacen += monto;
        mensaje << "Has depositado " << monto << " oro.";
    }else{
        if (oroEnAlmacen < monto) monto = oroEnAlmacen;
        personaje->recibirOro(monto);
        oroEnAlmacen -= monto;
        mensaje << "Has retirado " << monto << " oro.";
    }
    cliente->enviarInventario();
    cliente->enviarContenedor(std::move(serializarAlmacen(almacen, oroEnAlmacen)));
}

//Ataque

std::string Banquero::atacar(Personaje *objetivo){ return ""; }

std::string Banquero::atacar(Criatura *objetivo){ return ""; }

void Banquero::serAtacadoPor(Personaje *atacante){}

void Banquero::serAtacadoPor(Criatura *atacante){}

std::string Banquero::recibirDanio(int danio, Entidad *atacante){ return ""; }

void Banquero::recibirCuracion(unsigned int curacion, Entidad *lanzador){}

//Estado

void Banquero::actualizarEstado(double tiempo){
    //Nada
}

std::string Banquero::dropearItems(Entidad *atacante){ return "";}

SerializacionContenedor Banquero::serializarAlmacen(const std::vector<Item*> &almacen, uint32_t oro){
    SerializacionContenedor serContenedor;
    for (std::size_t i=0; i<TAM_TIENDA; i++){
        serContenedor.items[i] = std::move(almacen[i]->serializar());
    }
    serContenedor.oroContenedor = oro;
    return serContenedor;
}


Banquero::~Banquero(){

}