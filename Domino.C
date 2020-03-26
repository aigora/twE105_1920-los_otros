#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct
{
	int numero1;
	int numero2;
} ficha;

int fichaalta(int x[], int y[], int z[], int v[], int n); // determina cuál es la ficha más alta en juego
int primerturno(int x[], int y[], int z[], int v[], int n, int m); // sirve para saber quien empieza a jugar
int comprueba(int x[], int y[], int z[], int v[], int n, int m); // se ejecuta tras cada turno y sirve para comprobar si alguien se ha quedado sin fichas

void imprimirnormal(ficha c[], int y[], int n); // imprime una ficha tal y como está en la matriz
void imprimirreves(ficha c[], int y[], int n); // imprime una ficha dada la vuelta, por ejemplo, la ficha [1|2] la imprime como [2|1]
void juego(ficha c[], int v[], int w[], int x[], int y[], int z[], int n, int m, int p); // imprime todo el tablero de juego

int main()
{
	ficha fichas[29] = // voy a asociar a cada ficha 1 número, que corresponde con la posición ocupada en el vector
	{
		{8, 8}, // fila 0. Sé que esta ficha no existe pero la necesito para poder dar la vuelta a los números de la ficha
		        // Voy a simbolizar la ficha "inversa" con el número asociado pero en negativo
		{0, 1}, // fila 1
		{0, 2}, // fila 2
		{0, 3}, // fila 3
		{0, 4}, // fila 4
		{0, 5}, // fila 5
		{0, 6}, // fila 6
		{1, 2}, // fila 7
		{1, 3}, // fila 8
		{1, 4}, // fila 9
		{1, 5}, // fila 10
		{1, 6}, // fila 11
		{2, 3}, // fila 12
		{2, 4}, // fila 13
		{2, 5}, // fila 14
		{2, 6}, // fila 15
		{3, 4}, // fila 16
		{3, 5}, // fila 17
		{3, 6}, // fila 18
		{4, 5}, // fila 19
		{4, 6}, // fila 20
		{5, 6}, // fila 21
		{0, 0}, // fila 22
		{1, 1}, // fila 23
		{2, 2}, // fila 24
		{3, 3}, // fila 25
		{4, 4}, // fila 26
		{5, 5}, // fila 27
		{6, 6}  // fila 28
	};
	int aleatorio, igual; // estas dos variables van a servir para el reparto inicial de fichas
	int i, j; // estas dos variables las vamos a utilizar para los bucles
	int jugadores; // esta variable va a servir para indicar el número de jugadores, hasta un máximo de 4
	int valores[28]; // vector donde voy a almacenar todos los valores de "aleatorio"
	int fichasjugador1[7]; // vector donde voy a almacenar las fichas del jugador 1
	int fichasjugador2[7]; // vector donde voy a almacenar las fichas del jugador 2
	int fichasjugador3[7]; // vector donde voy a almacenar las fichas del jugador 3
	int fichasjugador4[7]; // vector donde voy a almacenar las fichas del jugador 4
	int tablero[28]; // vector donde voy a ir almacenando las fichas ya jugadas
	int turno; // esta variable sirve para saber quien empieza a jugar
	int fichagrande; // esta variable sirve para saber cuál es la ficha mas alta de las repartidas
	int contador=0; // esta variable sirve para contar el número de fichas que hay en el vector "tablero"
	int final=0; // esta variable determinará cuando se termina la partida
	int repeticion=0; // esta variable se usa para que cada jugador solo puede poner 1 pieza por ronda;
	int ganador; //esta variable va a determinar quién ha ganado la partida
	
	// este bucle solamente sirve para llenar el vector "tablero" de ceros
	// el 0 lo voy a utilizar para simular que no hay ficha
	for(i=0; i<28; i++)
	{
		tablero[i]=0;
	}
	printf("Selecciona el número de jugadores (entre 2 y 4): ");
	scanf("%i", &jugadores); // introduzco el número de jugadores deseados
	srand(time(NULL));

	// este bucle sirve para llenar el vector "valores" con valores aleatorios entre 1 y 28, sin repeticion
	for(i=0; i<28; i++)
	{
		do // uso un do-while porque necesito que, al menos, se genere 1 número aleatorio
		{
			igual=0; // al principio del bucle, igual vale 0. En caso de que el valor generado no coincida con ninguno de los anteriores, el bucle no se repite
			aleatorio=1+(rand()%28); // genero un valor aleatorio
			for(j=0; j<i; j++)
			{
				if(aleatorio==valores[j]) // si el valor generado coincide con alguno de los anteriores, igual valdrá 1
				igual=1;
			}
		}while(igual==1); // se ejecutará siempre que igual valga 1
		valores[i]=aleatorio; // asocio el número generado a una posición del vector "valores"
	}
	
	// este bucle sirve para repatir las fichas entre el número indicado de jugadores usando el vector "valores"
	// asocio 7 números consecutivos a cada jugador, es decir, los 7 primeros al jugador 1, del 8 al 15 al jugador 2 y así sucesivamente
	for(j=1; j<=jugadores; j++) // repito el bucle tantas veces como jugadores haya, pues no quiero repartir a jugadores "inexistentes" en la partida
	{
		for(i=0; i<7;i++)  // repito el bucle 7 veces porque al comenzar la partida cada jugador tiene 7 fichas
		{
			switch(j) 
			{
				case 1: // reparto al jugador 1
					aleatorio=valores[i];
					fichasjugador1[i]=aleatorio;
					break;
				case 2: // reparto al jugador 2
					aleatorio=valores[i+7];
					fichasjugador2[i]=aleatorio;
					break;
				case 3: // reparto al jugador 3
					aleatorio=valores[i+14];
					fichasjugador3[i]=aleatorio;
					break;
				case 4: // reparto al jugador 4
					aleatorio=valores[i+21];
					fichasjugador4[i]=aleatorio;
					break;
			}
		}
	}
	// tras este bucle ya tengo a todos los miembros de la partida con 7 fichas cada uno. Toca ver quién empieza a jugar
	// en el dominó, empieza a jugar quien tenga la ficha más alta, empezando por las fichas dobles
	fichagrande=fichaalta(fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, jugadores); // veo cual es la ficha más alta
	turno=primerturno(fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, jugadores, fichagrande); // veo quién tiene esa ficha
	juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, jugadores, turno, final); // imprimo el tablero de juego
	
	// este bucle sirve para ejecutar el primer turno
	// como ya sabemos quien empieza la partida, pone la ficha más alta en el tablero y se la quita al jugador correspondiente
	for(i=0; i<7; i++)
	{
		switch(turno) // dependiendo de quien empieza la partida
		{
			case 0: 
				if(fichasjugador1[i]==fichagrande)
				{
					tablero[0]=fichagrande; // coloca la ficha en el tablero
					fichasjugador1[i]=0; // le quita la ficha al jugador
				}
				break;
			case 1:
				if(fichasjugador2[i]==fichagrande)
				{
					tablero[0]=fichagrande;
					fichasjugador2[i]=0;
				}
				break;
			case 2:
				if(fichasjugador3[i]==fichagrande)
				{
					tablero[0]=fichagrande;
					fichasjugador3[i]=0;
				}
				break;
			case 3:
				if(fichasjugador4[i]==fichagrande)
				{
					tablero[0]=fichagrande;
					fichasjugador4[i]=0;
				}
				break;
		}
	}
	turno=(turno+1)%4; // avanzamos 1 turno, de forma que le toque al siguiente jugador
	juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, jugadores, turno, final);
	// antes de empezar con el desarrollo de la partida, voy a explicar que tenemos hasta ahora y que voy a hacer en el bucle do-while
	//  hasta ahora tenemos:
		// varios jugadores con 7 fichas cada uno menos 1 de ellos, el que haya colocado la ficha más alta, que tiene 6
		// el vector tablero lleno con 28 ceros salvo su primera posición "tablero[0]", que tiene el número asociado a la ficha más alta que se haya repartido
	// a partir de ahora, cada vez que se ejecute este gran bucle do-while va a corresponder al turno de 1 único jugador, de forma que se repitirá hasta que
	// o 1 de los jugadores se quede sin fichas o, en una ronda completa, nadie pueda poner ficha. Para ello, voy a usar las siguientes variables:
		// contador: va a simbolizar la última casilla del tablero con ficha y, cada vez que un jugador ponga, le sumaré 1 a su valor
		// final: cada vez que 1 jugador no pueda poner, le sumaré 1 a su valor pero, en caso de que algún jugador ponga, volverá a valer 0
		// repetición: cuando algún jugador ponga ficha valdrá 1, de forma que solo puede colocar cuando repeicion=1. Cada vex que avance de turno, valdrá 0
		// ganador: sirve para determinar quien ha ganado. Cada vez que un jugador ponga, valdrá el número de ese jugador, es decir, si coloca el jugador 1, valdrá 1
	do
	{
		for(i=0; i<7; i++) // este bucle sirve para recorrer 1 a 1 las fichas de cada jugador
		{
			switch (turno) // dependiendo de a quien le toque, ejecutará 1 caso u otro
						   // la única diferencia entre los casos es el vector que usa para ver si puede colocar ficha o no
			{
				case 0: // turno del jugador 1
					
					break;
				case 1: // turno del jugador 2
					
					break;
				case 2: // turno del jugador 3
					
					break;
				case 3: // turno del jugador 4
					
					break;
			}
		}
	} while(final<3);
	printf("\n\t   ¡¡¡EL JUGADOR %i HA GANADO!!!", ganador);
	return 0;
}

int fichaalta(int x[], int y[], int z[], int v[], int n)
// x[] es el vector fichasjugador1, y[] el vector fichasjugador2, z[] el vector fichasjugador3, v[] el vector fichasjugador4 y n los jugadores
// esta función sirve para determinar cual es la ficha más alta de entre las repartidas a todos los jugadores
{
	int i, j;
	int max;
	max=x[0];
	for(j=1; j<=n; j++)
	{
		for(i=0; i<7; i++)
		{
			switch(j)
			{
				case 1:
					if(x[i]>max)
					{
						max=x[i];
					}
					break;
				case 2:
					if(y[i]>max)
					{
						max=y[i];
					}
					break;
				case 3:
					if(z[i]>max)
					{
						max=z[i];
					}
					break;
				case 4:
					if(v[i]>max)
					{
						max=v[i];
					}
					break;
			}
		}
	}
	return max;
}

int primerturno(int x[], int y[], int z[], int v[], int n, int m)
// x[] es el vector fichasjugador1, y[] el vector fichasjugador2, z[] el vector fichasjugador3, v[] el vector fichasjugador4, n los jugadores y m es fichagrande
// esta función lo que hace es determinar que jugador tiene la ficha más alta
{
	int i, j, turno;
	for(j=1; j<=n; j++) // repito el bucle tantas veces como jugadores haya en la partida
	{
		for(i=0; i<7; i++) // recorro una a una las casillas de los vectores que contienen a las fichas
		{
			switch(j) // dependiendo del valor de j
			{
				case 1:
					if(x[i]==m) // si la casilla coincide con la ficha más alta, le toca a ese jugador
						turno=0; // el turno del jugador 1 lo simbolizo con el número 0
					break;
				case 2:
					if(y[i]==m)
						turno=1; // el turno del jugador 2 lo simbolizo con el número 1
					break;
				case 3:
					if(z[i]==m)
						turno=2; // el turno del jugador 3 lo simbolizo con el número 2
					break;
				case 4:
					if(v[i]==m)
						turno=3; // el turno del jugador 4 lo simbolizo con el número 3
					break;
			}
		}
	}
	return turno; // la función me devuelve qué jugador tiene la ficha más alta
}

int comprueba(int x[], int y[], int z[], int v[], int n, int m)
// x[] es el vector fichasjugador1, y[] el vector fichasjugador2, z[] el vector fichasjugador3, v[] el vector fichasjugador4, n final y m turno
{
	switch(m) //este bucle sirve para comprobar que todos siguen teniendo fichas
	{
		case 0:
			if((x[0]==0)&&(x[1]==0)&&(x[2]==0)&&(x[3]==0)&&(x[4]==0)&&(x[5]==0)&&(x[6]==0)) // si alguien se queda sin fichas, la partida ha terminado
			n=4;
			break;
		case 1:
			if((y[0]==0)&&(y[1]==0)&&(y[2]==0)&&(y[3]==0)&&(y[4]==0)&&(y[5]==0)&&(y[6]==0))
			n=4;
			break;
		case 2:
			if((z[0]==0)&&(z[1]==0)&&(z[2]==0)&&(z[3]==0)&&(z[4]==0)&&(z[5]==0)&&(z[6]==0))
			n=4;
			break;
		case 3:
			if((v[0]==0)&&(v[1]==0)&&(v[2]==0)&&(v[3]==0)&&(v[4]==0)&&(v[5]==0)&&(v[6]==0))
			n=4;
			break;
	}
	return n;
}

void imprimirnormal(ficha c[], int y[], int n)
{
	int imprime;
	imprime=y[n];
	printf("[%i|%i]", c[imprime].numero1, c[imprime].numero2);
}

void imprimirreves(ficha c[], int y[], int n)
{
	int imprime;
	imprime=y[n]*(-1);
	printf("[%i|%i]", c[imprime].numero2, c[imprime].numero1);
}

void juego(ficha c[], int v[], int w[], int x[], int y[], int z[], int n, int m, int p)
{
	// c[] es el vector de la estructura que contiene las fichas, v[] el vector fichasjugador1, w[] el vector fichasjugador2
	// x[] el vector fichasjugador3, y[] el vector fichasjugador4, z[] es el vector tablero, n es el número de jugadores y m es el turno
	int i, j;
	// este bucle sirve para imprimir las fichas del tablero
	printf("\nTablero:   ");
	for(j=0; j<28; j++)
	{
		if(z[j]>0)
		imprimirnormal(c, z, j);
		if(z[j]<0)
		imprimirreves(c, z, j);
	}
	printf("\n\n");
	// este bucle sirve para imprimr las fichas de cada jugador
	for(j=1; j<=n; j++)
	{
		printf("Jugador %i: ", j);
		for(i=0; i<7;i++)
		{
			switch(j)
			{
				case 1: //imprime las fichas del jugador 1
					if(v[i]>0) // si el número es positivo
					imprimirnormal(c, v, i);
					else if(v[i]<0) // si el número es negativo
					imprimirreves(c, v, i);
					break;
				case 2: //imprime las fichas del jugador 2
					if(w[i]>0)
					imprimirnormal(c, w, i);
					else if(w[i]<0)
					imprimirreves(c, w, i);
					break;
				case 3: //imprime las fichas del jugador 3
					if(x[i]>0)
					imprimirnormal(c, x, i);
					else if(x[i]<0)
					imprimirreves(c, x, i);
					break;
				case 4: //imprime las fichas del jugador 4
					if(y[i]>0)
					imprimirnormal(c, y, i);
					else if(y[i]<0)
					imprimirreves(c, y, i);
					break;
			}
		}
		printf("\n");
	}
	if(p<3)
	printf("\n\t\tTURNO DEL JUGADOR %i\n\n", m+1);
}
