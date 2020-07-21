#include "EntornoMusical.h"

#define VOLUMEN SDL_MIX_MAXVOLUME/2
#define NUEVO_AUDIO(x,y) sonidos[x] = createAudio(y, 0, VOLUMEN)

std::unordered_map<std::string, Audio*> EntornoMusical::sonidos;
EntornoMusical EntornoMusical::instancia;

EntornoMusical::EntornoMusical(){
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	initAudio();
	NUEVO_AUDIO("musicaMenu", "assets/audio/musicaMenu.wav");
	NUEVO_AUDIO("musicaJuego", "assets/audio/musicaJuego.wav");
	NUEVO_AUDIO("Cuerpo", "assets/audio/cuerpo.wav");
	NUEVO_AUDIO("Curar", "assets/audio/Curar.wav");
	NUEVO_AUDIO("Explosion", "assets/audio/explosion.wav");
	NUEVO_AUDIO("Flechazo", "assets/audio/flechazo.wav");
	NUEVO_AUDIO("FlechaM", "assets/audio/explosion.wav");
	NUEVO_AUDIO("Misil", "assets/audio/explosion.wav");
	NUEVO_AUDIO("Zombie", "assets/audio/zombie.wav");
	NUEVO_AUDIO("Esqueleto", "assets/audio/zombie3.wav");
	NUEVO_AUDIO("Goblin", "assets/audio/zombie3.wav");
	NUEVO_AUDIO("Ambiente1", "assets/audio/birds2.wav");
	NUEVO_AUDIO("100-101", "assets/audio/fantasma.wav");
	NUEVO_AUDIO("101-100", "assets/audio/fantasma-a-vivo.wav");
	NUEVO_AUDIO("CambioMapa", "assets/audio/teletransportar.wav");
}

EntornoMusical* EntornoMusical::obtenerInstancia(){
	return &instancia;
}

void EntornoMusical::reproducirSonido(std::string nombre){
	if (!sonidos.count(nombre)) return;
	try{
		playSoundFromMemory(sonidos.at(nombre),
			VOLUMEN*2);
	}catch(std::exception& e){}
}

void EntornoMusical::reproducirMusica(std::string nombre){
	if (!sonidos.count(nombre)) return;
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