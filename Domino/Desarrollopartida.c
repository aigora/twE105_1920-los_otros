#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "Domino.h"

void modomultijugador(int jugadores, int dificultad, int cargar) // el parametro n se refiere al numero de jugadores y m a la dificultad
{
	// estas variables serviran para la programación del desarrollo del juego
	FILE *txt;
	ficha fichas[29];
	int i=1, j, h;
	int aleatorio, igual; // estas dos variables van a servir para el reparto inicial de fichas
	int cargarpartida[203]; //esta variable va a servir para leer los valores del fichero
	int valores[28]={0}; // vector donde voy a almacenar todos los valores de "aleatorio"
	int fichasjugador1[28]={0}; // vector donde voy a almacenar las fichas del jugador 1
	int fichasjugador2[28]={0}; // vector donde voy a almacenar las fichas del jugador 2
	int fichasjugador3[28]={0}; // vector donde voy a almacenar las fichas del jugador 3
	int fichasjugador4[28]={0}; // vector donde voy a almacenar las fichas del jugador 4
	int tablero[55]={0}; // vector donde voy a ir almacenando las fichas ya jugadas
	int pozo[28]={0}; // este vector contrendra las fichas que no se hayan repartido al principio de la partida
	int turno; // esta variable sirve para saber quien empieza a jugar
	int fichagrande; // esta variable sirve para saber cual es la ficha mas alta de las repartidas
	int contadortableroderecha=27;
	int contadortableroizquierda=27;
	int contadorpozo=-1; // esta variable sirve para contar el numero de fichas que hay en el vector "pozo"
	int final=0; // esta variable determinara cuando se termina la partida
	int repeticion=0; // esta variable se usa para que cada jugador solo puede poner 1 pieza por ronda;
	int ganador=0; //esta variable va a determinar quien ha ganado la partida
	int eleccion, posibilidad, eleccionficha, eleccionlado, numerofichas;

	// estas variables van a servir para controlar el jugador local con el ratón
	_Bool running = 1;
    int x, y;
	Uint32 start;

	// estas variables serviran para la programación de la parte gráfica del juego
    SDL_Surface *fondo=NULL;
    SDL_Surface *turnoimagen=NULL;
    SDL_Surface *opcionlocal=NULL;
    SDL_Surface *ficha1[28]={NULL};
    SDL_Surface *ficha2[28]={NULL};
    SDL_Surface *ficha3[28]={NULL};
    SDL_Surface *ficha4[28]={NULL};
    SDL_Surface *tablerografico[55]={NULL};
    SDL_Surface *windowSurface=NULL;
    SDL_Rect destturno;
    SDL_Rect destlocal;
    SDL_Rect dest1[28];
    SDL_Rect dest2[28];
    SDL_Rect dest3[28];
    SDL_Rect dest4[28];
    SDL_Rect desttablero[55];

    // antes de empezar con la partida, voy a iniciar la libreria SDL2
    if(SDL_Init(SDL_INIT_EVERYTHING)<0) // se ejecutará en el caso de que no se halla iniciado correctamente la libreria SDL
    {
        printf("No se pudo iniciar SDL: %s\n",SDL_GetError());
        exit(1);
    }
    SDL_Window *window=SDL_CreateWindow("Domino", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 900, 800, SDL_WINDOW_ALLOW_HIGHDPI);
    windowSurface=SDL_GetWindowSurface(window);
    if(window==NULL) // si no se ha podido crear la ventana emergente
    {
        printf("No pude cargar ventana:", SDL_GetError());
        exit(1);
    }
    SDL_Event windowEvent;

    // EMPEZAMOS CON EL DESARROLLO DE LA PARTIDA
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
		imprimirfondo(fondo, turnoimagen, windowSurface, destturno, jugadores, turno);
		imprimirtablero(tablerografico, windowSurface, desttablero, tablero);
		if(jugadores==2)
            imprimirfichas2jugadores(ficha1, ficha2, ficha3, windowSurface, dest1, dest2, dest3, fichasjugador1, fichasjugador2, pozo);
        if(jugadores==3)
            imprimirfichas3jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, pozo);
        if(jugadores==4)
            imprimirfichas4jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4);
        SDL_UpdateWindowSurface(window);
        Sleep(2000);
		// este bucle sirve para ejecutar el primer turno, el cual se realizara de forma automatica
		// como ya sabemos quien empieza la partida, pone la ficha mas alta en el tablero y se la quita al jugador correspondiente
		for(i=0; i<28; i++)
		{
			if(fichasjugador1[i]==fichagrande)
			{
				tablero[27]=fichagrande; // coloca la ficha en el tablero
				fichasjugador1[i]=0; // le quita la ficha al jugador
			}
			if(fichasjugador2[i]==fichagrande)
			{
				tablero[27]=fichagrande;
				fichasjugador2[i]=0;
			}
			if(fichasjugador3[i]==fichagrande)
			{
				tablero[27]=fichagrande;
				fichasjugador3[i]=0;
			}
			if(fichasjugador4[i]==fichagrande)
			{
				tablero[27]=fichagrande;
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
        introducirfichero(jugadores, dificultad, turno, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, contadortableroderecha, contadortableroizquierda, contadorpozo, final, ganador);
		imprimirfondo(fondo, turnoimagen, windowSurface, destturno, jugadores, turno);
		imprimirtablero(tablerografico, windowSurface, desttablero, tablero);
        if(jugadores==2)
            imprimirfichas2jugadores(ficha1, ficha2, ficha3, windowSurface, dest1, dest2, dest3, fichasjugador1, fichasjugador2, pozo);
        if(jugadores==3)
            imprimirfichas3jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, pozo);
        if(jugadores==4)
            imprimirfichas4jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4);
        SDL_UpdateWindowSurface(window);
        Sleep(2000);
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
		for(i=0; i<203; i++)
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
			if((i>=115)&&(i<=169))
				tablero[i-115]=cargarpartida[i];
			if((i>=170)&&(i<=197))
				pozo[i-170]=cargarpartida[i];
			if(i==198)
				contadortableroderecha=cargarpartida[i];
			if(i==199)
				contadortableroizquierda=cargarpartida[i];
			if(i==200)
				contadorpozo=cargarpartida[i];
			if(i==201)
				final=cargarpartida[i];
			if(i==202)
				ganador=cargarpartida[i];
		}
		imprimirfondo(fondo, turnoimagen, windowSurface, destturno, jugadores, turno);
		imprimirtablero(tablerografico, windowSurface, desttablero, tablero);
        if(jugadores==2)
            imprimirfichas2jugadores(ficha1, ficha2, ficha3, windowSurface, dest1, dest2, dest3, fichasjugador1, fichasjugador2, pozo);
        if(jugadores==3)
            imprimirfichas3jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, pozo);
        if(jugadores==4)
            imprimirfichas4jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4);
        SDL_UpdateWindowSurface(window);
        Sleep(2000);
	}

	do //este bucle contiene el desarrollo de la partida
	{
		do
		{
			switch(turno)
			{
				case 0: // turno del jugador 1
					eleccion=0;
					posibilidad=0;
                    eleccionficha=0;
                    eleccionlado=0;
                    numerofichas=0;
					for(i=0; i<28; i++)
                    {
                        analiza(fichas, fichasjugador1, tablero, &contadortableroderecha, &contadortableroizquierda, &posibilidad, i);
                        if(fichasjugador1[i]!=0)
                            numerofichas+=1;
                    }
                    if(contadorpozo!=-1)
                        opcionlocal=SDL_LoadBMP("Poner-Robar.bmp");
                    if(contadorpozo==-1)
                        opcionlocal=SDL_LoadBMP("Poner-Pasar.bmp");
                    destlocal.x=750;
                    destlocal.y=0;
                    destlocal.w=opcionlocal->w;
                    destlocal.h=opcionlocal->h;
                    SDL_BlitSurface(opcionlocal,NULL,windowSurface,&destlocal);
                    do
                    {
                        running = 1;
                        while(running)
                        {
                            SDL_UpdateWindowSurface(window);
                            start = SDL_GetTicks();
                            while(SDL_PollEvent(&windowEvent))
                            {
                                switch(windowEvent.type)
                                {
                                    case SDL_QUIT:
                                        running = 0;
                                        break;
                                    case SDL_MOUSEBUTTONDOWN:
                                        x = windowEvent.button.x;
                                        y = windowEvent.button.y;
                                        if(x>=760&&x<=890&&y>=243&&y<=290)
                                            eleccion=1;
                                        if(x>=760&&x<=890&&y>=459&&y<=506)
                                            eleccion=2;
                                        running = 0;
                                        break;
                                }
                            }
                        }
                    } while((posibilidad==0&&eleccion==1)||(eleccion==0));
                    posibilidad=0;
                    opcionlocal=SDL_LoadBMP("negro.bmp");
                    SDL_BlitSurface(opcionlocal,NULL,windowSurface,&destlocal);
                    switch(eleccion)
                    {
                        case 1: // en el caso de que se haya escojido poner ficha y se pueda poner
                            running = 1;
                            while(running)
                            {
                                SDL_UpdateWindowSurface(window);
                                start = SDL_GetTicks();
                                while(SDL_PollEvent(&windowEvent))
                                {
                                    switch(windowEvent.type)
                                    {
                                        case SDL_QUIT:
                                            running = 0;
                                            break;
                                        case SDL_MOUSEBUTTONDOWN:
                                            x = windowEvent.button.x;
                                            y = windowEvent.button.y;
                                            for(i=0; i<numerofichas; i++)
                                            {
                                                if(jugadores==4)
                                                {
                                                    if(x>=248+37*i&&x<=281+37*i&&y>=658&&y<=723)
                                                        eleccionficha=i+1;
                                                }
                                                if(jugadores==3)
                                                {
                                                    if(x>=220+36*i&&x<=253+36*i&&y>=658&&y<=723)
                                                        eleccionficha=i+1;
                                                }
                                                if(jugadores==2)
                                                {
                                                    if(x>=167+36*i&&x<=200+36*i&&y>=658&&y<=723)
                                                        eleccionficha=i+1;
                                                }
                                            }
                                            analiza(fichas, fichasjugador1, tablero, &contadortableroderecha, &contadortableroizquierda, &posibilidad, eleccionficha-1);
                                            if(posibilidad==0)
                                                posibilidad=0;
                                            else
                                                running = 0;
                                            break;
                                    }
                                }
                            }
                            if(posibilidad==1)
                                colocarderecha(fichas, fichasjugador1, tablero, &contadortableroderecha, eleccionficha-1);
                            if(posibilidad==2)
                                colocarizquierda(fichas, fichasjugador1, tablero, &contadortableroizquierda, eleccionficha-1);
                            if(posibilidad==3)
                            {
                                opcionlocal=SDL_LoadBMP("Izq-Dcha.bmp");
                                SDL_BlitSurface(opcionlocal,NULL,windowSurface,&destlocal);
                                do
                                {
                                    running = 1;
                                    while(running)
                                    {
                                        SDL_UpdateWindowSurface(window);
                                        start = SDL_GetTicks();
                                        while(SDL_PollEvent(&windowEvent))
                                        {
                                            switch(windowEvent.type)
                                            {
                                                case SDL_QUIT:
                                                    running = 0;
                                                    break;
                                                case SDL_MOUSEBUTTONDOWN:
                                                    x = windowEvent.button.x;
                                                    y = windowEvent.button.y;
                                                    if(x>=760&&x<=890&&y>=243&&y<=290)
                                                        eleccionlado=2;
                                                    if(x>=760&&x<=890&&y>=459&&y<=506)
                                                        eleccionlado=1;
                                                    running = 0;
                                                    break;
                                            }
                                        }
                                    }
                                } while(eleccionlado==0);
                                if(eleccionlado==1)
                                    colocarderecha(fichas, fichasjugador1, tablero, &contadortableroderecha, eleccionficha-1);
                                if(eleccionlado==2)
                                    colocarizquierda(fichas, fichasjugador1, tablero, &contadortableroizquierda, eleccionficha-1);
                            }
                            repeticion=1;
                            final=0;
                            break;
                        case 2:
                            repeticion=0;
                            break;
                    }
                    opcionlocal=SDL_LoadBMP("negro.bmp");
                    SDL_BlitSurface(opcionlocal,NULL,windowSurface,&destlocal);
					if(repeticion==0&&contadorpozo!=-1)
					{
						robarficha(fichasjugador1, pozo, &contadorpozo);
						imprimirfondo(fondo, turnoimagen, windowSurface, destturno, jugadores, turno);
						imprimirtablero(tablerografico, windowSurface, desttablero, tablero);
                        if(jugadores==2)
                            imprimirfichas2jugadores(ficha1, ficha2, ficha3, windowSurface, dest1, dest2, dest3, fichasjugador1, fichasjugador2, pozo);
                        if(jugadores==3)
                            imprimirfichas3jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, pozo);
                        if(jugadores==4)
                            imprimirfichas4jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4);
                        SDL_UpdateWindowSurface(window);
                        Sleep(2000);
					}
					if(repeticion==1)
						ganador=1;
					break;
				case 1: // turno del jugador 2
					desarrollo(fichas, fichasjugador2, tablero, &contadortableroderecha, &contadortableroizquierda, &repeticion, &final, dificultad);
					if(repeticion==0&&contadorpozo!=-1)
					{
						robarficha(fichasjugador2, pozo, &contadorpozo);
						imprimirfondo(fondo, turnoimagen, windowSurface, destturno, jugadores, turno);
						imprimirtablero(tablerografico, windowSurface, desttablero, tablero);
                        if(jugadores==2)
                            imprimirfichas2jugadores(ficha1, ficha2, ficha3, windowSurface, dest1, dest2, dest3, fichasjugador1, fichasjugador2, pozo);
                        if(jugadores==3)
                            imprimirfichas3jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, pozo);
                        if(jugadores==4)
                            imprimirfichas4jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4);
                        SDL_UpdateWindowSurface(window);
                        Sleep(2000);
					}
					if(repeticion==1)
						ganador=2;
					break;
				case 2: // turno del jugador 3
					desarrollo(fichas, fichasjugador3, tablero, &contadortableroderecha, &contadortableroizquierda, &repeticion, &final, dificultad);
					if(repeticion==0&&contadorpozo!=-1)
					{
						robarficha(fichasjugador3, pozo, &contadorpozo);
						imprimirfondo(fondo, turnoimagen, windowSurface, destturno, jugadores, turno);
						imprimirtablero(tablerografico, windowSurface, desttablero, tablero);
                        if(jugadores==2)
                            imprimirfichas2jugadores(ficha1, ficha2, ficha3, windowSurface, dest1, dest2, dest3, fichasjugador1, fichasjugador2, pozo);
                        if(jugadores==3)
                            imprimirfichas3jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, pozo);
                        if(jugadores==4)
                            imprimirfichas4jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4);
                        SDL_UpdateWindowSurface(window);
                        Sleep(2000);
					}
					if(repeticion==1)
						ganador=3;
					break;
				case 3: // turno del jugador 4
					desarrollo(fichas, fichasjugador4, tablero, &contadortableroderecha, &contadortableroizquierda, &repeticion, &final, dificultad);
					if(repeticion==0&&contadorpozo!=-1)
					{
						robarficha(fichasjugador4, pozo, &contadorpozo);
						imprimirfondo(fondo, turnoimagen, windowSurface, destturno, jugadores, turno);
						imprimirtablero(tablerografico, windowSurface, desttablero, tablero);
                        if(jugadores==2)
                            imprimirfichas2jugadores(ficha1, ficha2, ficha3, windowSurface, dest1, dest2, dest3, fichasjugador1, fichasjugador2, pozo);
                        if(jugadores==3)
                            imprimirfichas3jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, pozo);
                        if(jugadores==4)
                            imprimirfichas4jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4);
                        SDL_UpdateWindowSurface(window);
                        Sleep(2000);
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
		introducirfichero(jugadores, dificultad, turno, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4, tablero, pozo, contadortableroderecha, contadortableroizquierda, contadorpozo, final, ganador);
		imprimirfondo(fondo, turnoimagen, windowSurface, destturno, jugadores, turno);
		imprimirtablero(tablerografico, windowSurface, desttablero, tablero);
        if(jugadores==2)
            imprimirfichas2jugadores(ficha1, ficha2, ficha3, windowSurface, dest1, dest2, dest3, fichasjugador1, fichasjugador2, pozo);
        if(jugadores==3)
            imprimirfichas3jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, pozo);
        if(jugadores==4)
            imprimirfichas4jugadores(ficha1, ficha2, ficha3, ficha4, windowSurface, dest1, dest2, dest3, dest4, fichasjugador1, fichasjugador2, fichasjugador3, fichasjugador4);
        SDL_UpdateWindowSurface(window);
        Sleep(2000);
	} while(final<3);
	printf("\n\n\t   ¡¡¡EL JUGADOR %i HA GANADO!!!\n", ganador);
	SDL_FreeSurface(fondo);
	SDL_FreeSurface(turnoimagen);
	SDL_FreeSurface(opcionlocal);
    for(i=0; i<28; i++)
    {
        SDL_FreeSurface(ficha1[i]);
        SDL_FreeSurface(ficha2[i]);
        SDL_FreeSurface(ficha3[i]);
        SDL_FreeSurface(ficha4[i]);
    }
    for(i=0; i<55; i++)
        SDL_FreeSurface(tablerografico[i]);
    SDL_FreeSurface(windowSurface);
    fondo=NULL;
    turnoimagen=NULL;
    opcionlocal=NULL;
    for(i=0; i<28; i++)
    {
        ficha1[i]=NULL;
        ficha2[i]=NULL;
        ficha3[i]=NULL;
        ficha4[i]=NULL;
    }
    for(i=0; i<55; i++)
        tablerografico[i]=NULL;
    windowSurface=NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
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

void siguienteturno(int jugadores, int *turno)
{
	if(jugadores==2)
		*turno=(*turno+1)%2;
	if(jugadores==3)
		*turno=(*turno+1)%3;
	if(jugadores==4)
		*turno=(*turno+1)%4;
}

void analiza(ficha fichas[], int fichasjugador1[], int tablero[], int *contadortableroderecha, int *contadortableroizquierda, int *posibilidad, int i)
{
	if(fichas[fichasjugador1[i]].numero1!=fichas[fichasjugador1[i]].numero2) // si la ficha observada no es doble
    {
        if(tablero[*contadortableroderecha]>0)
        {
            if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortableroderecha]].numero2==fichas[fichasjugador1[i]].numero1))
                *posibilidad+=1;
            if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortableroderecha]].numero2==fichas[fichasjugador1[i]].numero2))
                *posibilidad+=1;
        }
        if(tablero[*contadortableroderecha]<0)
        {
            if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortableroderecha]*(-1)].numero1==fichas[fichasjugador1[i]].numero1))
                *posibilidad+=1;
            if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortableroderecha]*(-1)].numero1==fichas[fichasjugador1[i]].numero2))
                *posibilidad+=1;
        }
        if(tablero[*contadortableroizquierda]>0)
        {
            if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortableroizquierda]].numero1==fichas[fichasjugador1[i]].numero1))
                *posibilidad+=2;
            if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortableroizquierda]].numero1==fichas[fichasjugador1[i]].numero2))
                *posibilidad+=2;
        }
        if(tablero[*contadortableroizquierda]<0)
        {
            if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortableroizquierda]*(-1)].numero2==fichas[fichasjugador1[i]].numero1))
                *posibilidad+=2;
            if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortableroizquierda]*(-1)].numero2==fichas[fichasjugador1[i]].numero2))
                *posibilidad+=2;
        }
    }
    if(fichas[fichasjugador1[i]].numero1==fichas[fichasjugador1[i]].numero2) // si la ficha observada es doble
    {
        if(tablero[*contadortableroderecha]>0)
        {
            if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortableroderecha]].numero2==fichas[fichasjugador1[i]].numero1))
                *posibilidad+=1;
        }
        if(tablero[*contadortableroderecha]<0)
        {
            if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortableroderecha]*(-1)].numero1==fichas[fichasjugador1[i]].numero1))
                *posibilidad+=1;
        }
        if(tablero[*contadortableroizquierda]>0)
        {
            if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortableroizquierda]].numero1==fichas[fichasjugador1[i]].numero1))
                *posibilidad+=2;
        }
        if(tablero[*contadortableroizquierda]<0)
        {
            if((fichasjugador1[i]>0)&&(fichas[tablero[*contadortableroizquierda]*(-1)].numero2==fichas[fichasjugador1[i]].numero1))
                *posibilidad+=2;
        }
    }
}

void colocarderecha(ficha fichas[], int jugador[], int tablero[], int *contadortableroderecha, int eleccionficha)
{
	int j;
	if(tablero[*contadortableroderecha]>0)
	{
		if((jugador[eleccionficha]>0)&&(fichas[tablero[*contadortableroderecha]].numero2==fichas[jugador[eleccionficha]].numero1))
		{
			tablero[*contadortableroderecha+1]=jugador[eleccionficha];
			jugador[eleccionficha]=0;
			*contadortableroderecha+=1;
		}
		if((jugador[eleccionficha]>0)&&(fichas[tablero[*contadortableroderecha]].numero2==fichas[jugador[eleccionficha]].numero2))
		{
			tablero[*contadortableroderecha+1]=jugador[eleccionficha]*(-1);
			jugador[eleccionficha]=0;
			*contadortableroderecha+=1;
		}
	}
	if(tablero[*contadortableroderecha]<0)
	{
		if((jugador[eleccionficha]>0)&&(fichas[tablero[*contadortableroderecha]*(-1)].numero1==fichas[jugador[eleccionficha]].numero1))
		{
			tablero[*contadortableroderecha+1]=jugador[eleccionficha];
			jugador[eleccionficha]=0;
			*contadortableroderecha+=1;
		}
		if((jugador[eleccionficha]>0)&&(fichas[tablero[*contadortableroderecha]*(-1)].numero1==fichas[jugador[eleccionficha]].numero2))
		{
			tablero[*contadortableroderecha+1]=jugador[eleccionficha]*(-1);
			jugador[eleccionficha]=0;
			*contadortableroderecha+=1;
		}
	}
	for(j=0; j<27-eleccionficha;j++)
		jugador[eleccionficha+j]=jugador[eleccionficha+1+j];
}

void colocarizquierda(ficha fichas[], int jugador[], int tablero[], int *contadortableroizquierda, int eleccionficha)
{
	int j;
	if(tablero[*contadortableroizquierda]>0)
	{
		if((jugador[eleccionficha]>0)&&(fichas[tablero[*contadortableroizquierda]].numero1==fichas[jugador[eleccionficha]].numero2))
		{
			tablero[*contadortableroizquierda-1]=jugador[eleccionficha];
			jugador[eleccionficha]=0;
			*contadortableroizquierda-=1;
		}
		if((jugador[eleccionficha]>0)&&(fichas[tablero[*contadortableroizquierda]].numero1==fichas[jugador[eleccionficha]].numero1))
		{
			tablero[*contadortableroizquierda-1]=jugador[eleccionficha]*(-1);
			jugador[eleccionficha]=0;
			*contadortableroizquierda-=1;
		}
	}
	if(tablero[*contadortableroizquierda]<0)
	{
		if((jugador[eleccionficha]>0)&&(fichas[tablero[*contadortableroizquierda]*(-1)].numero2==fichas[jugador[eleccionficha]].numero2))
		{
			tablero[*contadortableroizquierda-1]=jugador[eleccionficha];
			jugador[eleccionficha]=0;
			*contadortableroizquierda-=1;
		}
		if((jugador[eleccionficha]>0)&&(fichas[tablero[*contadortableroizquierda]*(-1)].numero2==fichas[jugador[eleccionficha]].numero1))
		{
			tablero[*contadortableroizquierda-1]=jugador[eleccionficha]*(-1);
			jugador[eleccionficha]=0;
			*contadortableroizquierda-=1;
		}
	}
	for(j=0; j<27-eleccionficha;j++)
		jugador[eleccionficha+j]=jugador[eleccionficha+1+j];
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

void desarrollo(ficha fichas[], int jugador[], int tablero[], int *contadortableroderecha, int *contadortableroizquierda, int *repeticion, int *final, int dificultad)
{
	int i, j;
	ficha jugada;
	if(dificultad==1) // se ejecuta el modo facil
	{
		for(i=0; i<27; i++)
		{
			if((tablero[*contadortableroizquierda]>0)&&(tablero[*contadortableroderecha]>0)) // si los numeros asociados a ambas fichas son positivos...
			{
				if((jugador[i]>0)&&(fichas[tablero[*contadortableroizquierda]].numero1==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					tablero[*contadortableroizquierda-1]=jugador[i];
					jugador[i]=0;
					*contadortableroizquierda-=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortableroderecha]].numero2==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					tablero[*contadortableroderecha+1]=jugador[i];
					jugador[i]=0;
					*contadortableroderecha+=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortableroderecha]].numero2==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					tablero[*contadortableroderecha+1]=jugador[i]*(-1);
					jugador[i]=0;
					*contadortableroderecha+=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortableroizquierda]].numero1==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					tablero[*contadortableroizquierda-1]=jugador[i]*(-1);
					jugador[i]=0;
					*contadortableroizquierda-=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
			}
			if((tablero[*contadortableroizquierda]>0)&&(tablero[*contadortableroderecha]<0)) // en el caso de que el primero sea positivo y el segundo negativo...
			{
				if((jugador[i]>0)&&(fichas[tablero[*contadortableroizquierda]].numero1==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					tablero[*contadortableroizquierda-1]=jugador[i];
					jugador[i]=0;
					*contadortableroizquierda-=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortableroderecha]*(-1)].numero1==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					tablero[*contadortableroderecha+1]=jugador[i];
					jugador[i]=0;
					*contadortableroderecha+=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortableroderecha]*(-1)].numero1==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					tablero[*contadortableroderecha+1]=jugador[i]*(-1);
					jugador[i]=0;
					*contadortableroderecha+=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortableroizquierda]].numero1==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					tablero[*contadortableroizquierda-1]=jugador[i]*(-1);
					jugador[i]=0;
					*contadortableroizquierda-=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
			}
			if((tablero[*contadortableroizquierda]<0)&&(tablero[*contadortableroderecha]>0)) // en el caso de que el primero sea negativo y el segundo positivo...
			{
				if((jugador[i]>0)&&(fichas[tablero[*contadortableroizquierda]*(-1)].numero2==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					tablero[*contadortableroizquierda-1]=jugador[i];
					jugador[i]=0;
					*contadortableroizquierda-=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortableroderecha]].numero2==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					tablero[*contadortableroderecha+1]=jugador[i];
					jugador[i]=0;
					*contadortableroderecha+=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortableroderecha]].numero2==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					tablero[*contadortableroderecha+1]=jugador[i]*(-1);
					jugador[i]=0;
					*contadortableroderecha+=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortableroizquierda]*(-1)].numero2==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					tablero[*contadortableroizquierda-1]=jugador[i]*(-1);
					jugador[i]=0;
					*contadortableroizquierda-=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
			}
			if((tablero[*contadortableroizquierda]<0)&&(tablero[*contadortableroderecha]<0)) // si los numeros asociados a ambas fichas son negativos...
			{
				if((jugador[i]>0)&&(fichas[tablero[*contadortableroizquierda]*(-1)].numero2==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					tablero[*contadortableroizquierda-1]=jugador[i];
					jugador[i]=0;
					*contadortableroizquierda-=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortableroderecha]*(-1)].numero1==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					tablero[*contadortableroderecha+1]=jugador[i];
					jugador[i]=0;
					*contadortableroderecha+=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortableroderecha]*(-1)].numero1==fichas[jugador[i]].numero2)&&(*repeticion==0))
				{
					tablero[*contadortableroderecha+1]=jugador[i]*(-1);
					jugador[i]=0;
					*contadortableroderecha+=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
				else if((jugador[i]>0)&&(fichas[tablero[*contadortableroizquierda]*(-1)].numero2==fichas[jugador[i]].numero1)&&(*repeticion==0))
				{
					tablero[*contadortableroizquierda-1]=jugador[i]*(-1);
					jugador[i]=0;
					*contadortableroizquierda-=1;
					*repeticion=1;
					for(j=0; j<27-i;j++)
						jugador[i+j]=jugador[i+1+j];
				}
			}
		}
	}
	if(dificultad==2) // se ejecuta el modo dificil
	{
		jugada=mododificil(fichas, jugador, tablero, contadortableroderecha, contadortableroizquierda);
		if(jugada.numero2==-1)
			*repeticion=0;
		else
		{
			if(jugada.numero2==1)
				colocarizquierda(fichas, jugador, tablero, contadortableroizquierda, jugada.numero1);
			 else if(jugada.numero2==2)
			 	colocarderecha(fichas, jugador, tablero, contadortableroderecha, jugada.numero1);
			*repeticion=1;
		}
	}
	if(*repeticion==1) // en el caso de poner ficha
		*final=0; // la variable final vale 0
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

ficha mododificil(ficha fichas[], int jugador[], int tablero[], int *contadortableroderecha, int *contadortableroizquierda)
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
		if(tablero[*contadortableroderecha]>0)
		{
			if((jugador[i]>0)&&(fichas[tablero[*contadortableroderecha]].numero2==fichas[jugador[i]].numero1))
				jugabilidad_derecha+=1;
			if((jugador[i]>0)&&(fichas[tablero[*contadortableroderecha]].numero2==fichas[jugador[i]].numero2))
				jugabilidad_derecha+=2;
		}
		if(tablero[*contadortableroderecha]<0)
		{
			if((jugador[i]>0)&&(fichas[tablero[*contadortableroderecha]*(-1)].numero1==fichas[jugador[i]].numero1))
				jugabilidad_derecha+=1;
			if((jugador[i]>0)&&(fichas[tablero[*contadortableroderecha]*(-1)].numero1==fichas[jugador[i]].numero2))
				jugabilidad_derecha+=2;
		}
		if(tablero[*contadortableroizquierda]>0)
		{
			if((jugador[i]>0)&&(fichas[tablero[*contadortableroizquierda]].numero1==fichas[jugador[i]].numero1))
				jugabilidad_izquierda+=1;
			if((jugador[i]>0)&&(fichas[tablero[*contadortableroizquierda]].numero1==fichas[jugador[i]].numero2))
				jugabilidad_izquierda+=2;
		}
		if(tablero[*contadortableroizquierda]<0)
		{
			if((jugador[i]>0)&&(fichas[tablero[*contadortableroizquierda]*(-1)].numero2==fichas[jugador[i]].numero1))
				jugabilidad_izquierda+=1;
			if((jugador[i]>0)&&(fichas[tablero[*contadortableroizquierda]*(-1)].numero2==fichas[jugador[i]].numero2))
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

void introducirfichero(int jugadores, int dificultad, int turno, int fichasjugador1[], int fichasjugador2[], int fichasjugador3[], int fichasjugador4[], int tablero[], int pozo[], int contadortableroderecha, int contadortableroizquierda, int contadorpozo, int final, int ganador)
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
		for(i=0; i<55; i++)
			fprintf(txt, "%i ", tablero[i]);
		fprintf(txt, "\n");
		for(i=0; i<28; i++)
			fprintf(txt, "%i ", pozo[i]);
		fprintf(txt, "\n%i\n", contadortableroderecha);
		fprintf(txt, "%i\n", contadortableroizquierda);
		fprintf(txt, "%i\n", contadorpozo);
		fprintf(txt, "%i\n", final);
		fprintf(txt, "%i\n", ganador);
	}
	fclose(txt);
}
