typedef struct
{
	int numero1;
	int numero2;
} ficha; // esta estructura sirve para simular las fichas, compuestas por 2 numeros enteros entre 0 y 6

typedef struct
{
	int numero;
	int repeticiones;
} dificil; // esta estructura la voy a emplear en el modo dificil, el primer numero es el numero contado y el segundo es el numero de veces que se repite

void modomultijugador(int jugadores, int dificultad); // esta funcion va a contener todo el sistema de juego
	int fichaalta(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int jugadores);
	int primerturno(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int jugadores, int fichagrande);
	void juego(ficha fichas[], int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int tablero[], int pozo[], int jugadores, int turno, int final);
		void imprimirnormal(ficha fichas[], int vectorfichas[], int posicion); 
		void imprimirreves(ficha fichas[], int vectorfichas[], int posicion);
	int siguienteturno(int jugadores, int turno);
	int jugadorlocal(ficha fichas[], int fichasjugador1[], int tablero[], int contadortablero, int contadorpozo, int repeticion);
		int analizaderecha(ficha fichas[], int fichasjugador1[], int tablero[], int contadortablero, int posibilidad, int i);
		int analizaizquierda(ficha fichas[], int fichasjugador1[], int tablero[], int posibilidad, int i);
		void colocarderecha(ficha fichas[], int fichasjugador1[], int tablero[], int contadortablero, int eleccionficha);
		void colocarizquierda(ficha fichas[], int fichasjugador1[], int tablero[], int contadortablero, int eleccionficha);
	void robarficha(int jugador[], int pozo[], int contadorpozo);
	int modofacil(ficha fichas[], int jugador[], int tablero[], int contadortablero, int repeticion);
	int mododificil(ficha fichas[], int jugador[], int tablero[], int contadortablero, int repeticion);
	int comprueba(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int final, int turno);
