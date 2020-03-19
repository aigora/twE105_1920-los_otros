#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	// creamos una matriz que contenga las 28 filas, siendo la primera columna el número asociado a cada ficha
	int fichas[28][3] = // Matriz 28 x 3
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
	int a, b, i, j, jugadores;
	printf("Selecciona el número de jugadores: ");
	scanf("%i", &jugadores);
	srand(time(NULL));
	for(j=1; j<=jugadores; j++)
	{
		printf("Jugador %i: ", j);
		for(i=1; i<=7;i++)
		{
			a=rand()%28;
			printf("[%i|%i] ", fichas[a][1], fichas[a][2]);
		}
		printf("\n");
	}
	return 0;
}
