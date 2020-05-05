typedef struct
{
	int numero1;
	int numero2;
} ficha; // esta estructura sirve para simular las fichas, compuestas por 2 numeros enteros entre 0 y 6

void modomultijugador(int jugadores, int dificultad, int cargar); // esta funcion va a contener todo el sistema de juego
	int fichaalta(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[]);
	int primerturno(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int fichagrande);
	void juego(ficha fichas[], int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int tablero[], int pozo[], int jugadores, int turno, int final);
		void imprimirnormal(ficha fichas[], int vectorfichas[], int posicion); 
		void imprimirreves(ficha fichas[], int vectorfichas[], int posicion);
	void siguienteturno(int jugadores, int *turno);
	void jugadorlocal(ficha fichas[], int fichasjugador1[], int tablero[], int *contadortablero, int contadorpozo, int *repeticion, int *final);
		void analizaderecha(ficha fichas[], int fichasjugador1[], int tablero[], int *contadortablero, int *posibilidad, int i);
		void analizaizquierda(ficha fichas[], int fichasjugador1[], int tablero[], int *posibilidad, int i);
		void colocarderecha(ficha fichas[], int fichasjugador1[], int tablero[], int *contadortablero, int eleccionficha);
		void colocarizquierda(ficha fichas[], int fichasjugador1[], int tablero[], int *contadortablero, int eleccionficha);
	void robarficha(int jugador[], int pozo[], int *contadorpozo);
	void desarrollo(ficha fichas[], int jugador[], int tablero[], int *contadortablero, int *repeticion, int *final, int dificultad);
	void comprueba(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int *final, int turno);
	
void introducirfichero(int jugadores, int dificultad, int turno, int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int tablero[], int pozo[], int contadortablero, int contadorpozo, int final, int ganador);

