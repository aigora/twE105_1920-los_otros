#include <SDL2/SDL.h>

typedef struct
{
	int numero1;
	int numero2;
} ficha; // esta estructura sirve para simular las fichas, compuestas por 2 numeros enteros entre 0 y 6

void modomultijugador(int jugadores, int dificultad, int cargar); // esta funcion va a contener todo el sistema de juego
	int fichaalta(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[]);
	int primerturno(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int fichagrande);
	void siguienteturno(int jugadores, int *turno);
	void analiza(ficha fichas[], int fichasjugador1[], int tablero[], int *contadortableroderecha, int *contadortableroizquierda, int *posibilidad, int i);
	void colocarderecha(ficha fichas[], int fichasjugador1[], int tablero[], int *contadortableroderecha, int eleccionficha);
	void colocarizquierda(ficha fichas[], int fichasjugador1[], int tablero[], int *contadortableroizquierda, int eleccionficha);
	void robarficha(int jugador[], int pozo[], int *contadorpozo);
	void desarrollo(ficha fichas[], int jugador[], int tablero[], int *contadortableroderecha, int *contadortableroizquierda, int *repeticion, int *final, int dificultad);
	void comprueba(int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int *final, int turno);
	int buscador_prioridad(int numero,ficha fichas[], int fichasjugador[], int tablero[]);
	int comparador(int numero_1, int numero_2,ficha fichas[], int fichasjugador[], int tablero[]);
	ficha mododificil(ficha fichas[], int jugador[], int tablero[], int *contadortableroderecha, int *contadortableroizquierda);
void introducirfichero(int jugadores, int dificultad, int turno, int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int tablero[], int pozo[], int contadortableroderecha, int contadortableroizquierda, int contadorpozo, int final, int ganador);


void imprimirfichas4jugadores(SDL_Surface *ficha1[], SDL_Surface *ficha2[], SDL_Surface *ficha3[], SDL_Surface *ficha4[], SDL_Surface *windowSurface, SDL_Rect dest1[], SDL_Rect dest2[], SDL_Rect dest3[], SDL_Rect dest4[], int jugador1[], int jugador2[], int jugador3[], int jugador4[]);
void imprimirfichas3jugadores(SDL_Surface *ficha1[], SDL_Surface *ficha2[], SDL_Surface *ficha3[], SDL_Surface *ficha4[], SDL_Surface *windowSurface, SDL_Rect dest1[], SDL_Rect dest2[], SDL_Rect dest3[], SDL_Rect dest4[], int jugador1[], int jugador2[], int jugador3[], int pozo[]);
void imprimirfichas2jugadores(SDL_Surface *ficha1[], SDL_Surface *ficha2[], SDL_Surface *ficha3[], SDL_Surface *windowSurface, SDL_Rect dest1[], SDL_Rect dest2[], SDL_Rect dest3[], int jugador1[], int jugador2[], int pozo[]);
void imprimirfondo(SDL_Surface *fondo, SDL_Surface *turnoimagen, SDL_Surface *windowSurface, SDL_Rect destturno, int jugadores, int turno);
void imprimirtablero(SDL_Surface *tablerografico[], SDL_Surface *windowSurface, SDL_Rect desttablero[], int tablero[]);
