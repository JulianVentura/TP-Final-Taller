#include <math.h>
#include "mapa.h"

Mapa::Mapa(SDL_Renderer* renderer){
	ancho = 10;
	largo = 10;
	alto = 5;
	const char* rutas[] = {"","CasillaTierra.png","CasillaMadera.png"};
	int alturas[CANT_TEXT] = {0,64,192};
	for(int i = 1;i <  CANT_TEXT;i++){
		altura_text[i] = alturas[i];
		SDL_Surface* sup_actual = IMG_Load(rutas[i]);
		texturas[i] = SDL_CreateTextureFromSurface(renderer, sup_actual);
		SDL_FreeSurface(sup_actual);
	}

	for(int x = 0;x < ancho;x++){
		for(int y = 0;y < largo;y++){
			for(int z = 0;z < alto;z++){
				mapa[x][y][z] = 0;
			}
		}
	}

		for(int x = 0;x < ancho;x++){
			for(int y = 0;y < largo;y++){
				mapa[x][y][alto - 1] = 1;
				mapa[x][y][alto - 2] = 1;
		}

		/*
		mapa[0][0][alto - 3] = 2;
		
		mapa[1][2][alto - 3] = 2;
		mapa[3][0][alto - 3] = 2;
		mapa[0][3][alto - 3] = 2;
		mapa[4][0][alto - 3] = 2;
		*/
	}
}

void Mapa::dibujar(SDL_Renderer* renderer){
	int x = 0;int y = 0;int z = alto - 1;
	int x2,y2,z2;
	SDL_Texture* text_actual;
	SDL_Rect marco;
	marco.h = LADO_CELDA;
	marco.w = LADO_CELDA;
	while(!(x == 0 && y == largo && z == alto - 1)){
		x2 = x;y2 = y;z2 = z;
		marco.h = altura_text[mapa[x][y][z]];
        if(mapa[x][y][z] != 0){
        	text_actual = texturas[mapa[x][y][z]];
        	x2 *= LADO_CELDA/2;y2 *= LADO_CELDA/2;z2 = (int)(z*LADO_CELDA/2 - altura_text[mapa[x][y][z]]);
        	marco.x = (x2 - y2)/sqrt(2);
        	marco.y = (x2 + 2*z2 + y2)/sqrt(6);
        	marco.x += 200;
        	marco.y += 200;
        	SDL_RenderCopy(renderer, text_actual, NULL, &marco);
        }

        x++;
        if(x == ancho){
            x = 0;z--;
        }
        if(z < 0){
           x = 0;y++;z = alto - 1;
        }
	}
}

