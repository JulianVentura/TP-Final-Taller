#include <stdio.h>

int main(int argc, char const *argv[])
{
	int	ancho = 5;
	int largo = 5;
	int alto = 5;
	int x = 0;int y = 0;int z = alto - 1;

	while(y != largo){
		printf("%i , %i ,%i\n",x,y,z);
		x++;
		if(x == ancho){
			x = 0;z--;
		}
		if(z < 0){
			x = 0;y++;z = alto - 1;
		}
		
	}

	return 0;
}