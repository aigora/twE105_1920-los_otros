#include <stdio.h>
#include "Domino.h"

main(int argc, char *argv[])
{
	int jugadores=0, dificultad=0, cargar;
	char repetir;
	printf("\t\t*Simulador de Domino*\n\n");
	do
	{
		printf("Elige una opcion:\n"); // Nuestro programa permitira juegos de hasta 4 jugadores, 1 local y el resto CPU's
		printf("1: Nueva partida\n");
		printf("2: Cargar partida\n");
		scanf("%i",&cargar);
		if(cargar==1)
		{
			do
			{
				printf("\nSelecciona el numero de jugadores (entre 2 y 4)\n");
				printf("0: Salir del Programa\n");
				scanf("%i", &jugadores);
			}while(jugadores==1||jugadores<0||jugadores>4);
			switch(jugadores)
			{
				case 0:
					break;
				default:
					do
					{
						printf("\nSelecciona la dificultad del juego:\n");
						printf("1: Facil\n");
						printf("2: Dificil\n");
						printf("0: Salir del Programa\n");
						scanf("%i", &dificultad);
					}while(dificultad!=0 && dificultad!=1 && dificultad!=2);
					switch(dificultad)
					{
						case 0:
							break;
						default:
							modomultijugador(jugadores, dificultad, cargar);
							break;
					}
					break;
			}
		}
		if(cargar==2)
			modomultijugador(jugadores, dificultad, cargar);
   		do
		{
			printf("Quieres Jugar de nuevo?\n");
			printf("Si: y\n");
			printf("No: n\n");
    		scanf("%s",&repetir);
   		} while(repetir!='y' && repetir!='n'&& repetir!='Y'&& repetir!='N');
	} while(repetir=='y'||repetir=='Y');
}
