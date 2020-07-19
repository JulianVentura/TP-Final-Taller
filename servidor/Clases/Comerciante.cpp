#include "Comerciante.h"
#include "Cliente.h"
#include "Estado.h"
#include "Personaje.h"
#include "Arma.h"
#include "Armadura.h"
#include "Casco.h"
#include "Escudo.h"
#include "Pocion.h"
#include "FabricaDeItems.h"

Comerciante::Comerciante(float x, float y) : Entidad("Comerciante#"){
    Configuraciones *config = Configuraciones::obtenerInstancia();
    FabricaDeItems *fabrica = FabricaDeItems::obtenerInstancia();
    std::string id_base = "Comerciante";
    uint32_t ancho = config->obtenerCiudadanoAncho(id_base);
    uint32_t alto = config->obtenerCiudadanoAlto(id_base);
    posicion = std::move(Posicion(x, y, ancho, alto));
    unsigned int cont = 0;
    itemNulo = fabrica -> crearItemNulo();
    items.resize(TAM_TIENDA, itemNulo);
    std::vector<std::string> idItems = config->obtenerCiudadanoStockArmas(id_base);
    for (auto &idArma : idItems){
        if (cont == TAM_TIENDA) break;
        items[cont] = fabrica->crearArma(idArma);
        cont++;
    }
    idItems = config->obtenerCiudadanoStockArmaduras(id_base);
    for (auto &idArmadura : idItems){
        if (cont == TAM_TIENDA) break;
        items[cont] = fabrica->crearArmadura(idArmadura);
        cont++;
    }
    idItems = config->obtenerCiudadanoStockEscudos(id_base);
    for (auto &idEscudo : idItems){
        if (cont == TAM_TIENDA) break;
        items[cont] = fabrica->crearEscudo(idEscudo);
        cont++;
    }
    idItems = config->obtenerCiudadanoStockCascos(id_base);
    for (auto &idCasco : idItems){
        if (cont == TAM_TIENDA) break;
        items[cont] = fabrica->crearCasco(idCasco);
        cont++;
    }
    idItems = config->obtenerCiudadanoStockPociones(id_base);
    for (auto &idPocion : idItems){
        if (cont == TAM_TIENDA) break;
        items[cont] = fabrica->crearPocion(idPocion);
        cont++;
    }   
}

void Comerciante::interactuar(Estado *estado, Cliente *cliente){
    estado->pedirListado(this, cliente);
}
void Comerciante::comprar(unsigned int pos, Estado *estado, Cliente *cliente){
    estado->pedirCompra(pos, this, cliente);
}
void Comerciante::vender(unsigned int pos, Estado *estado, Cliente *cliente){
    estado->pedirVenta(pos, this, cliente);
}

void Comerciante::comprar(unsigned int pos, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarMensaje(mensaje, false);
        return;
    }
    if (pos >= TAM_TIENDA || items[pos] == itemNulo){
        //No hay nada que comprar
        return;
    }
    if (personaje->tieneOroSuficiente(items[pos]->obtenerPrecio())){
        personaje->almacenar(items[pos]);
        personaje->restarOro(items[pos]->obtenerPrecio());
        cliente -> enviarInventario();
        cliente -> enviarTienda(std::move(this->serializarTienda()));
        std::string mensaje = "Se compro " + items[pos]->obtenerId();
        cliente->enviarMensaje(mensaje, false);
    }else{
        std::string mensaje = "No tiene oro suficiente";
        cliente->enviarMensaje(mensaje, false);
    }
}

void Comerciante::vender(Item* item, Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        std::string mensaje = "La distancia es muy grande";
        cliente->enviarMensaje(mensaje, false);
        personaje->almacenar(item);
        return;
    }
    
    personaje->recibirOro(item->obtenerPrecio());
    cliente -> enviarInventario();
    cliente -> enviarTienda(std::move(this->serializarTienda()));
    std::string mensaje = "Se vendio " + item->obtenerId();
    cliente->enviarMensaje(mensaje, false);
}

void Comerciante::listar(Personaje *personaje, Cliente *cliente){
    float distancia = this->posicion.calcularDistancia(personaje->obtenerPosicion());
    if (distancia > distanciaMaximaDeInteraccion){
        //Estamos muy lejos
        return;
    }
    cliente -> enviarTienda(this->serializarTienda());
}

void Comerciante::transaccion(bool esDeposito, Estado *estado, Cliente *cliente){}

//Ataque

std::string Comerciante::atacar(Personaje *objetivo){ return ""; }

std::string Comerciante::atacar(Criatura *objetivo){ return ""; }

void Comerciante::serAtacadoPor(Personaje *atacante){}

void Comerciante::serAtacadoPor(Criatura *atacante){}

std::string Comerciante::recibirDanio(int danio, Entidad *atacante){ return "";}

void Comerciante::recibirCuracion(unsigned int curacion, Entidad *lanzador){}

//Estado

void Comerciante::actualizarEstado(double tiempo){
    //Nada
}

std::string Comerciante::dropearItems(Entidad *atacante){ return "";}

SerializacionContenedor Comerciante::serializarTienda(){
    SerializacionContenedor serContenedor;
    serContenedor.oroContenedor = 0;
    std::vector<SerializacionItem> resultado(TAM_TIENDA);
    for (std::size_t i=0; i<TAM_TIENDA; i++){
        serContenedor.items[i] = std::move(items[i]->serializar());
    }
    return serContenedor;
}


Comerciante::~Comerciante(){}