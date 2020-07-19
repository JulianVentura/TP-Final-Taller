#include "EntornoMusical.h"

#define VOLUMEN SDL_MIX_MAXVOLUME
#define NUEVO_AUDIO(x,y) sonidos[x] = createAudio(y, 0, VOLUMEN)

std::unordered_map<std::string, Audio*> EntornoMusical::sonidos;
EntornoMusical EntornoMusical::instancia;

EntornoMusical::EntornoMusical(){
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	initAudio();
	NUEVO_AUDIO("musicaMenu", "assets/audio/musicaMenu.wav");
	NUEVO_AUDIO("musicaJuego", "assets/audio/musicaJuego.wav");
	NUEVO_AUDIO("musicaJuego2", "assets/audio/musicaJuego2.wav");
}

EntornoMusical* EntornoMusical::obtenerInstancia(){
	return &instancia;
}

void EntornoMusical::reproducirSonido(std::string nombre){
	try{
		playSoundFromMemory(sonidos.at(nombre),
			VOLUMEN/2);
	}catch(std::exception& e){}
}

void EntornoMusical::reproducirMusica(std::string nombre){
	try{
		playMusicFromMemory(sonidos.at(nombre),
			VOLUMEN);
	}catch(std::exception& e){}
}

EntornoMusical::~EntornoMusical(){
	pauseAudio();
	endAudio();
	for(auto& sonido : sonidos){
		freeAudio(sonido.second);
	}
}