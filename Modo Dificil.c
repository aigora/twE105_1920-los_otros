#include <stdio.h>

typedef struct
{
	int numero1;
	int numero2;
} ficha;


int buscador_prioridad(int numero,ficha fichas[], int fichasjugador[], int tablero[], int contadortablero);
int comparador(int numero_1, int numero_2,ficha fichas[], int fichasjugador[], int tablero[], int contadortablero);
ficha mododificil(ficha fichas[], int fichasjugador[], int tablero[], int contadortablero);


int main()
{
	ficha fichas[29] = // voy a asociar a cada ficha 1 numero, que corresponde con la posicion ocupada en el vector
	{
		{8, 8}, // fila 0. Se que esta ficha no existe pero la necesito para poder dar la vuelta a los numeros de la ficha
		        // Voy a simbolizar la ficha "inversa" con el numero asociado pero en negativo
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
	
	int tablero[28] = {-19, -13, -2, 1, 23, 11, 28, -20, -9, 10, 21, -15}; // valores de prueba
	int contadortablero = 11;
	int fichasjugador[28] = {14, 27};
	ficha jugada = mododificil(fichas, fichasjugador, tablero, contadortablero);
	printf("%i     %i", jugada.numero1, jugada.numero2);
}


int buscador_prioridad(int numero,ficha fichas[], int fichasjugador[], int tablero[], int contadortablero) // esta funcon busca las veces que un numero ha sido jugado, su prioridad
{
	int prioridad = 0;
	int i;
	for(i=0; i<contadortablero; i++) // este bucle sirve para comprobar cuantas veces un numero aparece en el tablero (de un total de 7, estando 1 en la mano del jugador)
	{
		if( (fichas[tablero[i]].numero1==numero || fichas[tablero[i]].numero2==numero ) || fichas[tablero[i]].numero1==(-numero) || fichas[tablero[i]].numero2==(-numero)) 
		{
			prioridad += 1;
		}
		
	}
	for(i=0; i<21; i++) // este bucle sirve para comprobar cuantas veces un numero aparece en en la mano del jugador contando la ficha en si
	{
		if( (fichas[fichasjugador[i]].numero1==numero || fichas[fichasjugador[i]].numero2==numero ) || fichas[fichasjugador[i]].numero1==(-numero) || fichas[fichasjugador[i]].numero2==(-numero)) 
		{
			prioridad += 1;
		}
		
	}
	return prioridad;
}



int comparador(int numero_1, int numero_2,ficha fichas[], int fichasjugador[], int tablero[], int contadortablero) // esta funcion compara la prioridad de dos numeros en una pieza
{
	int a = buscador_prioridad(numero_1,fichas,fichasjugador,tablero,contadortablero);
	int b = buscador_prioridad(numero_2,fichas,fichasjugador,tablero,contadortablero);
	
	if (a >= b)
	{
		return 1;
	}else
	{
		return 2;	
	}
}


ficha mododificil(ficha fichas[], int fichasjugador[], int tablero[], int contadortablero)
{
	int prioridades[14] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; // en este vector me guardo las posiciones de las fichas por orden de prioridad para ser jugadas
	int lado_de_la_jugada[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // en este me voy a guardar de que lado se juega esa pieza
	int lado;
	int jugabilidad_derecha, jugabilidad_izquierda;
	int derecha = 2, izquierda = 1;
	int valor_alto;
	int numero_pieza = 7;
	int numero_tablero = 7;
	int posicion, mejorpieza;
	int i;
	ficha respuesta;
	
	 // Setup inicial 
	// empiezo el bucle
	for(i=0; i<27; i++)
	{
		jugabilidad_derecha = 0;
		jugabilidad_izquierda = 0;
		lado = 0;
		
		if(tablero[contadortablero]>0)
		{
			if((fichasjugador[i]>0)&&(fichas[tablero[contadortablero]].numero2==fichas[fichasjugador[i]].numero1))
				jugabilidad_derecha += 1;
			if((fichasjugador[i]>0)&&(fichas[tablero[contadortablero]].numero2==fichas[fichasjugador[i]].numero2))
				jugabilidad_derecha += 2;
		}else if(tablero[contadortablero]<0)
		{
			if((fichasjugador[i]>0)&&(fichas[tablero[contadortablero]*(-1)].numero1==fichas[fichasjugador[i]].numero1))
				jugabilidad_derecha +=1;
			if((fichasjugador[i]>0)&&(fichas[tablero[contadortablero]*(-1)].numero1==fichas[fichasjugador[i]].numero2))
				jugabilidad_derecha +=2;
		}
			if(tablero[0]>0)
			{
				if((fichasjugador[i]>0)&&(fichas[tablero[0]].numero1==fichas[fichasjugador[i]].numero1))
				jugabilidad_izquierda += 1;
				if((fichasjugador[i]>0)&&(fichas[tablero[0]].numero1==fichas[fichasjugador[i]].numero2))
				jugabilidad_izquierda += 2;
			}else if(tablero[0]<0)
			{
				if((fichasjugador[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[fichasjugador[i]].numero1))
				jugabilidad_izquierda += 1;
				if((fichasjugador[i]>0)&&(fichas[tablero[0]*(-1)].numero2==fichas[fichasjugador[i]].numero2))
				jugabilidad_izquierda += 2;
			}
		// termina la verificación de jugabilidad
		// paso a verificar prioridad
		if (jugabilidad_derecha != 0 || jugabilidad_izquierda != 0) // si no es jugable no tenemos que mirar prioridades
		{
			switch ( jugabilidad_derecha )
			{
    			case 3:
    				numero_pieza = fichas[fichasjugador[i]].numero1; // al ser doble miro el numero de la izquierda
					numero_tablero = numero_pieza;
					lado = derecha;
        			break;
        		case 0:                                              // como he comprobado que se puede jugar arriba miro que numero puedo jugar al otro lado
        			lado = izquierda;
        			numero_tablero = fichas[tablero[0]].numero1;
        			
        			if (jugabilidad_izquierda == 1)
        			{
        				numero_pieza = fichas[fichasjugador[i]].numero1;	
					}else
					{
						numero_pieza = fichas[fichasjugador[i]].numero2;
					}
        			break;
        		default:
        			break;
			}
			switch ( jugabilidad_izquierda )
			{
    			case 3:
					numero_pieza = fichas[fichasjugador[i]].numero1;
					numero_tablero = numero_pieza;
					lado = izquierda;
        			break;
        		case 0:
        			lado = derecha;
        			numero_tablero = fichas[tablero[contadortablero]].numero2;
        			
        			if (jugabilidad_derecha == 1)
        			{
        				numero_pieza = fichas[fichasjugador[i]].numero1;	
					}else
					{
						numero_pieza = fichas[fichasjugador[i]].numero2;
					}
        			break;
        		default:
        			break;
			}
			if (jugabilidad_derecha == jugabilidad_izquierda)
			{
				if (jugabilidad_derecha == 1)
				{
					numero_pieza = fichas[fichasjugador[i]].numero1;
					numero_tablero = fichas[tablero[contadortablero]].numero2;
					lado = derecha;
				}else
				{
					numero_pieza = fichas[fichasjugador[i]].numero2;
					numero_tablero = fichas[tablero[contadortablero]].numero2;
					lado = derecha;
				}
			} else if ((jugabilidad_derecha == 2 && jugabilidad_izquierda == 1 )) // para la explicación de esta parte subiré un documento, para no llenar el codigo más
			{
				valor_alto = comparador(fichas[fichasjugador[i]].numero1,fichas[fichasjugador[i]].numero2,fichas,fichasjugador,tablero,contadortablero);
				if (valor_alto == 1)
				{
				numero_pieza = fichas[fichasjugador[i]].numero1;
				numero_tablero = fichas[tablero[0]].numero1;
				lado = izquierda;
				}else
				{
				numero_pieza = fichas[fichasjugador[i]].numero2;
				numero_tablero = fichas[tablero[contadortablero]].numero2;
				lado = derecha;	
				}
			}else
			{
				valor_alto = comparador(fichas[fichasjugador[i]].numero1,fichas[fichasjugador[i]].numero2,fichas,fichasjugador,tablero,contadortablero);
				if (valor_alto == 1)
				{
				numero_pieza = fichas[fichasjugador[i]].numero1;
				numero_tablero = fichas[tablero[contadortablero]].numero2;
				lado = derecha;
				}else
				{
				numero_pieza = fichas[fichasjugador[i]].numero2;
				numero_tablero = fichas[tablero[0]].numero1;
				lado = izquierda;	
				}
			}
			posicion = (buscador_prioridad(numero_pieza,fichas,fichasjugador,tablero,contadortablero) 
				+ buscador_prioridad(numero_tablero,fichas,fichasjugador,tablero,contadortablero ) );
			prioridades[posicion] = i;
			lado_de_la_jugada[posicion] = lado;
		}

	}
	mejorpieza = -1; // al final del bucle, voy a saber la posicion de la pieza que tenga más prioridad
	for(i=0;i<14;i++)
	{
		if (prioridades[i] != -1)
		{
			mejorpieza = i;
		}
	}
	
	if (mejorpieza != -1)
	{
	respuesta.numero1 = prioridades[mejorpieza];
	respuesta.numero2 = lado_de_la_jugada[mejorpieza];	
	} else 
	{
	respuesta.numero1 = -1;
	respuesta.numero2 = -1;
	}
	
	return respuesta;
}
