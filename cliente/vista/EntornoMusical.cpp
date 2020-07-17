#include "EntornoMusical.h"

#define NUEVO_AUDIO(x,y) sonidos[x] = createAudio(y, 0, SDL_MIX_MAXVOLUME)

std::unordered_map<std::string, Audio*> EntornoMusical::sonidos;
EntornoMusical EntornoMusical::instancia;

EntornoMusical::EntornoMusical(){
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	initAudio();
	NUEVO_AUDIO("musicaMenu", "assets/audio/musicaMenu.wav");
}

EntornoMusical* EntornoMusical::obtenerInstancia(){
	return &instancia;
}

void EntornoMusical::reproducirSonido(std::string nombre){
	try{
		playSoundFromMemory(sonidos.at(nombre),
			SDL_MIX_MAXVOLUME/2);
	}catch(std::exception& e){}
}

void EntornoMusical::reproducirMusica(std::string nombre){
	try{
		playMusicFromMemory(sonidos.at(nombre),
			SDL_MIX_MAXVOLUME);
	}catch(std::exception& e){}
}

EntornoMusical::~EntornoMusical(){
	pauseAudio();
	endAudio();
	for(auto& sonido : sonidos){
		freeAudio(sonido.second);
	}
}