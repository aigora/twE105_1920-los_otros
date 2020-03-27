#include <stdio.h>

void main ()
{
	int modo;
	int jugadores;
	int cpus;
	char repetir;
	do
	{
		do
		{
			printf("*Simulador de Domino*\n\n");
    		printf("Elige tu modo de juego\n");
    		printf("1: Modo Solo\n");			//	Habrá un modo de juego a solas
			printf("2: Modo Multijugador\n");   // Nuestro programa permitira juegos de hasta 4 jugadores, 1 local y el resto CPU's
			printf("3: Salir del Programa\n");
			scanf("%i",&modo);
    	} while(modo<1||modo>3);
        switch(modo)
    	{
    		case 1:
      			printf("\nHas selecionado el MODO SOLO\n");
      			// Aqui se inicia la funcion de juego con parametro para juego a solo
      			break;
    		case 2:
				printf("Has selecionado MODO MULTIJUGADOR\n");
    			do
				{
    				printf("Seleciona el numero de jugadores total 2-4\n");
					printf("0: Salir del Programa\n");
					scanf("%i",&jugadores);
    			} while(jugadores==1||jugadores<0||jugadores>4);
    			if (jugadores == 0)
				{
					break;
				}
				// Aqui se inicia el modo multijugador, en función del número de jugadores elegido
    			break;
    		case 3:
      			printf("Saliendo del programa\n");
      			break;
    	}
    do
	{
		printf("Quieres Jugar de nuevo?\nSi: y\nNo: n \n");
    	scanf("%s",&repetir);
    } while(repetir!='y' && repetir!='n');
	} while(repetir=='y');
}
