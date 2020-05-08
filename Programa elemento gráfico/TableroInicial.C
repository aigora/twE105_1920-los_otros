#include <stdio.h>
#include <graphics.h>
#include <conio.h>

main()
{
	int gd = DETECT, gm;
	int i, jugadores;
	scanf("%i", &jugadores);
	
	// LO PRIMERO QUE VOY A HACER ES CARGAR LA TARJETA GRÁFICA
	initgraph(&gd, &gm, "C:\\TC\\BGI"); // cargo el dispositivo grafico del ordenador
	setbkcolor(BLACK); // este comando sirve para elegir el color del fondo
	cleardevice(); // borro todo lo que haya en la pantalla y muestro el fondo de negro
	
	// AHORA VOY A CREAR EL TABLERO
	// LAS DOS PRIMERAS LÍNEAS SIRVEN PARA EL "RECTANGULO" DE JUEGO Y LAS 3 SIGUIENTES PARA EL TITULO
	setfillstyle(SOLID_FILL, GREEN); // selecciono un color de relleno
	bar(160, 60, 1000, 600); // creo un rectángulo sin bordes y lo relleno del color elegido anteriormente
	setcolor(YELLOW); // selecciono el color del texto
	settextstyle(3, HORIZ_DIR, 3); // selecciono el formato del texto, el primer número corresponde a la fuente (tipo de letra) y el último al factor de aumento
	outtextxy(500, 20, "Tablero de juego"); // muestro el texto por pantalla, mostrandolo en las coordenadas x e y definidas
	
	// TRAS CREAR EL TABLERO, VOY A HABILITAR UNA ZONA PARA LAS FICHAS DEL POZO
	setcolor(RED); // selecciono el color del texto
	settextstyle(4, HORIZ_DIR, 1); // selecciono el formato del texto
	outtextxy(1100, 425, "Fichas de reserva"); // muestro el texto por pantalla, mostrandolo en las coordenadas x e y definidas
	setcolor(RED); // selecciono el color del rectángulo
	rectangle(1080, 450, 1350, 600); // los dos primeros argumentos corresponden a la esquina superior izquierda y los dos últimos a la esquina inferior derecha
	
	// ES EL TURNO DE MOSTRAR LAS FICHAS DE LOS JUGADORES
	// LO PRIMERO QUE VOY A HACER ES CREAR UN "LOGO" PARA EL JUGADOR 1
	// esta parte sirve para el circulo exterior
	setcolor(CYAN);
	setlinestyle(1, DASHED_LINE, 3); // el primer número corresponde al estilo de linea y el ultimo al grosor
	circle(300, 530, 60); // los dos primeros argumentos son las coordenas x e y del centro y el último al radio
	// esta parte sirve para dibujar el "cuerpo"
	setcolor(BLUE);
	setlinestyle(1, SOLID_LINE, 2);
	circle(300, 510, 20);
	arc(300, 555, 0, 180, 25); // los dos primeros números son las coordenadas x e y del centro, los dos siguientes el angulo incial y final y el ultimo el radio
	line(275, 555, 325, 555); // los dos primeros numeros son las coordenadas del punto inicial y los dos ultimos las del punto final
	
  	for(i=0; i<jugadores; i++) // mostrare tantos jugadores como haya en la partida
  	{
	  	if(i==0) // muestro al jugador 1
	  	{
	  		setcolor(BLUE);
	    	settextstyle(6, HORIZ_DIR, 1);
	        outtextxy(235, 565, "PLAYER 1");
		}
		if(i==1) // muestro al jugador 2
	  	{
	  		setcolor(WHITE);
			settextstyle(4, HORIZ_DIR, 1);
			outtextxy(1100, 125, "PLAYER 2:");
		}
		if(i==2) // muestro al jugador 3
	  	{
	  		setcolor(LIGHTMAGENTA);
	    	settextstyle(4, HORIZ_DIR, 1);
	    	outtextxy(1100, 225, "PLAYER 3:");
		}
		if(i==3) // muestro al jugador 4
	  	{
	  		setcolor(LIGHTGREEN);
	  		settextstyle(4, HORIZ_DIR, 1);
	  		outtextxy(1100, 325, "PLAYER 4:");
		}
	}
	
  	getch();
  	closegraph(); // cierro la tarjeta grafica
}
