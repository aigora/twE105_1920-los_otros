typedef struct
{
	int numero1;
	int numero2;
} ficha;

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


int mododificil(ficha fichas[], int fichasjugador[], int tablero[], int contadortablero, int contadorpozo)
{
	int prioridades[12] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; // en este vector me guardo las posiciones de las fichas por orden de veces que ya se han jugado
	int jugabilidad_derecha, jugabilidad_izquierda;
	int valor_alto;
	int numero_pieza = 7;
	int numero_tablero = 7;
	int posicion;
	int i; // Setup inicial 
	// empiezo el bucle
	for(i=0; i<27; i++)
	{
		jugabilidad_derecha = 0;
		jugabilidad_izquierda = 0;
		
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
		if (jugabilidad_derecha != 3) // si la posibilidad es 3 la ficha es de numero doble y no hace falta comparar
		{
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
		}
		// termina la verificación de jugabilidad
		// paso a verificar prioridad
		if (jugabilidad_derecha != 0 && jugabilidad_izquierda != 0) // si no es jugable no tenemos que mirar prioridades
		{
			if(jugabilidad_derecha == 3 || jugabilidad_izquierda == 3)
			{
				numero_pieza = fichas[fichasjugador[i]].numero1; // al ser doble miro el 1
				numero_tablero = numero_pieza; // la prioridad viene dada por las veces que se ha jugado un numero 
				//en el caso de una pieza doble, la prioridad del numero que queda fuera y el en que se juega son iguales 
				//porque es el mismo numero
			} else if ((jugabilidad_derecha == 2 && jugabilidad_izquierda == 1 )) // para la explicación de esta parte subiré un documento, para no llenar el codigo más
			{
				valor_alto = comparador(fichas[fichasjugador[i]].numero1,fichas[fichasjugador[i]].numero2,fichas,fichasjugador,tablero,contadortablero);
				if (valor_alto == 1)
				{
				numero_pieza = fichas[fichasjugador[i]].numero1;
				numero_tablero = fichas[tablero[0]].numero1;
				// hay que poner el lado de la jugada, ojo
				}else
				{
				numero_pieza = fichas[fichasjugador[i]].numero2;
				numero_tablero = fichas[tablero[contadortablero]].numero2;	
				}
			}else if ((jugabilidad_derecha == 1 && jugabilidad_izquierda == 2 ))
			{
				valor_alto = comparador(fichas[fichasjugador[i]].numero1,fichas[fichasjugador[i]].numero2,fichas,fichasjugador,tablero,contadortablero);
				if (valor_alto == 1)
				{
				numero_pieza = fichas[fichasjugador[i]].numero1;
				numero_tablero = fichas[tablero[contadortablero]].numero2;
				}else
				{
				numero_pieza = fichas[fichasjugador[i]].numero2;
				numero_tablero = fichas[tablero[0]].numero1;	
				}
			}else if (jugabilidad_izquierda == 2 )
			{
				numero_pieza = numero_pieza = fichas[fichasjugador[i]].numero2;
        		numero_tablero =  fichas[tablero[0]].numero1;

			}
			else if (jugabilidad_izquierda == 1 )
			{
				numero_pieza = numero_pieza = fichas[fichasjugador[i]].numero1;
        		numero_tablero =  fichas[tablero[0]].numero1;
			}
			
		}
	posicion = (buscador_prioridad(numero_pieza,fichas,fichasjugador,tablero,contadortablero) 
					+ buscador_prioridad(numero_tablero,fichas,fichasjugador,tablero,contadortablero ) );
	prioridades[posicion] = i;
	}
	
//
//	i = 12;
//	while(prioridades[i]<0 && )
//	{
//		// finish return function + what happens if you can't play
//	}
//	
//	
}
