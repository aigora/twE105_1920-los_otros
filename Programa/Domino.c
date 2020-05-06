#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Domino.h"

void modomultijugador(int jugadores, int dificultad, int cargar) // el parametro n se refiere al numero de jugadores y m a la dificultad
{
	FILE *txt;
	ficha fichas[29];
	int i=1, j, h;
	int aleatorio, igual; // estas dos variables van a servir para el reparto inicial de fichas
	int cargarpartida[175]; //esta variable va a servir para leer los valores del fichero
	int valores[28]={0}; // vector donde voy a almacenar todos los valores de "aleatorio"
	int fichasjugador1[28]={0}; // vector donde voy a almacenar las fichas del jugador 1
	int fichasjugador2[28]={0}; // vector donde voy a almacenar las fichas del jugador 2
	int fichasjugador3[28]={0}; // vector donde voy a almacenar las fichas del jugador 3
	int fichasjugador4[28]={0}; // vector donde voy a almacenar las fichas del jugador 4
	int tablero[28]={0}; // vector donde voy a ir almacenando las fichas ya jugadas
	int pozo[28]={0}; // este vector contrendra las fichas que no se hayan repartido al principio de la partida
	int turno; // esta variable sirve para saber quien empieza a jugar
	int fichagrande; // esta variable sirve para saber cual es la ficha mas alta de las repartidas
	int contadortablero=0; // esta variable sirve para contar el numero de fichas que hay en el vector "tablero"
	int contadorpozo=-1; // esta variable sirve para contar el numero de fichas que hay en el vector "pozo"
	int final=0; // esta variable determinara cuando se termina la partida
	int repeticion=0; // esta variable se usa para que cada jugador solo puede poner 1 pieza por ronda;
	int ganador=0; //esta variable va a determinar quien ha ganado la partida	
	
	// los dos bucles siguientes sirven para crear las fichas
	fichas->numero1=8;
	fichas->numero2=8;
	for(j=0; j<6; j++)
	{
		for(h=(j+1); h<7; h++)
		{
			(fichas+i)->numero1=j;
			(fichas+i)->numero2=h;
			i++;
		}
	}
	for(j=0; j<7; j++) // ahora genero las fichas dobles
	{
		(fichas+i)->numero1=j;
		(fichas+i)->numero2=j;
		i++;
	} i=0;

	if(cargar==1) // solo se va a ejecutar cuando se empieze una nueva partida
	{
		srand(time(NULL));
		for(i=0; i<28; i++)
		{
			do
			{
				igual=0; 
				aleatorio=1+(rand()%28); // genero valores aleaorios entre 1 y 28
				for(j=0; j<i; j++)
				{
					if(aleatorio==valores[j])
						igual=1;
				}
			}while(igual==1); // si un numero se repite, se genero otro
			valores[i]=aleatorio;
		}
		
		// este bucle sirve para repatir las fichas entre el numero indicado de jugadores usando el vector "valores"
		// asocio 7 numeros consecutivos a cada jugador, es decir, los 7 primeros al jugador 1, del 8 al 15 al jugador 2 y asi sucesivamente
		for(i=0; i<7; i++)
		{
			fichasjugador1[i]=valores[i];
			fichasjugador2[i]=valores[i+7];
			fichasjugador3[i]=valores[i+14];
			fichasjugador4[i]=valores[i+21];
			if(jugadores==2)
			{
				for(j=0; j<14; j++)
					pozo[j]=valores[j+14];
				fichasjugador3[i]=0;
				fichasjugador4[i]=0;
				contadorpozo=13;
			}
			if(jugadores==3)
			{
				pozo[i]=valores[i+21];
				fichasjugador4[i]=0;
				contadorpozo=6;
			}
		}
		// tras este bucle ya tengo a todos los miembros de la partida con 7 fichas cada uno y las restantes en el pozo. Toca ver quien empieza a jugar
		// en el domino, empieza a jugar quien tenga la ficha mas alta, empezando por las fichas dobles
		fichagrande=fichaalta(fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4); // veo cual es la ficha mas alta
		turno=primerturno(fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, fichagrande); // veo quien tiene esa ficha
		juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final); // imprimo el tablero de juego
		
		// este bucle sirve para ejecutar el primer turno, el cual se realizara de forma automatica
		// como ya sabemos quien empieza la partida, pone la ficha mas alta en el tablero y se la quita al jugador correspondiente
		for(i=0; i<28; i++)
		{
			if(fichasjugador1[i]==fichagrande)
			{
				tablero[0]=fichagrande; // coloca la ficha en el tablero
				fichasjugador1[i]=0; // le quita la ficha al jugador
			}
			if(fichasjugador2[i]==fichagrande)
			{
				tablero[0]=fichagrande;
				fichasjugador2[i]=0;
			}
			if(fichasjugador3[i]==fichagrande)
			{
				tablero[0]=fichagrande;
				fichasjugador3[i]=0;
			}
			if(fichasjugador4[i]==fichagrande)
			{
				tablero[0]=fichagrande;
				fichasjugador4[i]=0;
			}
		}
		
		for(i=0; i<7; i++)
		{
			if(turno==0)
				if(fichasjugador1[i]==0)
					for(j=0; j<27-i;j++)
						fichasjugador1[i+j]=fichasjugador1[i+1+j];
			if(turno==1)
					if(fichasjugador2[i]==0)
						for(j=0; j<27-i;j++)
							fichasjugador2[i+j]=fichasjugador2[i+1+j];
			if(turno==2)
					if(fichasjugador3[i]==0)
						for(j=0; j<27-i;j++)
							fichasjugador3[i+j]=fichasjugador3[i+1+j];
			if(turno==3)
					if(fichasjugador4[i]==0)
						for(j=0; j<27-i;j++)
							fichasjugador4[i+j]=fichasjugador4[i+1+j];
		}
		
		siguienteturno(jugadores, &turno); // avanzamos 1 turno, de forma que le toque al siguiente jugador
		juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
		introducirfichero(jugadores, dificultad, turno, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, contadortablero, contadorpozo, final, ganador);
	}

	if(cargar==2)
	{
		txt=fopen("partida.txt", "r");
		if(txt==NULL)
			printf("Error al abrir el archivo.\n");
		else
		{
			while(fscanf(txt, "%i", &jugadores)!=EOF)
			{
				cargarpartida[i]=jugadores;
				i++;
			}
		}
		fclose(txt);
		i=0;
		for(i=0; i<175; i++)
		{
			if(i==0)
				jugadores=cargarpartida[i];
			if(i==1)
				dificultad=cargarpartida[i];
			if(i==2)
				turno=cargarpartida[i];
			if((i>=3)&&(i<=30))
				fichasjugador1[i-3]=cargarpartida[i];
			if((i>=31)&&(i<=58))
				fichasjugador2[i-31]=cargarpartida[i];
			if((i>=59)&&(i<=86))
				fichasjugador3[i-59]=cargarpartida[i];
			if((i>=87)&&(i<=114))
				fichasjugador4[i-87]=cargarpartida[i];
			if((i>=115)&&(i<=142))
				tablero[i-115]=cargarpartida[i];
			if((i>=143)&&(i<=170))
				pozo[i-143]=cargarpartida[i];
			if(i==171)
				contadortablero=cargarpartida[i];
			if(i==172)
				contadorpozo=cargarpartida[i];
			if(i==173)
				final=cargarpartida[i];
			if(i==174)
				ganador=cargarpartida[i];
		}
		juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
	}

	do //este bucle contiene el desarrollo de la partida
	{
		do
		{
			switch(turno)
			{
				case 0: // turno del jugador 1
					jugadorlocal(fichas, fichasjugador1, tablero, &contadortablero, contadorpozo, &repeticion, &final);
					if(repeticion==0&&contadorpozo!=-1)
					{
						robarficha(fichasjugador1, pozo, &contadorpozo);
						juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
					}
					if(repeticion==1)
						ganador=1;
					break;
				case 1: // turno del jugador 2
					desarrollo(fichas, fichasjugador2, tablero, &contadortablero, &repeticion, &final, dificultad);
					if(repeticion==0&&contadorpozo!=-1)
					{
						robarficha(fichasjugador2, pozo, &contadorpozo);
						juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
					}
					if(repeticion==1)
						ganador=2;
					break;
				case 2: // turno del jugador 3
					desarrollo(fichas, fichasjugador3, tablero, &contadortablero, &repeticion, &final, dificultad);
					if(repeticion==0&&contadorpozo!=-1)
					{
						robarficha(fichasjugador3, pozo, &contadorpozo);
						juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
					}
					if(repeticion==1)
						ganador=3;
					break;
				case 3: // turno del jugador 4
					desarrollo(fichas, fichasjugador4, tablero, &contadortablero, &repeticion, &final, dificultad);
					if(repeticion==0&&contadorpozo!=-1)
					{
						robarficha(fichasjugador4, pozo, &contadorpozo);
						juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
					}
					if(repeticion==1)
						ganador=4;
					break;
			} 
		} while(repeticion==0&&contadorpozo!=-1);
		if(repeticion==0)
			final+=1;
		comprueba(fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, &final, turno);
		repeticion=0;
		siguienteturno(jugadores, &turno);
		juego(fichas, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, jugadores, turno, final);
		introducirfichero(jugadores, dificultad, turno, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, contadortablero, contadorpozo, final, ganador);
	} while(final<3);
	printf("\n\n\t   ¡¡¡EL JUGADOR %i HA GANADO!!!\n", ganador);
}

int fichaalta(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[])
{
	int i, max=fichasjugador1[0];
	for(i=0; i<7; i++)
	{
		if(fichasjugador1[i]>max)
			max=fichasjugador1[i];
		if(fichasjugador2[i]>max)
			max=fichasjugador2[i];
		if(fichasjugador3[i]>max)
			max=fichasjugador3[i];
		if(fichasjugador4[i]>max)
			max=fichasjugador4[i];
	}
	return max; // la funcion devuelve cual es la ficha mas alta de entre todas las repartidas. Recordemos que no tener ficha se simboliza con el 0
}

int primerturno(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int fichagrande)
{
	int i, turno;
	for(i=0; i<7; i++) // recorro una a una las casillas de los vectores que contienen a las fichas
	{
		if(fichasjugador1[i]==fichagrande) // si la casilla coincide con la ficha mas alta, le toca a ese jugador
			return 0; // el turno del jugador 1 lo simbolizo con el numero 0
		if(fichasjugador2[i]==fichagrande)
			return 1; // el turno del jugador 2 lo simbolizo con el numero 1
		if(fichasjugador3[i]==fichagrande)
			return 2; // el turno del jugador 3 lo simbolizo con el numero 2
		if(fichasjugador4[i]==fichagrande)
			return 3; // el turno del jugador 4 lo simbolizo con el numero 3
	}
}

void juego(ficha fichas[], int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int tablero[], int pozo[], int jugadores, int turno, int final)
// esta funcion sirve para imprimir el tablero de juego
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
	// este bucle sirve para imprimir las fichas de cada jugador
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
	// este bucle sirve para imprimir las fichas del pozo
	printf("\nPozo:   ");
	for(j=0; j<28; j++)
		if(pozo[j]>0)
			imprimirnormal(fichas, pozo, j);
	// en el caso de que la partida no haya terminado, imprime el siguiente turno
	if(final<3)
		printf("\n\n\t\tTURNO DEL JUGADOR %i\n\n", turno+1);
}

void imprimirnormal(ficha fichas[], int vectorfichas[], int posicion)
{
	printf("[%i|%i]", fichas[vectorfichas[posicion]].numero1, fichas[vectorfichas[posicion]].numero2);
}

void imprimirreves(ficha fichas[], int vectorfichas[], int posicion)
{
	printf("[%i|%i]", fichas[vectorfichas[posicion]*(-1)].numero2, fichas[vectorfichas[posicion]*(-1)].numero1);
}

void siguienteturno(int jugadores, int *turno)
{
	if(jugadores==2)
		*turno=(*turno+1)%2;	
	if(jugadores==3)
		*turno=(*turno+1)%3;
	if(jugadores==4)
		*turno=(*turno+1)%4;
}

void jugadorlocal(ficha fichas[], int fichasjugador1[], int tablero[], int *contadortablero, int contadorpozo, int *repeticion, int *final)
{
	int i, eleccion, posibilidad=0, eleccionficha, eleccionlado;
	for(i=0; i<27; i++) // este bucle sirve para comprobar si puede poner alguna ficha
	{
		analizaderecha(fichas, fichasjugador1, tablero, contadortablero, &posibilidad, i);
		analizaizquierda(fichas, fichasjugador1, tablero, &posibilidad, i);
	}
	do
	{
		printf("Opciones para este turno:\n");
		printf("1: Poner ficha\n");
		if(contadorpozo!=-1)
			printf("2: Robar ficha\n");
		if(contadorpozo==-1)
			printf("2: No puedo colocar\n");
		scanf("%i",&eleccion);
		if(posibilidad==0&&eleccion==1)
		{
			do
			{
				if(contadorpozo!=-1)
					printf("No puede poner ficha. Hay que robar\n");
				if(contadorpozo==-1)
					printf("No puede poner ficha. Hay que pasar.\n");
				scanf("%i",&eleccion);
			}while(eleccion!=2);
		}
	} while(eleccion<1||eleccion>2);
	posibilidad=0;
	switch(eleccion)
	{
		case 1: // en el caso de que se haya escojido poner ficha y se pueda poner
			printf("Escoja que ficha quiere poner (empieza por la ficha 1):\n");
			scanf("%i",&eleccionficha);
			analizaderecha(fichas, fichasjugador1, tablero, contadortablero, &posibilidad, eleccionficha-1);
			analizaizquierda(fichas, fichasjugador1, tablero, &posibilidad, eleccionficha-1);
			if(posibilidad==0) // si esa ficha no se puede poner te obliga a escoger otra
			{
				while(posibilidad==0)
				{
					printf("Esa ficha no se puede poner, escoja otra.\n");
					scanf("%i",&eleccionficha);
					analizaderecha(fichas, fichasjugador1, tablero, contadortablero, &posibilidad, eleccionficha-1);
					analizaizquierda(fichas, fichasjugador1, tablero, &posibilidad, eleccionficha-1);
				}
			}
			posibilidad=0;
			printf("¿Por que lado la quiere colocar?\n1: Derecha\n2: Izquierda\n");
			scanf("%i",&eleccionlado);
			do
			{
				if(eleccionlado==1)
					analizaderecha(fichas, fichasjugador1, tablero, contadortablero, &posibilidad, eleccionficha-1);
				if(eleccionlado==2)
					analizaizquierda(fichas, fichasjugador1, tablero, &posibilidad, eleccionficha-1);
				if(posibilidad==0) // si no se puede colocar por el lado escogido
				{
					printf("No se puede colocar por ese lado. Escoja el otro\n");
					scanf("%i",&eleccionlado);
				}
			}while(posibilidad==0);
			// una vez ya sabemos la ficha que queremos colocar y porque lado hacerlo...
			if(eleccionlado==1)
				colocarderecha(fichas, fichasjugador1, tablero, contadortablero, eleccionficha-1);
			if(eleccionlado==2)
				colocarizquierda(fichas, fichasjugador1, tablero, contadortablero, eleccionficha-1);
			*repeticion=1;
			*contadortablero+=1;
			*final=0;
			break;
		case 2:
			*repeticion=0;
			break;
	}
}

void analizaderecha(ficha fichas[], int fichasjugador1[], int tablero[], int *contadortablero, int *posibilidad, int i)
{
	if(tablero[*contadortablero]>0)
	{
		if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortablero]].numero2==fichas[fichasjugador1[i]].numero1))
			*posibilidad=1;
		if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortablero]].numero2==fichas[fichasjugador1[i]].numero2))
			*posibilidad=1;
	}
	if(tablero[*contadortablero]<0)
	{
		if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortablero]*(-1)].numero1==fichas[fichasjugador1[i]].numero1))
			*posibilidad=1;
		if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortablero]*(-1)].numero1==fichas[fichasjugador1[i]].numero2))
			*posibilidad=1;
	}
}

void analizaizquierda(ficha fichas[], int fichasjugador1[], int tablero[], int *posibilidad, int i)
{
	if(tablero[0]>0)
	{
		if((fichasjugador1[i]>0)&&(fichas[tablero[0]].numero1==fichas[fichasjugador1[i]].numero1))
			*posibilidad=1;
		if((fichasjugador1[i]>0)&&(fichas[tablero[0]].numero1==fichas[fichasjugador1[i]].numero2))
			*posibilidad=1;
	}
	if(tablero[0]<0)
	{
		if((fichasjugador1[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[fichasjugador1[i]].numero1))
			*posibilidad=1;
		if((fichasjugador1[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[fichasjugador1[i]].numero2))
			*posibilidad=1;
	}
}
void colocarderecha(ficha fichas[], int fichasjugador1[], int tablero[], int *contadortablero, int eleccionficha)
{
	int j;
	if(tablero[*contadortablero]>0)
	{
		if((fichasjugador1[eleccionficha]>0)&&(fichas[tablero[*contadortablero]].numero2==fichas[fichasjugador1[eleccionficha]].numero1))
		{
			tablero[*contadortablero+1]=fichasjugador1[eleccionficha];
			fichasjugador1[eleccionficha]=0;
		}
		if((fichasjugador1[eleccionficha]>0)&&(fichas[tablero[*contadortablero]].numero2==fichas[fichasjugador1[eleccionficha]].numero2))
		{
			tablero[*contadortablero+1]=fichasjugador1[eleccionficha]*(-1);
			fichasjugador1[eleccionficha]=0;
		}
	}
	if(tablero[*contadortablero]<0)
	{
		if((fichasjugador1[eleccionficha]>0)&&(fichas[tablero[*contadortablero]*(-1)].numero1==fichas[fichasjugador1[eleccionficha]].numero1))
		{
			tablero[*contadortablero+1]=fichasjugador1[eleccionficha];
			fichasjugador1[eleccionficha]=0;
		}
		if((fichasjugador1[eleccionficha]>0)&&(fichas[tablero[*contadortablero]*(-1)].numero1==fichas[fichasjugador1[eleccionficha]].numero2))
		{
			tablero[*contadortablero+1]=fichasjugador1[eleccionficha]*(-1);
			fichasjugador1[eleccionficha]=0;
		}
	}
	for(j=0; j<27-eleccionficha;j++)
		fichasjugador1[eleccionficha+j]=fichasjugador1[eleccionficha+1+j];
}

void colocarizquierda(ficha fichas[], int fichasjugador1[], int tablero[], int *contadortablero, int eleccionficha)
{
	int j;
	if(tablero[0]>0)
	{
		if((fichasjugador1[eleccionficha]>0)&&(fichas[tablero[0]].numero1==fichas[fichasjugador1[eleccionficha]].numero2))
		{
			for(j=0; j<=*contadortablero; j++)
				tablero[*contadortablero+1-j]=tablero[*contadortablero-j];
			tablero[0]=fichasjugador1[eleccionficha];
			fichasjugador1[eleccionficha]=0;
		}
		if((fichasjugador1[eleccionficha]>0)&&(fichas[tablero[0]].numero1==fichas[fichasjugador1[eleccionficha]].numero1))
		{
			for(j=0; j<=*contadortablero; j++)
				tablero[*contadortablero+1-j]=tablero[*contadortablero-j];
			tablero[0]=fichasjugador1[eleccionficha]*(-1);
			fichasjugador1[eleccionficha]=0;
		}
	}
	if(tablero[0]<0)
	{
		if((fichasjugador1[eleccionficha]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[fichasjugador1[eleccionficha]].numero2))
		{
			for(j=0; j<=*contadortablero; j++)
				tablero[*contadortablero+1-j]=tablero[*contadortablero-j];
			tablero[0]=fichasjugador1[eleccionficha];
			fichasjugador1[eleccionficha]=0;
		}
		if((fichasjugador1[eleccionficha]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[fichasjugador1[eleccionficha]].numero1))
		{
			for(j=0; j<=*contadortablero; j++)
				tablero[*contadortablero+1-j]=tablero[*contadortablero-j];
			tablero[0]=fichasjugador1[eleccionficha]*(-1);
			fichasjugador1[eleccionficha]=0;
		}
	}
	for(j=0; j<27-eleccionficha;j++)
		fichasjugador1[eleccionficha+j]=fichasjugador1[eleccionficha+1+j];
}

void robarficha(int jugador[], int pozo[], int *contadorpozo)
{
	int i;
	for(i=0; i<27; i++)
		jugador[27-i]=jugador[26-i];
	jugador[0]=pozo[*contadorpozo];
	pozo[*contadorpozo]=0;
	*contadorpozo-=1;
}

void desarrollo(ficha fichas[], int jugador[], int tablero[], int *contadortablero, int *repeticion, int *final, int dificultad)
{
	int i, j;
	ficha jugada;
	if(dificultad==1) // se ejecuta el modo facil
	{
		for(i=0; i<27; i++)
		{
			if((tablero[0]>0)&&(tablero[*contadortablero]>0)) // si los numeros asociados a ambas fichas son positivos...
			{
				if((jugador[i]>0)&&(fichas[tablero[0]].numero1==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					for(j=0; j<=*contadortablero; j++)
						tablero[*contadortablero+1-j]=tablero[*contadortablero-j];
					tablero[0]=jugador[i];
					jugador[i]=0;
					*repeticion=1;
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortablero]].numero2==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					tablero[*contadortablero+1]=jugador[i];
					jugador[i]=0;
					*repeticion=1;
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortablero]].numero2==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					tablero[*contadortablero+1]=jugador[i]*(-1);
					jugador[i]=0;
					*repeticion=1;
				}
				else if((jugador[i]>0)&&(fichas[tablero[0]].numero1==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					for(j=0; j<=*contadortablero; j++)
						tablero[*contadortablero+1-j]=tablero[*contadortablero-j];
					tablero[0]=jugador[i]*(-1);
					jugador[i]=0;
					*repeticion=1;
				}
			}
			if((tablero[0]>0)&&(tablero[*contadortablero]<0)) // en el caso de que el primero sea positivo y el segundo negativo...
			{
				if((jugador[i]>0)&&(fichas[tablero[0]].numero1==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					for(j=0; j<=*contadortablero; j++)
						tablero[*contadortablero+1-j]=tablero[*contadortablero-j];
					tablero[0]=jugador[i];
					jugador[i]=0;
					*repeticion=1;
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortablero]*(-1)].numero1==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					tablero[*contadortablero+1]=jugador[i];
					jugador[i]=0;
					*repeticion=1;
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortablero]*(-1)].numero1==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					tablero[*contadortablero+1]=jugador[i]*(-1);
					jugador[i]=0;
					*repeticion=1;
				}
				else if((jugador[i]>0)&&(fichas[tablero[0]].numero1==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					for(j=0; j<=*contadortablero; j++)
						tablero[*contadortablero+1-j]=tablero[*contadortablero-j];
					tablero[0]=jugador[i]*(-1);
					jugador[i]=0;
					*repeticion=1;
				}
			}
			if((tablero[0]<0)&&(tablero[*contadortablero]>0)) // en el caso de que el primero sea negativo y el segundo positivo...
			{
				if((jugador[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					for(j=0; j<=*contadortablero; j++)
						tablero[*contadortablero+1-j]=tablero[*contadortablero-j];
					tablero[0]=jugador[i];
					jugador[i]=0;
					*repeticion=1;
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortablero]].numero2==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					tablero[*contadortablero+1]=jugador[i];
					jugador[i]=0;
					*repeticion=1;
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortablero]].numero2==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					tablero[*contadortablero+1]=jugador[i]*(-1);
					jugador[i]=0;
					*repeticion=1;
				}
				else if((jugador[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					for(j=0; j<=*contadortablero; j++)
						tablero[*contadortablero+1-j]=tablero[*contadortablero-j];
					tablero[0]=jugador[i]*(-1);
					jugador[i]=0;
					*repeticion=1;
				}
			}
			if((tablero[0]<0)&&(tablero[*contadortablero]<0)) // si los numeros asociados a ambas fichas son negativos...
			{
				if((jugador[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					for(j=0; j<=*contadortablero; j++)
						tablero[*contadortablero+1-j]=tablero[*contadortablero-j];
					tablero[0]=jugador[i];
					jugador[i]=0;
					*repeticion=1;
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortablero]*(-1)].numero1==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					tablero[*contadortablero+1]=jugador[i];
					jugador[i]=0;
					*repeticion=1;
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortablero]*(-1)].numero1==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					tablero[*contadortablero+1]=jugador[i]*(-1);
					jugador[i]=0;
					*repeticion=1;
				}
				else if((jugador[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					for(j=0; j<=*contadortablero; j++)
						tablero[*contadortablero+1-j]=tablero[*contadortablero-j];
					tablero[0]=jugador[i]*(-1);
					jugador[i]=0;
					*repeticion=1;
				}
			}
		}
	}
	if(dificultad==2) // se ejecuta el modo dificil
	{
		jugada=mododificil(fichas, jugador, tablero, contadortablero);
		printf("\n%i %i\n", jugada.numero1, jugada.numero2);
		if(jugada.numero2==-1)
			*repeticion=0;
		else 
		{
			if(jugada.numero2==1)
				colocarizquierda(fichas, jugador, tablero, contadortablero, jugada.numero1);
			 else if(jugada.numero2==2)
				colocarderecha(fichas, jugador, tablero, contadortablero, jugada.numero1);
			*repeticion=1;
		}
	}
	if(*repeticion==1)
	{
		*contadortablero+=1;
		*final=0;
	}
}

void comprueba(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int *final, int turno)
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
		*final=4;
}

void introducirfichero(int jugadores, int dificultad, int turno, int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int tablero[], int pozo[], int contadortablero, int contadorpozo, int final, int ganador)
{
	FILE *txt;
	int i;
	txt=fopen("partida.txt", "w");
	if(txt==NULL)
		printf("Error al abrir el archivo.\n");
	else
	{
		fprintf(txt, "%i\n", jugadores);
		fprintf(txt, "%i\n", dificultad);
		fprintf(txt, "%i\n", turno);
		for(i=0; i<28; i++)
			fprintf(txt, "%i ", fichasjugador1[i]);
		fprintf(txt, "\n");
		for(i=0; i<28; i++)
			fprintf(txt, "%i ", fichasjugador2[i]);
		fprintf(txt, "\n");
		for(i=0; i<28; i++)
			fprintf(txt, "%i ", fichasjugador3[i]);
		fprintf(txt, "\n");
		for(i=0; i<28; i++)
			fprintf(txt, "%i ", fichasjugador4[i]);
		fprintf(txt, "\n");
		for(i=0; i<28; i++)
			fprintf(txt, "%i ", tablero[i]);
		fprintf(txt, "\n");
		for(i=0; i<28; i++)
			fprintf(txt, "%i ", pozo[i]);
		fprintf(txt, "\n%i\n", contadortablero);
		fprintf(txt, "%i\n", contadorpozo);
		fprintf(txt, "%i\n", final);
		fprintf(txt, "%i\n", ganador);
	}
	fclose(txt);
}
