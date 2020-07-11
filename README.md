## Compilación

Cliente: Ubicarse en cliente/ y ejecutar "make"
```
cd cliente
make
bin/cliente.out
```

Servidor: Ubicarse en servidor/build y ejecutar "cmake ..". El servidor se ejecuta como "./servidor <configuraciones.json>". Dicho archivo se encuenta en servidor/.
```
cd servidor
mkdir build
cd build
cmake ..
make
./servidor ../configuraciones.json
```

## Requisitos

- Probado en Ubuntu 64 bits y Linux Mint 32 bits.

- Biblioteca SDL2, SLD_Image, SDL_TTF 
```
sudo apt install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

- Biblioteca Nlohman dev_3.7.0-2: http://mirrors.kernel.org/ubuntu/pool/universe/n/nlohmann-json3/nlohmann-json3-dev_3.7.0-2_all.deb

(Se puede instalar también con ```sudo apt install nlohmann-json3-dev```, pero en algunas versiones de ubuntu, se instala la versión 2, que no funciona para el tp).

- Biblioteca de audio incorporada en el propio código, no requiere instalación adicional.

## Videos

07/07/20 https://drive.google.com/file/d/1oXUqZB-LbbHu-14e_8CEyprskqbhAZ4W/view?usp=sharing

10/07/20 https://drive.google.com/file/d/1EVyVw1n9N7nDgGxBKSg9l3YXiGpXUSjN/view?usp=sharing

## Notas

Nota: Crear siempre una nueva cuenta al logearse en el servidor,
	  aún no está implementada la base de datos.
	  Para una introduccion general a la estructura del código, ver:

10/07/20 https://drive.google.com/file/d/1-KCT0oHJ5-JcQTcdRnJfPt037v1Z_rTs/view?usp=sharing

	* Ignorar la clase posicionable, ha quedado en desuso en refactorizaciones recientes.
