#include "BaseDeDatos.h"


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

std::string BaseDeDatos::leerCadena(){
	char buffer[TAM_CADENAS];
	archivo.read(buffer, TAM_CADENAS);
	std::string cadena(buffer);
	return cadena;
}

void BaseDeDatos::escribirCadena(std::string cadena){
	if(cadena.size() < TAM_CADENAS)
  		cadena.append(TAM_CADENAS - cadena.size(),0);
  	archivo.write(cadena.c_str(), TAM_CADENAS);
}

void BaseDeDatos::nuevoCliente(std::pair<std::string,
 std::string> &credenciales, std::string &mapaActual, Personaje *personaje){
 	std::lock_guard<std::mutex> lock (m);
    dirs[credenciales.first] = ultima_dir;
  	archivo.seekp(ultima_dir*TAM_BLOQUES);
  	escribirCadena(credenciales.second);
    ultima_dir++;
}

void BaseDeDatos::guardarDirs(){
	std::fstream archivo_json;
	archivo_json.open("clientes.dir", std::fstream::out | std::fstream::trunc);
  	archivo_json << std::setw(4) << dirs << std::endl;
}

void BaseDeDatos::guardarCliente(std::string &id){
    std::lock_guard<std::mutex> lock (m);
    guardarDirs();
}

//Necesito el id del mapa y el Personaje
std::pair<std::string, std::unique_ptr<Personaje>> 
BaseDeDatos::cargarCliente(std::pair<std::string, std::string> &credenciales){
	std::lock_guard<std::mutex> lock (m);
    std::unique_ptr<Personaje> personaje(new Personaje(0, 0,
     credenciales.first, "Paladin", "Humano"));
    return std::pair<std::string,
     std::unique_ptr<Personaje>>("mapa", std::move(personaje));
}

//Chequea que el id exista y la contraseña sea valida
bool BaseDeDatos::verificarCliente(std::pair<std::string, std::string> &credenciales){
	std::lock_guard<std::mutex> lock (m);
    auto it = dirs.find(credenciales.first);
  	if(it != dirs.end()){
  		int corrimiento;
  		dirs.at(credenciales.first).get_to(corrimiento);
  		archivo.seekg(corrimiento*TAM_BLOQUES);
  		std::string clave_correcta = std::move(leerCadena());
  		return clave_correcta == credenciales.second;
  	}
    return false;
}