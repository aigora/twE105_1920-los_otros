#include <stdio.h>
#include "Domino.h"

int buscador_prioridad(int numero, ficha fichas[], int jugador[], int tablero[]) // esta funcon busca las veces que un numero ha sido jugado, su prioridad
{
	int prioridad=0, i;
	for(i=0; i<27; i++) // este bucle sirve para comprobar cuantas veces un numero aparece en el tablero o en la mano del jugador
		if(fichas[tablero[i]].numero1==numero||fichas[tablero[i]].numero2==numero||fichas[jugador[i]].numero1==numero||fichas[jugador[i]].numero2==numero) 
			prioridad+=1;
	return prioridad;
}

int comparador(int numero_1, int numero_2, ficha fichas[], int jugador[], int tablero[]) // esta funcion compara la prioridad de dos numeros en una pieza
{
	if(buscador_prioridad(numero_1, fichas, jugador, tablero)>=buscador_prioridad(numero_2, fichas, jugador, tablero))
		return 1;
	else
		return 2;
}

ficha mododificil(ficha fichas[], int jugador[], int tablero[], int *contadortablero)
{
	int prioridades[14]; // en este vector me guardo las posiciones de las fichas por orden de prioridad para ser jugadas
	int lado_de_la_jugada[14]={0}; // en este me voy a guardar de que lado se juega esa pieza
	int lado, derecha=2, izquierda=1;
	int jugabilidad_derecha, jugabilidad_izquierda;
	int valor_alto, i=0;;
	int numero_pieza=7, numero_tablero=7;
	int posicion, mejorpieza=-1;
	ficha respuesta;
	
	for(i=0; i<14; i++) // relleno el bucle de -1
		prioridades[i]=-1;
	
	// Setup inicial 
	// empiezo el bucle
	for(i=0; i<27; i++)
	{
		jugabilidad_derecha=0;
		jugabilidad_izquierda=0;
		lado=0;
		if(tablero[*contadortablero]>0)
		{
			if((jugador[i]>0)&&(fichas[tablero[*contadortablero]].numero2==fichas[jugador[i]].numero1))
				jugabilidad_derecha+=1;
			if((jugador[i]>0)&&(fichas[tablero[*contadortablero]].numero2==fichas[jugador[i]].numero2))
				jugabilidad_derecha+=2;
		}
		if(tablero[*contadortablero]<0)
		{
			if((jugador[i]>0)&&(fichas[tablero[*contadortablero]*(-1)].numero1==fichas[jugador[i]].numero1))
				jugabilidad_derecha+=1;
			if((jugador[i]>0)&&(fichas[tablero[*contadortablero]*(-1)].numero1==fichas[jugador[i]].numero2))
				jugabilidad_derecha+=2;
		}
		if(tablero[0]>0)
		{
			if((jugador[i]>0)&&(fichas[tablero[0]].numero1==fichas[jugador[i]].numero1))
				jugabilidad_izquierda+=1;
			if((jugador[i]>0)&&(fichas[tablero[0]].numero1==fichas[jugador[i]].numero2))
				jugabilidad_izquierda+=2;
		}
		if(tablero[0]<0)
		{
			if((jugador[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[jugador[i]].numero1))
				jugabilidad_izquierda+=1;
			if((jugador[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[jugador[i]].numero2))
				jugabilidad_izquierda+=2;
		}
		// termina la verificación de jugabilidad
		// paso a verificar prioridad
		if(jugabilidad_derecha!=0||jugabilidad_izquierda!=0) // si ambos son 0, no es jugable y no tenemos que mirar prioridades
		{
			if(jugabilidad_derecha==0) // solo se puede colocar por la izquierda
			{
    			lado=izquierda;
    			if(jugabilidad_izquierda==1 || jugabilidad_izquierda==3)
    			{
    				numero_pieza=fichas[jugador[i]].numero2;
    				numero_tablero=fichas[jugador[i]].numero1;
				}
    			if(jugabilidad_izquierda==2)
    			{
    				numero_pieza=fichas[jugador[i]].numero1;
    				numero_tablero=fichas[jugador[i]].numero2;
				}
			}
			if(jugabilidad_izquierda==0) // solo se puede colocar por la derecha
			{
    			lado=derecha;
    			if(jugabilidad_derecha==1 || jugabilidad_derecha==3)
    			{
    				numero_pieza=fichas[jugador[i]].numero2;
    				numero_tablero=fichas[jugador[i]].numero1;
				}	
				if(jugabilidad_derecha==2)
				{
    				numero_pieza=fichas[jugador[i]].numero1;
    				numero_tablero=fichas[jugador[i]].numero2;
				}
			}
			if(jugabilidad_derecha==jugabilidad_izquierda) // si ambas jugabilidades son iguales, la coloco a la derecha
			{
				lado=derecha;
				if(jugabilidad_derecha==1 || jugabilidad_derecha==3)
    			{
    				numero_pieza=fichas[jugador[i]].numero2;
    				numero_tablero=fichas[jugador[i]].numero1;
				}	
				if(jugabilidad_derecha==2)
				{
    				numero_pieza=fichas[jugador[i]].numero1;
    				numero_tablero=fichas[jugador[i]].numero2;
				}
			}
			if(jugabilidad_derecha==3 && (jugabilidad_izquierda==1 || jugabilidad_izquierda==2))
			{
				lado=derecha;
				numero_pieza=fichas[jugador[i]].numero1; // al ser doble miro el numero de la izquierda
				numero_tablero=fichas[jugador[i]].numero1;
			}
			if(jugabilidad_izquierda==3 && (jugabilidad_derecha==1 || jugabilidad_derecha==2))
			{
				lado=izquierda;
				numero_pieza=fichas[jugador[i]].numero1; // al ser doble miro el numero de la izquierda
				numero_tablero=fichas[jugador[i]].numero1;
			}
			if(jugabilidad_derecha==2 && jugabilidad_izquierda==1) // para la explicación de esta parte subiré un documento, para no llenar el codigo más
			{
				valor_alto=comparador(fichas[jugador[i]].numero1, fichas[jugador[i]].numero2, fichas, jugador, tablero);
				if(valor_alto==1)
				{
					lado=izquierda;
					numero_pieza=fichas[jugador[i]].numero2;
					numero_tablero=fichas[jugador[i]].numero1;
				}
				else
				{
					lado=derecha;
					numero_pieza=fichas[jugador[i]].numero1;
					numero_tablero=fichas[jugador[i]].numero2;
				}
			}
			if(jugabilidad_derecha==1 && jugabilidad_izquierda==2)
			{
				valor_alto=comparador(fichas[jugador[i]].numero1, fichas[jugador[i]].numero2, fichas, jugador, tablero);
				if(valor_alto==1)
				{
					lado=derecha;
					numero_pieza=fichas[jugador[i]].numero2;
					numero_tablero=fichas[jugador[i]].numero1;
				}
				else
				{
					lado=izquierda;
					numero_pieza=fichas[jugador[i]].numero1;
					numero_tablero=fichas[jugador[i]].numero2;
				}
			}
			posicion=(buscador_prioridad(numero_pieza, fichas, jugador, tablero)+buscador_prioridad(numero_tablero, fichas, jugador, tablero));
			prioridades[posicion]=i;
			lado_de_la_jugada[posicion]=lado;
		}
	}
	for(i=0; i<14; i++) // al final del bucle, voy a saber la posicion de la pieza que tenga más prioridad
		if(prioridades[i]!=-1)
			mejorpieza=i;
	if(mejorpieza!=-1)
	{
		respuesta.numero1=prioridades[mejorpieza];
		respuesta.numero2=lado_de_la_jugada[mejorpieza];	
	}
	else 
	{
		respuesta.numero1=-1;
		respuesta.numero2=-1;
	}
	return respuesta;
}
