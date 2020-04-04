#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct
{
	int numero1;
	int numero2;
} ficha;

int fichaalta(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int jugadores);
int primerturno(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int jugadores, int fichagrande);
int siguienteturno(int jugadores, int turno);
int comprueba(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int final, int turno);
int modofacil(ficha fichas[], int jugador[], int tablero[], int pozo[], int contadortablero, int repeticion);

void imprimirnormal(ficha fichas[], int vectorfichas[], int posicion); // imprime una ficha tal y como está en la matriz
void imprimirnormal(ficha fichas[], int vectorfichas[], int posicion); // imprime una ficha dada la vuelta, por ejemplo, la ficha [1|2] la imprime como [2|1]
void juego(ficha fichas[], int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int tablero[], int pozo[], int jugadores, int turno, int final);
void modomultijugador(int jugadores, int dificultad); // esta función va a contener todo el sistema de juego
void robarficha(int jugador[], int pozo[], int contadorpozo);

int main()
{
	int modo, jugadores, dificultad;
	char repetir;
	do
	{
		do
		{
			printf("\t\t*Simulador de Domino*\n\n");
    		printf("Elige tu modo de juego\n");
    		printf("1: Modo Solo\n");			//	Habrá un modo de juego a solas
			printf("2: Modo Multijugador\n");   // Nuestro programa permitira juegos de hasta 4 jugadores, 1 local y el resto CPU's
			printf("3: Salir del Programa\n");
			scanf("%i",&modo);
    	} while(modo<1||modo>3); // se volverá a ejecutar siempre que el modo de juego no exista
    	
        switch(modo)
    	{
    		case 1:
      			printf("\nHas seleccionado el MODO SOLO\n");
      			// Aqui se inicia la funcion de juego con parametro para juegar solo
      			break;
    		case 2:
				printf("\nHas seleccionado MODO MULTIJUGADOR\n");
    			do
				{
    				printf("\nSelecciona el numero de jugadores 2-4\n");
					printf("0: Salir del Programa\n");
					scanf("%i",&jugadores);
    			} while(jugadores==1||jugadores<0||jugadores>4);
    			if (jugadores == 0)
				{
					break;
				}
				do
				{
					printf("\nSelecciona la dificultad del juego\nFacil: 1\nDificil: 2\n");
    				scanf("%s",&dificultad);
    			} while(dificultad!='1' && dificultad!='2');
				modomultijugador(jugadores, dificultad);
    			break;
    		case 3:
      			printf("Saliendo del programa\n");
      			break;
    	}
    do
	{
		printf("\nQuieres Jugar de nuevo?\nSi: y\nNo: n \n");
    	scanf("%s",&repetir);
    } while(repetir!='y' && repetir!='n');
	} while(repetir=='y');
	return 0;
}

int fichaalta(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int jugadores)
// esta función sirve para determinar cual es la ficha más alta de entre las repartidas a todos los jugadores
{
	int i, j, max;
	max=fichasjugador1[0];
	for(j=1; j<=jugadores; j++)
	{
		for(i=0; i<7; i++)
		{
			switch(j)
			{
				case 1:
					if(fichasjugador1[i]>max)
					{
						max=fichasjugador1[i];
					}
					break;
				case 2:
					if(fichasjugador2[i]>max)
					{
						max=fichasjugador2[i];
					}
					break;
				case 3:
					if(fichasjugador3[i]>max)
					{
						max=fichasjugador3[i];
					}
					break;
				case 4:
					if(fichasjugador4[i]>max)
					{
						max=fichasjugador4[i];
					}
					break;
			}
		}
	}
	return max;
}

int primerturno(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int jugadores, int fichagrande)
// esta función lo que hace es determinar que jugador tiene la ficha más alta
{
	int i, j, turno;
	for(j=1; j<=jugadores; j++) // repito el bucle tantas veces como jugadores haya en la partida
	{
		for(i=0; i<7; i++) // recorro una a una las casillas de los vectores que contienen a las fichas
		{
			switch(j) // dependiendo del valor de j
			{
				case 1:
					if(fichasjugador1[i]==fichagrande) // si la casilla coincide con la ficha más alta, le toca a ese jugador
						turno=0; // el turno del jugador 1 lo simbolizo con el número 0
					break;
				case 2:
					if(fichasjugador2[i]==fichagrande)
						turno=1; // el turno del jugador 2 lo simbolizo con el número 1
					break;
				case 3:
					if(fichasjugador3[i]==fichagrande)
						turno=2; // el turno del jugador 3 lo simbolizo con el número 2
					break;
				case 4:
					if(fichasjugador4[i]==fichagrande)
						turno=3; // el turno del jugador 4 lo simbolizo con el número 3
					break;
			}
		}
	}
	return turno; // la función me devuelve qué jugador tiene la ficha más alta
}

int siguienteturno(int jugadores, int turno)
{
	if(jugadores==2)
		return (turno+1)%2;	
	if(jugadores==3)
		return (turno+1)%3;
	if(jugadores==4)
		return (turno+1)%4;
}

int comprueba(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int final, int turno)
{
	int i, sinfichas=1;
	for(i=0; i<28; i++)
	{
		switch(turno) //este bucle sirve para comprobar que todos siguen teniendo fichas
		{
			case 0:
				if(fichasjugador1[i]!=0)
				sinfichas=0;
				break;
			case 1:
				if(fichasjugador2[i]!=0)
				sinfichas=0;
				break;
			case 2:
				if(fichasjugador3[i]!=0)
				sinfichas=0;
				break;
			case 3:
				if(fichasjugador4[i]!=0)
				sinfichas=0;
				break;
		}
	}
	if(sinfichas==1)
		final=4;
	return final;
}

void imprimirnormal(ficha fichas[], int vectorfichas[], int posicion)
{
	printf("[%i|%i]", fichas[vectorfichas[posicion]].numero1, fichas[vectorfichas[posicion]].numero2);
}

void imprimirreves(ficha fichas[], int vectorfichas[], int posicion)
{
	printf("[%i|%i]", fichas[vectorfichas[posicion]*(-1)].numero2, fichas[vectorfichas[posicion]*(-1)].numero1);
}

void juego(ficha fichas[], int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int tablero[], int pozo[], int jugadores, int turno, int final)
{
	int i, j;
	// este bucle sirve para imprimir las fichas del tablero
	printf("\nTablero:   ");
	for(j=0; j<28; j++)
	{
		if(tablero[j]>0)
		imprimirnormal(fichas, tablero, j);
		if(tablero[j]<0)
		imprimirreves(fichas, tablero, j);
	}
	printf("\n\n");
	// este bucle sirve para imprimr las fichas de cada jugador
	for(j=1; j<=jugadores; j++)
	{
		printf("Jugador %i: ", j);
		for(i=0; i<28;i++)
		{
			switch(j)
			{
				case 1: //imprime las fichas del jugador 1
					if(fichasjugador1[i]>0)
					imprimirnormal(fichas, fichasjugador1, i);
					break;
				case 2: //imprime las fichas del jugador 2
					if(fichasjugador2[i]>0)
					imprimirnormal(fichas, fichasjugador2, i);
					break;
				case 3: //imprime las fichas del jugador 3
					if(fichasjugador3[i]>0)
					imprimirnormal(fichas, fichasjugador3, i);
					break;
				case 4: //imprime las fichas del jugador 4
					if(fichasjugador4[i]>0)
					imprimirnormal(fichas, fichasjugador4, i);
					break;
			}
		}
		printf("\n");
	}
	printf("\nPozo:   ");
	for(j=0; j<28; j++)
	{
		if(pozo[j]>0)
		imprimirnormal(fichas, pozo, j);
	}
	if(final<3)
	printf("\n\n\t\tTURNO DEL JUGADOR %i\n\n", turno+1);
}

void modomultijugador(int jugadores, int dificultad) // el parámetro n se refiere al número de jugadores y m a la dificultad
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
	int valores[28]={0}; // vector donde voy a almacenar todos los valores de "aleatorio"
	int fichasjugador1[28]={0}; // vector donde voy a almacenar las fichas del jugador 1
	int fichasjugador2[28]={0}; // vector donde voy a almacenar las fichas del jugador 2
	int fichasjugador3[28]={0}; // vector donde voy a almacenar las fichas del jugador 3
	int fichasjugador4[28]={0}; // vector donde voy a almacenar las fichas del jugador 4
	int tablero[28]={0}; // vector donde voy a ir almacenando las fichas ya jugadas
	int pozo[28]={0}; // este vector contrendrá las fichas que no se hayan repartido al principio de la partida
	int turno; // esta variable sirve para saber quien empieza a jugar
	int fichagrande; // esta variable sirve para saber cuál es la ficha mas alta de las repartidas
	int contadortablero=0; // esta variable sirve para contar el número de fichas que hay en el vector "tablero"
	int contadorpozo; // esta variable sirve para contar el número de fichas que hay en el vector "pozo"
	int final=0; // esta variable determinará cuando se termina la partida
	int repeticion=0; // esta variable se usa para que cada jugador solo puede poner 1 pieza por ronda;
	int ganador; //esta variable va a determinar quién ha ganado la partida

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
	for(j=1; j<=jugadores+1; j++) // repito el bucle tantas veces como jugadores haya, pues no quiero repartir a jugadores "inexistentes" en la partida
	{
		if(jugadores==2)
		{
			switch(j) 
				{
					case 1: // reparto al jugador 1
						for(i=0; i<7; i++)
						{
							aleatorio=valores[i];
							fichasjugador1[i]=aleatorio;
						}
						break;
					case 2: // reparto al jugador 2
						for(i=0; i<7; i++)
						{
							aleatorio=valores[i+7];
							fichasjugador2[i]=aleatorio;
						}
						break;
					case 3: // introduzco el resto de las fichas en el vector "pozo"
						for(i=0; i<14; i++)
						{
							aleatorio=valores[i+14];
							pozo[i]=aleatorio;
						}
						break;
				}
				contadorpozo=13;
		}
		if(jugadores==3) // si hay 3 jugadores, reparto 7 fichas a cada jugador y las 7 restantes van al pozo
		{
			for(i=0; i<7;i++)
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
					case 4: // introduzco el resto de las fichas en el vector "pozo"
						aleatorio=valores[i+21];
						pozo[i]=aleatorio;
						break;
				}
			}
			contadorpozo=6;
		}
		if(jugadores==4) // si hay 4 jugadores, reparto 7 fichas a cada jugador
		{
			for(i=0; i<7;i++)
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
					case 5: // no hay fichas en el pozo
						break;
				}
			}
			contadorpozo=-1;
		}
	}
	// tras este bucle ya tengo a todos los miembros de la partida con 7 fichas cada uno y las restantes en el pozo. Toca ver quién empieza a jugar
	// en el dominó, empieza a jugar quien tenga la ficha más alta, empezando por las fichas dobles
	fichagrande=fichaalta(fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, jugadores); // veo cual es la ficha más alta
	turno=primerturno(fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, jugadores, fichagrande); // veo quién tiene esa ficha
	juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final); // imprimo el tablero de juego
	
	// este bucle sirve para ejecutar el primer turno, el cuál se realizará de forma automática
	// como ya sabemos quien empieza la partida, pone la ficha más alta en el tablero y se la quita al jugador correspondiente
	for(i=0; i<28; i++)
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
	turno=siguienteturno(jugadores, turno); // avanzamos 1 turno, de forma que le toque al siguiente jugador
	juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
	
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
	if(dificultad=='1')
	{
		do
		{
			do
			{
				switch(turno)
				{
					case 0: // turno del jugador 1
						repeticion=modofacil(fichas, fichasjugador1, tablero, pozo, contadortablero, repeticion);
						if(repeticion==0&&contadorpozo!=-1)
						{
							robarficha(fichasjugador1, pozo, contadorpozo);
							contadorpozo-=1;
							juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
						}
						if(repeticion==1)
						{
							ganador=1;
							contadortablero+=1;
							final=0;
						}
						break;
					case 1: // turno del jugador 2
						repeticion=modofacil(fichas, fichasjugador2, tablero, pozo, contadortablero, repeticion);
						if(repeticion==0&&contadorpozo!=-1)
						{
							robarficha(fichasjugador2, pozo, contadorpozo);
							contadorpozo-=1;
							juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
						}
						if(repeticion==1)
						{
							ganador=2;
							contadortablero+=1;
							final=0;
						}
						break;
					case 2: // turno del jugador 3
						repeticion=modofacil(fichas, fichasjugador3, tablero, pozo, contadortablero, repeticion);
						if(repeticion==0&&contadorpozo!=-1)
						{
							robarficha(fichasjugador3, pozo, contadorpozo);
							contadorpozo-=1;
							juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
						}
						if(repeticion==1)
						{
							ganador=3;
							contadortablero+=1;
							final=0;
						}
						break;
					case 3: // turno del jugador 4
						repeticion=modofacil(fichas, fichasjugador4, tablero, pozo, contadortablero, repeticion);
						if(repeticion==0&&contadorpozo!=-1)
						{
							robarficha(fichasjugador4, pozo, contadorpozo);
							contadorpozo-=1;
							juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
						}
						if(repeticion==1)
						{
							ganador=4;
							contadortablero+=1;
							final=0;
						}
						break;
				} 
			} while(repeticion==0&&contadorpozo!=-1);
			if(repeticion==0)
				final+=1;
			final=comprueba(fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, final, turno);
			repeticion=0;
			turno=siguienteturno(jugadores, turno);
			juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
		} while(final<3);
	printf("\n\t   ¡¡¡EL JUGADOR %i HA GANADO!!!\n", ganador);
	}
}

int modofacil(ficha fichas[], int jugador[], int tablero[], int pozo[], int contadortablero, int repeticion)
{
	int i,j;
	for(i=0; i<27; i++)
	{
		if((tablero[0]>0)&&(tablero[contadortablero]>0)) // si los números asociados a ambas fichas son positivos...
		{
			if((jugador[i]>0)&&(fichas[tablero[0]].numero1==fichas[jugador[i]].numero2)&&(repeticion==0))
			{
				for(j=0; j<=contadortablero; j++)
					tablero[contadortablero+1-j]=tablero[contadortablero-j];
				tablero[0]=jugador[i];
				jugador[i]=0;
				repeticion=1;
			}
			else if((jugador[i]>0)&&(fichas[tablero[contadortablero]].numero2==fichas[jugador[i]].numero1)&&(repeticion==0))
			{
				tablero[contadortablero+1]=jugador[i];
				jugador[i]=0;
				repeticion=1;
			}
			else if((jugador[i]>0)&&(fichas[tablero[contadortablero]].numero2==fichas[jugador[i]].numero2)&&(repeticion==0))
			{
				tablero[contadortablero+1]=jugador[i]*(-1);
				jugador[i]=0;
				repeticion=1;
			}
			else if((jugador[i]>0)&&(fichas[tablero[0]].numero1==fichas[jugador[i]].numero1)&&(repeticion==0))
			{
				for(j=0; j<=contadortablero; j++)
					tablero[contadortablero+1-j]=tablero[contadortablero-j];
				tablero[0]=jugador[i]*(-1);
				jugador[i]=0;
				repeticion=1;
			}
		}
		if((tablero[0]>0)&&(tablero[contadortablero]<0)) // en el caso de que el primero sea positivo y el segundo negativo...
		{
			if((jugador[i]>0)&&(fichas[tablero[0]].numero1==fichas[jugador[i]].numero2)&&(repeticion==0))
			{
				for(j=0; j<=contadortablero; j++)
					tablero[contadortablero+1-j]=tablero[contadortablero-j];
				tablero[0]=jugador[i];
				jugador[i]=0;
				repeticion=1;
			}
			else if((jugador[i]>0)&&(fichas[tablero[contadortablero]*(-1)].numero1==fichas[jugador[i]].numero1)&&(repeticion==0))
			{
				tablero[contadortablero+1]=jugador[i];
				jugador[i]=0;
				repeticion=1;
			}
			else if((jugador[i]>0)&&(fichas[tablero[contadortablero]*(-1)].numero1==fichas[jugador[i]].numero2)&&(repeticion==0))
			{
				tablero[contadortablero+1]=jugador[i]*(-1);
				jugador[i]=0;
				repeticion=1;
			}
			else if((jugador[i]>0)&&(fichas[tablero[0]].numero1==fichas[jugador[i]].numero1)&&(repeticion==0))
			{
				for(j=0; j<=contadortablero; j++)
					tablero[contadortablero+1-j]=tablero[contadortablero-j];
				tablero[0]=jugador[i]*(-1);
				jugador[i]=0;
				repeticion=1;
			}
		}
		if((tablero[0]<0)&&(tablero[contadortablero]>0)) // en el caso de que el primero sea negativo y el segundo positivo...
		{
			if((jugador[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[jugador[i]].numero2)&&(repeticion==0))
			{
				for(j=0; j<=contadortablero; j++)
					tablero[contadortablero+1-j]=tablero[contadortablero-j];
				tablero[0]=jugador[i];
				jugador[i]=0;
				repeticion=1;
			}
			else if((jugador[i]>0)&&(fichas[tablero[contadortablero]].numero2==fichas[jugador[i]].numero1)&&(repeticion==0))
			{
				tablero[contadortablero+1]=jugador[i];
				jugador[i]=0;
				repeticion=1;
			}
			else if((jugador[i]>0)&&(fichas[tablero[contadortablero]].numero2==fichas[jugador[i]].numero2)&&(repeticion==0))
			{
				tablero[contadortablero+1]=jugador[i]*(-1);
				jugador[i]=0;
				repeticion=1;
			}
			else if((jugador[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[jugador[i]].numero1)&&(repeticion==0))
			{
				for(j=0; j<=contadortablero; j++)
					tablero[contadortablero+1-j]=tablero[contadortablero-j];
				tablero[0]=jugador[i]*(-1);
				jugador[i]=0;
				repeticion=1;
			}
		}
		if((tablero[0]<0)&&(tablero[contadortablero]<0)) // si los números asociados a ambas fichas son negativos...
		{
			if((jugador[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[jugador[i]].numero2)&&(repeticion==0))
			{
				for(j=0; j<=contadortablero; j++)
					tablero[contadortablero+1-j]=tablero[contadortablero-j];
				tablero[0]=jugador[i];
				jugador[i]=0;
				repeticion=1;
			}
			else if((jugador[i]>0)&&(fichas[tablero[contadortablero]*(-1)].numero1==fichas[jugador[i]].numero1)&&(repeticion==0))
			{
				tablero[contadortablero+1]=jugador[i];
				jugador[i]=0;
				repeticion=1;
			}
			else if((jugador[i]>0)&&(fichas[tablero[contadortablero]*(-1)].numero1==fichas[jugador[i]].numero2)&&(repeticion==0))
			{
				tablero[contadortablero+1]=jugador[i]*(-1);
				jugador[i]=0;
				repeticion=1;
			}
			else if((jugador[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[jugador[i]].numero1)&&(repeticion==0))
			{
				for(j=0; j<=contadortablero; j++)
					tablero[contadortablero+1-j]=tablero[contadortablero-j];
				tablero[0]=jugador[i]*(-1);
				jugador[i]=0;
				repeticion=1;
			}
		}	
	}	
	return repeticion;
}

void robarficha(int jugador[], int pozo[], int contadorpozo)
{
	int i;
	for(i=0; i<27; i++)
		jugador[27-i]=jugador[26-i];
	jugador[0]=pozo[contadorpozo];
	pozo[contadorpozo]=0;
}
