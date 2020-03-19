#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void repartirfichas(int x[28][3], int f, int c); //esta función repartirá las fichas entre todos los jugadores

int main()
{
	// creamos una matriz que contenga las 28 filas, siendo la primera columna el número asociado a cada ficha
	int fichas[28][3] = // matriz 28 x 3
	{
		{0, 0, 0}, // fila 1
		{1, 0, 1}, // fila 2
		{2, 0, 2}, // fila 3
		{3, 0, 3}, // fila 4
		{4, 0, 4}, // fila 5
		{5, 0, 5}, // fila 6
		{6, 0, 6}, // fila 7
		{7, 1, 1}, // fila 8
		{8, 1, 2}, // fila 9
		{9, 1, 3}, // fila 10
		{10, 1, 4}, // fila 11
		{11, 1, 5}, // fila 12
		{12, 1, 6}, // fila 13
		{13, 2, 2}, // fila 14
		{14, 2, 3}, // fila 15
		{15, 2, 4}, // fila 16
		{16, 2, 5}, // fila 17
		{17, 2, 6}, // fila 18
		{18, 3, 3}, // fila 19
		{19, 3, 4}, // fila 20
		{20, 3, 5}, // fila 21
		{21, 3, 6}, // fila 22
		{22, 4, 4}, // fila 23
		{23, 4, 5}, // fila 24
		{24, 4, 6}, // fila 25
		{25, 5, 5}, // fila 26
		{26, 5, 6}, // fila 27
		{27, 6, 6}  // fila 28
	};
	repartirfichas(fichas, 28, 3);
	return 0;
}

void repartirfichas(int x[28][3], int f, int c)
{
	int a, i, j, jugadores, igual;
	int valores[28]; // vector donde voy a almacenar los valores de a
	printf("Selecciona el número de jugadores: ");
	scanf("%i", &jugadores); // introduzco el número de jugadores deseados
	srand(time(NULL));
	for(i=0; i<28; i++) //este bucle sirve para llenar el vector con valores aleatorios de a entre 0 y 27 sin repeticion
	{
		do
		{
			igual=0;
			a=rand()%28;
			for(j=0; j<i; j++)
			{
				if(a==valores[j])
				igual=1;
			}
		}while(igual==1);
		valores[i]=a;
	}
	for(j=1; j<=jugadores; j++) // repartirá fichas a tantos jugadores como le haya indicado
	{
		printf("Jugador %i: ", j); //fichas correspondientes al jugador j (1, 2, 3 o 4)
		for(i=1; i<=7;i++)  //repito el bucle 7 veces pues ak comenzar la partida cada jugador tiene 7 fichas
		{
			switch(j)
			{
				case 1: //reparto al jugador 1
					a=valores[i-1];
					printf("[%i|%i] ", x[a][1], x[a][2]);
					break;
				case 2: //reparto al jugador 2
					a=valores[i+6];
					printf("[%i|%i] ", x[a][1], x[a][2]);
					break;
				case 3: //reparto al jugador 3
					a=valores[i+13];
					printf("[%i|%i] ", x[a][1], x[a][2]);
					break;
				case 4: //reparto al jugador 4
					a=valores[i+20];
					printf("[%i|%i] ", x[a][1], x[a][2]);
					break;
			}
		}
		printf("\n");
	}
}
