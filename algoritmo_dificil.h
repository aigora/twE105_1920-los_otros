
typedef struct
{
	int numero1;
	int numero2;
} ficha;


int buscador_prioridad(int numero,ficha fichas[], int fichasjugador[], int tablero[], int contadortablero);
int comparador(int numero_1, int numero_2,ficha fichas[], int fichasjugador[], int tablero[], int contadortablero);
ficha mododificil(ficha fichas[], int fichasjugador[], int tablero[], int contadortablero);
