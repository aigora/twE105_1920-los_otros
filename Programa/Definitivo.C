#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Domino.h"

int main()
{
	int modo, jugadores=0, dificultad=0, cargar;
	char repetir;
	do
	{
		do
		{
			printf("\t\t*Simulador de Domino*\n\n");
    		printf("Elige tu modo de juego:\n");
    		printf("1: Modo Solo\n");			//	Habra un modo de juego a solas
			printf("2: Modo Multijugador\n");   // Nuestro programa permitira juegos de hasta 4 jugadores, 1 local y el resto CPU's
			printf("3: Salir del Programa\n");
			scanf("%i",&modo);
    	} while(modo<1||modo>3); // se volvera a ejecutar siempre que el modo de juego no exista
        switch(modo)
    	{
    		case 1:
      			printf("\nHas seleccionado el MODO SOLO\n");
      			// Aqui se inicia la funcion de juego con parametro para jugar solo
      			break;
    		case 2:
				printf("\nHas seleccionado MODO MULTIJUGADOR\n");
    			printf("Elige una opcion:\n");
    			printf("1: Nueva partida\n");
    			printf("2: Cargar partida\n");
    			scanf("%i",&cargar);
    			if(cargar==1)
    			{
    				do
					{
	    				printf("\nSelecciona el numero de jugadores 2-4\n");
	    				printf("0: Salir del Programa\n");
						scanf("%i", &jugadores);
	    			} while(jugadores==1||jugadores<0||jugadores>4);
	    			if(jugadores==0)
						break;
					do
					{
						printf("\nSelecciona la dificultad del juego:\n");
						printf("Elige una opcion:\n");
		    			printf("1: Facil\n");
		    			printf("2: Dificil\n");
		    			printf("0: Salir del Programa\n");
	    				scanf("%i", &dificultad);
	    			} while(dificultad!=0 && dificultad!=1 && dificultad!=2);
	    			if(dificultad==0)
						break;
					modomultijugador(jugadores, dificultad, cargar);
				}
				if(cargar==2)
	    			modomultijugador(jugadores, dificultad, cargar);
    			break;
    		case 3:
      			printf("Saliendo del programa\n");
      			break;
    	}
   		do
		{
			printf("Quieres Jugar de nuevo?\n");
			printf("Si: y\n");
			printf("No: n\n");
    		scanf("%s",&repetir);
   		} while(repetir!='y' && repetir!='n'&& repetir!='Y'&& repetir!='N');
	} while(repetir=='y'||repetir=='Y');
	return 0;
}
