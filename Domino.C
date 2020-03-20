#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int primerturno(int x[], int y[], int z[], int v[], int n);
void imprimirficha(int x[28][3], int y[], int n);

int main()
{
	int fichas[28][3] = // matriz 28 x 3, siendo la primera columna el número asociado a cada ficha
	                    // la segunda y tercera columna forman todas las combinaciones posibles de fichas
	{
		{0, 0, 1}, // fila 1
		{1, 0, 2}, // fila 2
		{2, 0, 3}, // fila 3
		{3, 0, 4}, // fila 4
		{4, 0, 5}, // fila 5
		{5, 0, 6}, // fila 6
		{6, 1, 2}, // fila 7
		{7, 1, 3}, // fila 8
		{8, 1, 4}, // fila 9
		{9, 1, 5}, // fila 10
		{10, 1, 6}, // fila 11
		{11, 2, 3}, // fila 12
		{12, 2, 4}, // fila 13
		{13, 2, 5}, // fila 14
		{14, 2, 6}, // fila 15
		{15, 3, 4}, // fila 16
		{16, 3, 5}, // fila 17
		{17, 3, 6}, // fila 18
		{18, 4, 5}, // fila 19
		{19, 4, 6}, // fila 20
		{20, 5, 6}, // fila 21
		{21, 0, 0}, // fila 22
		{22, 1, 1}, // fila 23
		{23, 2, 2}, // fila 24
		{24, 3, 3}, // fila 25
		{25, 4, 4}, // fila 26
		{26, 5, 5}, // fila 27
		{27, 6, 6}  // fila 28
	};
	int aleatorio; // esta variable va a servir para el reparto inicial de fichas
	int igual; // esta variable va a servir para el reparto inicial de fichas
	int i, j; // estas dos variables las vamos a utilizar para los bucles
	int jugadores; // esta variable va a servir para indicar el número de jugadores, hasta un máximo de 4
	int valores[28]; // vector donde voy a almacenar todos los valores de a
	int fichasjugador1[7]; // vector donde voy a almacenar las fichas del jugador 1
	int fichasjugador2[7]; // vector donde voy a almacenar las fichas del jugador 2
	int fichasjugador3[7]; // vector donde voy a almacenar las fichas del jugador 3
	int fichasjugador4[7]; // vector donde voy a almacenar las fichas del jugador 4
	int tablero[28]; // vector donde voy a ir almacenando las fichas ya jugadas
	int turno; // esta variable sirve para saber a quien le toca jugar
	
	//este bucle solamente sirve para llenar el vector tablero de -5
	//esto me va a servir para que el vector no este vacio, de forma que cada vez que introduzca una ficha nueva lo sustituiré
	for(i=0; i<28; i++)
	{
		tablero[i]=-1;
	}
	
	printf("Selecciona el número de jugadores (entre 2 y 4): ");
	scanf("%i", &jugadores); // introduzco el número de jugadores deseados
	srand(time(NULL));

	//este bucle sirve para llenar el vector "valores" con valores aleatorios de a entre 0 y 27 sin repeticion
	for(i=0; i<28; i++)
	{
		do // uso un do-while porque necesito que, al menos, se genere 1 número aleatorio
		{
			igual=0;
			aleatorio=rand()%28;
			for(j=0; j<i; j++)
			{
				if(aleatorio==valores[j]) // si algún valor de a se repite, el bucle do-while se volverá a ejecutar
				igual=1;
			}
		}while(igual==1);
		valores[i]=aleatorio;
	}
	
	//este bucle sirve para repatir las fichas entre el número indicado de jugadores
	for(j=1; j<=jugadores; j++)
	{
		for(i=1; i<=7;i++)  //repito el bucle 7 veces pues al comenzar la partida cada jugador tiene 7 fichas
		{
			switch(j)
			{
				case 1: //reparto al jugador 1
					aleatorio=valores[i-1];
					fichasjugador1[i-1]=aleatorio; // asocio a cada posición del vector una ficha
					break;
				case 2: //reparto al jugador 2
					aleatorio=valores[i+6];
					fichasjugador2[i-1]=aleatorio;
					break;
				case 3: //reparto al jugador 3
					aleatorio=valores[i+13];
					fichasjugador3[i-1]=aleatorio;
					break;
				case 4: //reparto al jugador 4
					aleatorio=valores[i+20];
					fichasjugador4[i-1]=aleatorio;
					break;
			}
		}
	}
	turno=primerturno(fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, jugadores);
	printf("\t\t TURNO JUGADOR %i\n", turno+1);
	for(j=1; j<=jugadores; j++)
	{
		printf("Jugador %i: ", j);
		for(i=1; i<=7;i++)
		{
			switch(j)
			{
				case 1: 
					imprimirficha(fichas, fichasjugador1, i-1);
					break;
				case 2:
					imprimirficha(fichas, fichasjugador2, i-1);
					break;
				case 3:
					imprimirficha(fichas, fichasjugador3, i-1);
					break;
				case 4:
					imprimirficha(fichas, fichasjugador4, i-1);
					break;
			}
		}
		printf("\n");
	}
	return 0;
}

int primerturno(int x[], int y[], int z[], int v[], int n)
{
	int i, j, turno;
	for(j=1; j<=n; j++)
	{
		for(i=0; i<7; i++)
		{
			switch(j)
			{
				case 1:
					if(x[i]==27) //compruebo que jugador tiene el 6 doble
					turno=0;
					break;
				case 2:
					if(y[i]==27)
					turno=1;
					break;
				case 3:
					if(z[i]==27)
					turno=2;
					break;
				case 4:
					if(v[i]==27)
					turno=3;
					break;
			}
		}
	}
	return turno;
}

void imprimirficha(int x[28][3], int y[], int n)
{
	int imprime;
	imprime=y[n];
	printf("[%i|%i]", x[imprime][1], x[imprime][2]);
}
