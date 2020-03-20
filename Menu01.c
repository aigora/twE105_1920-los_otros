#include <stdio.h>

void main ()
{
	int input;
	int jugadores;
	int cpus;
	char Repetir;
do{
	do{
		printf("*Simulador de Domino*\n\n");
    	printf("Elige tu modo de juego\n");
    	printf("1: Modo Solo\n");			//Habrá un modo de juego a solas
		printf("2: Modo Multijugador\n");   // Nuestro programa permitira juegos de hasta 4 jugadores, humanos o CPUs
		printf("3: Salir del Programa\n");
		scanf("%i",&input);
    }while(input<1||input>3);
        
  switch(input)
    {
    case 1:
      printf("\nHas selecionado el MODO SOLO\n");
      // Aqui se inicia la funcion de juego con parametro para juego a solo
      break;
    case 2:
		printf("Has selecionado MODO MULTIJUGADOR\n");
    	do{
    		printf("Seleciona el numero de jugadores total 2-4\n");
			printf("0: Salir del Programa\n");
			scanf("%i",&jugadores);
    	}while(jugadores==1||jugadores<0||jugadores>4);
    	if (jugadores == 0)
		{ break;
		}	
    	do{
			printf("Seleciona el numero de CPU (no puede ser mayor que el numero de jugadores)\n");
			scanf("%i",&cpus);
    	}while(cpus<1||cpus>jugadores);
    	printf("has selecionado un juego multijugador con %i jugadores, de los cuales %i son CPUs\n", jugadores, cpus);
    	break;
    case 3:
      printf("Saliendo del programa\n");
      break;
    }
    printf("Quieres Jugar de nuevo?\nSi: y\nNo: n \n");
    scanf("%s",&Repetir);
    
}while(Repetir=='y');
}
