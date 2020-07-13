#include "BaseDeDatos.h"
#include "Cliente.h"

// Métodos privados

std::string BaseDeDatos::leerCadena(){
	char buffer[TAM_CADENAS];
	archivo.read(buffer, TAM_CADENAS);
	std::string cadena(buffer);
	return cadena;
}

bool BaseDeDatos::existeCliente(std::string id){
    auto it = dirs.find(id);
	return (it != dirs.end());
}

void BaseDeDatos::escribirCadena(std::string cadena){
	if(cadena.size() < TAM_CADENAS)
  		cadena.append(TAM_CADENAS - cadena.size(),0);
  	archivo.write(cadena.c_str(), TAM_CADENAS);
}

void BaseDeDatos::guardarDirs(){
	std::fstream archivo_json;
	archivo_json.open("clientes.dir", std::fstream::out | std::fstream::trunc);
	//El 4 es un número mágico de la biblioteca Nlohman.
  	archivo_json << std::setw(4) << dirs << std::endl;
}

// Métodos públicos

BaseDeDatos::BaseDeDatos(){
	ultima_dir = 0;
	std::fstream archivo_json;
    archivo_json.open("clientes.dir", std::fstream::in | std::fstream::out);
	if(archivo_json.is_open()){
		archivo_json >> dirs;
		archivo_json.close();
		dirs.at(" ").get_to(ultima_dir);
	}else{
		dirs[" "] = ultima_dir;
	}

	archivo.open("clientes.dat", std::fstream::in | std::fstream::out |
	 std::fstream::binary);
	if(!archivo.is_open()){
		archivo.open("clientes.dat", std::fstream::in | std::fstream::out |
		 std::fstream::binary | std::fstream::app);
		archivo.close();
		archivo.open("clientes.dat", std::fstream::in | std::fstream::out |
		 std::fstream::binary);
	}
}


void BaseDeDatos::nuevoCliente(std::pair<std::string, std::string> &credenciales, 
    std::string& idRaza, std::string& idClase, std::string& idMapa,
    Personaje *personaje){
 	std::lock_guard<std::mutex> lock (m);
 	if(existeCliente(credenciales.first)) return;
    dirs[credenciales.first] = ultima_dir;
  	archivo.seekp(ultima_dir*TAM_BLOQUES, std::ios_base::beg);
  	escribirCadena(credenciales.second);
  	escribirCadena(idRaza);
  	escribirCadena(idClase);
  	escribirCadena(idMapa);
  	serializacionPersonaje datos = personaje -> serializar();
  	archivo.write((char*)&datos, sizeof(serializacionPersonaje));
    ultima_dir++;
    guardarDirs();
}



void BaseDeDatos::moverACliente(const std::string& nombre){
	int desplazamiento = 0;
	dirs.at(nombre).get_to(desplazamiento);
	archivo.seekg(desplazamiento*TAM_BLOQUES, std::ios_base::beg);
	archivo.seekp(desplazamiento*TAM_BLOQUES, std::ios_base::beg);
}

void BaseDeDatos::guardarCliente(Cliente* cliente){
    std::lock_guard<std::mutex> lock (m);
    serializacionPersonaje datos = cliente -> obtenerPersonaje() -> serializar();
    moverACliente(cliente -> obtenerId());
    //Omitir campos inmutables: Id, Raza y Clase.
	archivo.seekp(3*TAM_CADENAS, std::ios_base::cur);
	escribirCadena(cliente -> obtenerIdSala());
    archivo.write((char*)&datos, sizeof(serializacionPersonaje));
}

std::pair<std::string, std::unique_ptr<Personaje>> 
BaseDeDatos::cargarCliente(std::pair<std::string, std::string> &credenciales){
	std::lock_guard<std::mutex> lock (m);
	moverACliente(credenciales.first);
	archivo.seekg(TAM_CADENAS, std::ios_base::cur);
	serializacionPersonaje datos;
	std::string idRaza  = leerCadena();
	std::string idClase = leerCadena();
	std::string idMapa = leerCadena();
	archivo.read((char*)&datos, sizeof(serializacionPersonaje));
    std::unique_ptr<Personaje> personaje(new Personaje(credenciales.first,
    	idRaza, idClase, datos));
    return std::pair<std::string, std::unique_ptr<Personaje>>
    		(idMapa, std::move(personaje));
}

//Chequea que el id exista y la contraseña sea valida
bool BaseDeDatos::verificarCliente(std::pair<std::string, std::string> &credenciales){
	std::lock_guard<std::mutex> lock (m);
    auto it = dirs.find(credenciales.first);
  	if(it != dirs.end()){
  		moverACliente(credenciales.first);
  		std::string clave_correcta = std::move(leerCadena());
  		return clave_correcta == credenciales.second;
  	}
    return false;
}

BaseDeDatos::~BaseDeDatos(){
	guardarDirs();
}
