#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "Domino.h"

void imprimirfichas4jugadores(SDL_Surface *ficha1[], SDL_Surface *ficha2[], SDL_Surface *ficha3[], SDL_Surface *ficha4[], SDL_Surface *windowSurface, SDL_Rect dest1[], SDL_Rect dest2[], SDL_Rect dest3[], SDL_Rect dest4[], int jugador1[], int jugador2[], int jugador3[], int jugador4[])
{
    int i;
    for(i=0; i<28; i++)
    {
        // jugador 1
        if(jugador1[i]==0)
            ficha1[i]=SDL_LoadBMP("noficha.bmp");
        if(jugador1[i]==1)
            ficha1[i]=SDL_LoadBMP("ficha_01v1.bmp");
        if(jugador1[i]==2)
            ficha1[i]=SDL_LoadBMP("ficha_02v1.bmp");
        if(jugador1[i]==3)
            ficha1[i]=SDL_LoadBMP("ficha_03v1.bmp");
        if(jugador1[i]==4)
            ficha1[i]=SDL_LoadBMP("ficha_04v1.bmp");
        if(jugador1[i]==5)
            ficha1[i]=SDL_LoadBMP("ficha_05v1.bmp");
        if(jugador1[i]==6)
            ficha1[i]=SDL_LoadBMP("ficha_06v1.bmp");
        if(jugador1[i]==7)
            ficha1[i]=SDL_LoadBMP("ficha_12v1.bmp");
        if(jugador1[i]==8)
            ficha1[i]=SDL_LoadBMP("ficha_13v1.bmp");
        if(jugador1[i]==9)
            ficha1[i]=SDL_LoadBMP("ficha_14v1.bmp");
        if(jugador1[i]==10)
            ficha1[i]=SDL_LoadBMP("ficha_15v1.bmp");
        if(jugador1[i]==11)
            ficha1[i]=SDL_LoadBMP("ficha_16v1.bmp");
        if(jugador1[i]==12)
            ficha1[i]=SDL_LoadBMP("ficha_23v1.bmp");
        if(jugador1[i]==13)
            ficha1[i]=SDL_LoadBMP("ficha_24v1.bmp");
        if(jugador1[i]==14)
            ficha1[i]=SDL_LoadBMP("ficha_25v1.bmp");
        if(jugador1[i]==15)
            ficha1[i]=SDL_LoadBMP("ficha_26v1.bmp");
        if(jugador1[i]==16)
            ficha1[i]=SDL_LoadBMP("ficha_34v1.bmp");
        if(jugador1[i]==17)
            ficha1[i]=SDL_LoadBMP("ficha_35v1.bmp");
        if(jugador1[i]==18)
            ficha1[i]=SDL_LoadBMP("ficha_36v1.bmp");
        if(jugador1[i]==19)
            ficha1[i]=SDL_LoadBMP("ficha_45v1.bmp");
        if(jugador1[i]==20)
            ficha1[i]=SDL_LoadBMP("ficha_46v1.bmp");
        if(jugador1[i]==21)
            ficha1[i]=SDL_LoadBMP("ficha_56v1.bmp");
        if(jugador1[i]==22)
            ficha1[i]=SDL_LoadBMP("ficha_00v.bmp");
        if(jugador1[i]==23)
            ficha1[i]=SDL_LoadBMP("ficha_11v.bmp");
        if(jugador1[i]==24)
            ficha1[i]=SDL_LoadBMP("ficha_22v.bmp");
        if(jugador1[i]==25)
            ficha1[i]=SDL_LoadBMP("ficha_33v.bmp");
        if(jugador1[i]==26)
            ficha1[i]=SDL_LoadBMP("ficha_44v.bmp");
        if(jugador1[i]==27)
            ficha1[i]=SDL_LoadBMP("ficha_55v.bmp");
        if(jugador1[i]==28)
            ficha1[i]=SDL_LoadBMP("ficha_66v.bmp");
        dest1[i].x=248+37*i;
        dest1[i].y=658;
        dest1[i].w=ficha1[i]->w;
        dest1[i].h=ficha1[i]->h;
        SDL_BlitSurface(ficha1[i],NULL,windowSurface,&dest1[i]);

        // jugador 2
        if(jugador2[i]==0)
            ficha2[i]=SDL_LoadBMP("noficha.bmp");
        if(jugador2[i]!=0)
            ficha2[i]=SDL_LoadBMP("fichaocultavertical.bmp");
        dest2[i].x=470-37*i;
        dest2[i].y=27;
        dest2[i].w=ficha2[i]->w;
        dest2[i].h=ficha2[i]->h;
        SDL_BlitSurface(ficha2[i],NULL,windowSurface,&dest2[i]);

        // jugador 3
        if(jugador3[i]==0)
            ficha3[i]=SDL_LoadBMP("noficha.bmp");
        if(jugador3[i]!=0)
            ficha3[i]=SDL_LoadBMP("fichaocultahorizontal.bmp");
        dest3[i].x=27;
        dest3[i].y=248+37*i;
        dest3[i].w=ficha3[i]->w;
        dest3[i].h=ficha3[i]->h;
        SDL_BlitSurface(ficha3[i],NULL,windowSurface,&dest3[i]);

        // jugador 4
        if(jugador4[i]==0)
            ficha4[i]=SDL_LoadBMP("noficha.bmp");
        if(jugador4[i]!=0)
            ficha4[i]=SDL_LoadBMP("fichaocultahorizontal.bmp");
        dest4[i].x=658;
        dest4[i].y=470-37*i;
        dest4[i].w=ficha4[i]->w;
        dest4[i].h=ficha4[i]->h;
        SDL_BlitSurface(ficha4[i],NULL,windowSurface,&dest4[i]);
    }
}

void imprimirfichas3jugadores(SDL_Surface *ficha1[], SDL_Surface *ficha2[], SDL_Surface *ficha3[], SDL_Surface *ficha4[], SDL_Surface *windowSurface, SDL_Rect dest1[], SDL_Rect dest2[], SDL_Rect dest3[], SDL_Rect dest4[], int jugador1[], int jugador2[], int jugador3[], int pozo[])
{
    int i;
    for(i=0; i<28; i++)
    {
        // jugador 1
        if(jugador1[i]==0)
            ficha1[i]=SDL_LoadBMP("noficha.bmp");
        if(jugador1[i]==1)
            ficha1[i]=SDL_LoadBMP("ficha_01v1.bmp");
        if(jugador1[i]==2)
            ficha1[i]=SDL_LoadBMP("ficha_02v1.bmp");
        if(jugador1[i]==3)
            ficha1[i]=SDL_LoadBMP("ficha_03v1.bmp");
        if(jugador1[i]==4)
            ficha1[i]=SDL_LoadBMP("ficha_04v1.bmp");
        if(jugador1[i]==5)
            ficha1[i]=SDL_LoadBMP("ficha_05v1.bmp");
        if(jugador1[i]==6)
            ficha1[i]=SDL_LoadBMP("ficha_06v1.bmp");
        if(jugador1[i]==7)
            ficha1[i]=SDL_LoadBMP("ficha_12v1.bmp");
        if(jugador1[i]==8)
            ficha1[i]=SDL_LoadBMP("ficha_13v1.bmp");
        if(jugador1[i]==9)
            ficha1[i]=SDL_LoadBMP("ficha_14v1.bmp");
        if(jugador1[i]==10)
            ficha1[i]=SDL_LoadBMP("ficha_15v1.bmp");
        if(jugador1[i]==11)
            ficha1[i]=SDL_LoadBMP("ficha_16v1.bmp");
        if(jugador1[i]==12)
            ficha1[i]=SDL_LoadBMP("ficha_23v1.bmp");
        if(jugador1[i]==13)
            ficha1[i]=SDL_LoadBMP("ficha_24v1.bmp");
        if(jugador1[i]==14)
            ficha1[i]=SDL_LoadBMP("ficha_25v1.bmp");
        if(jugador1[i]==15)
            ficha1[i]=SDL_LoadBMP("ficha_26v1.bmp");
        if(jugador1[i]==16)
            ficha1[i]=SDL_LoadBMP("ficha_34v1.bmp");
        if(jugador1[i]==17)
            ficha1[i]=SDL_LoadBMP("ficha_35v1.bmp");
        if(jugador1[i]==18)
            ficha1[i]=SDL_LoadBMP("ficha_36v1.bmp");
        if(jugador1[i]==19)
            ficha1[i]=SDL_LoadBMP("ficha_45v1.bmp");
        if(jugador1[i]==20)
            ficha1[i]=SDL_LoadBMP("ficha_46v1.bmp");
        if(jugador1[i]==21)
            ficha1[i]=SDL_LoadBMP("ficha_56v1.bmp");
        if(jugador1[i]==22)
            ficha1[i]=SDL_LoadBMP("ficha_00v.bmp");
        if(jugador1[i]==23)
            ficha1[i]=SDL_LoadBMP("ficha_11v.bmp");
        if(jugador1[i]==24)
            ficha1[i]=SDL_LoadBMP("ficha_22v.bmp");
        if(jugador1[i]==25)
            ficha1[i]=SDL_LoadBMP("ficha_33v.bmp");
        if(jugador1[i]==26)
            ficha1[i]=SDL_LoadBMP("ficha_44v.bmp");
        if(jugador1[i]==27)
            ficha1[i]=SDL_LoadBMP("ficha_55v.bmp");
        if(jugador1[i]==28)
            ficha1[i]=SDL_LoadBMP("ficha_66v.bmp");
        dest1[i].x=220+36*i;
        dest1[i].y=658;
        dest1[i].w=ficha1[i]->w;
        dest1[i].h=ficha1[i]->h;
        SDL_BlitSurface(ficha1[i],NULL,windowSurface,&dest1[i]);

        // jugador 2
        if(jugador2[i]==0)
            ficha2[i]=SDL_LoadBMP("noficha.bmp");
        if(jugador2[i]!=0)
            ficha2[i]=SDL_LoadBMP("fichaocultavertical.bmp");
        dest2[i].x=500-36*i;
        dest2[i].y=27;
        dest2[i].w=ficha2[i]->w;
        dest2[i].h=ficha2[i]->h;
        SDL_BlitSurface(ficha2[i],NULL,windowSurface,&dest2[i]);

        // jugador 3
        if(jugador3[i]==0)
            ficha3[i]=SDL_LoadBMP("noficha.bmp");
        if(jugador3[i]!=0)
            ficha3[i]=SDL_LoadBMP("fichaocultahorizontal.bmp");
        dest3[i].x=27;
        dest3[i].y=220+36*i;
        dest3[i].w=ficha3[i]->w;
        dest3[i].h=ficha3[i]->h;
        SDL_BlitSurface(ficha3[i],NULL,windowSurface,&dest3[i]);

        // pozo
        if(pozo[i]==0)
            ficha4[i]=SDL_LoadBMP("noficha.bmp");
        if(pozo[i]!=0)
            ficha4[i]=SDL_LoadBMP("fichaocultahorizontal.bmp");
        dest4[i].x=658;
        dest4[i].y=248+37*i;
        dest4[i].w=ficha4[i]->w;
        dest4[i].h=ficha4[i]->h;
        SDL_BlitSurface(ficha4[i],NULL,windowSurface,&dest4[i]);
    }
}

void imprimirfichas2jugadores(SDL_Surface *ficha1[], SDL_Surface *ficha2[], SDL_Surface *ficha3[], SDL_Surface *windowSurface, SDL_Rect dest1[], SDL_Rect dest2[], SDL_Rect dest3[], int jugador1[], int jugador2[], int pozo[])
{
    int i;
    for(i=0; i<28; i++)
    {
        // jugador 1
        if(jugador1[i]==0)
            ficha1[i]=SDL_LoadBMP("noficha.bmp");
        if(jugador1[i]==1)
            ficha1[i]=SDL_LoadBMP("ficha_01v1.bmp");
        if(jugador1[i]==2)
            ficha1[i]=SDL_LoadBMP("ficha_02v1.bmp");
        if(jugador1[i]==3)
            ficha1[i]=SDL_LoadBMP("ficha_03v1.bmp");
        if(jugador1[i]==4)
            ficha1[i]=SDL_LoadBMP("ficha_04v1.bmp");
        if(jugador1[i]==5)
            ficha1[i]=SDL_LoadBMP("ficha_05v1.bmp");
        if(jugador1[i]==6)
            ficha1[i]=SDL_LoadBMP("ficha_06v1.bmp");
        if(jugador1[i]==7)
            ficha1[i]=SDL_LoadBMP("ficha_12v1.bmp");
        if(jugador1[i]==8)
            ficha1[i]=SDL_LoadBMP("ficha_13v1.bmp");
        if(jugador1[i]==9)
            ficha1[i]=SDL_LoadBMP("ficha_14v1.bmp");
        if(jugador1[i]==10)
            ficha1[i]=SDL_LoadBMP("ficha_15v1.bmp");
        if(jugador1[i]==11)
            ficha1[i]=SDL_LoadBMP("ficha_16v1.bmp");
        if(jugador1[i]==12)
            ficha1[i]=SDL_LoadBMP("ficha_23v1.bmp");
        if(jugador1[i]==13)
            ficha1[i]=SDL_LoadBMP("ficha_24v1.bmp");
        if(jugador1[i]==14)
            ficha1[i]=SDL_LoadBMP("ficha_25v1.bmp");
        if(jugador1[i]==15)
            ficha1[i]=SDL_LoadBMP("ficha_26v1.bmp");
        if(jugador1[i]==16)
            ficha1[i]=SDL_LoadBMP("ficha_34v1.bmp");
        if(jugador1[i]==17)
            ficha1[i]=SDL_LoadBMP("ficha_35v1.bmp");
        if(jugador1[i]==18)
            ficha1[i]=SDL_LoadBMP("ficha_36v1.bmp");
        if(jugador1[i]==19)
            ficha1[i]=SDL_LoadBMP("ficha_45v1.bmp");
        if(jugador1[i]==20)
            ficha1[i]=SDL_LoadBMP("ficha_46v1.bmp");
        if(jugador1[i]==21)
            ficha1[i]=SDL_LoadBMP("ficha_56v1.bmp");
        if(jugador1[i]==22)
            ficha1[i]=SDL_LoadBMP("ficha_00v.bmp");
        if(jugador1[i]==23)
            ficha1[i]=SDL_LoadBMP("ficha_11v.bmp");
        if(jugador1[i]==24)
            ficha1[i]=SDL_LoadBMP("ficha_22v.bmp");
        if(jugador1[i]==25)
            ficha1[i]=SDL_LoadBMP("ficha_33v.bmp");
        if(jugador1[i]==26)
            ficha1[i]=SDL_LoadBMP("ficha_44v.bmp");
        if(jugador1[i]==27)
            ficha1[i]=SDL_LoadBMP("ficha_55v.bmp");
        if(jugador1[i]==28)
            ficha1[i]=SDL_LoadBMP("ficha_66v.bmp");
        dest1[i].x=167+36*i;
        dest1[i].y=658;
        dest1[i].w=ficha1[i]->w;
        dest1[i].h=ficha1[i]->h;
        SDL_BlitSurface(ficha1[i],NULL,windowSurface,&dest1[i]);

        // jugador 2
        if(jugador2[i]==0)
            ficha2[i]=SDL_LoadBMP("noficha.bmp");
        if(jugador2[i]!=0)
            ficha2[i]=SDL_LoadBMP("fichaocultavertical.bmp");
        dest2[i].x=167+36*i;
        dest2[i].y=27;
        dest2[i].w=ficha2[i]->w;
        dest2[i].h=ficha2[i]->h;
        SDL_BlitSurface(ficha2[i],NULL,windowSurface,&dest2[i]);

        // pozo
        if(pozo[i]==0)
            ficha3[i]=SDL_LoadBMP("noficha.bmp");
        if(pozo[i]!=0)
            ficha3[i]=SDL_LoadBMP("fichaocultahorizontal.bmp");
        dest3[i].x=658;
        dest3[i].y=125+36*i;
        dest3[i].w=ficha3[i]->w;
        dest3[i].h=ficha3[i]->h;
        SDL_BlitSurface(ficha3[i],NULL,windowSurface,&dest3[i]);
    }
}

void imprimirfondo(SDL_Surface *fondo, SDL_Surface *turnoimagen, SDL_Surface *windowSurface, SDL_Rect destturno, int jugadores, int turno)
{
    if(jugadores==2)
        fondo=SDL_LoadBMP("tablero2.bmp"); //carga la imagen del tablero
    if(jugadores==3)
        fondo=SDL_LoadBMP("tablero3.bmp"); //carga la imagen del tablero
    if(jugadores==4)
        fondo=SDL_LoadBMP("tablero4.bmp"); //carga la imagen del tablero
    if(fondo==NULL)
    {
        printf("No pude cargar gr�fico: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_BlitSurface(fondo,NULL,windowSurface,NULL);
    if(turno==0)
        turnoimagen=SDL_LoadBMP("Turno1.bmp"); //carga la imagen del tablero
    if(turno==1)
        turnoimagen=SDL_LoadBMP("Turno2.bmp"); //carga la imagen del tablero
    if(turno==2)
        turnoimagen=SDL_LoadBMP("Turno3.bmp"); //carga la imagen del tablero
    if(turno==3)
        turnoimagen=SDL_LoadBMP("Turno4.bmp"); //carga la imagen del tablero
    destturno.x=0;
    destturno.y=750;
    destturno.w=turnoimagen->w;
    destturno.h=turnoimagen->h;
    SDL_BlitSurface(turnoimagen,NULL,windowSurface,&destturno);
}

void imprimirtablero(SDL_Surface *tablerografico[], SDL_Surface *windowSurface, SDL_Rect desttablero[], int tablero[])
{
    int i;
    for(i=3; i<52; i++)
    {
        if((i>=3&&i<=6)||(i>=24&&i<=26)||(i>=28&&i<=30)||(i>=42&&i<=46)) // voy a escoger las imagenes de las fichas en horizontal
        {
            if(tablero[i]==0)
                tablerografico[i-1]=SDL_LoadBMP("noficha.bmp");
            if(tablero[i]==1)
                tablerografico[i-1]=SDL_LoadBMP("ficha_01h1.bmp");
            if(tablero[i]==-1)
                tablerografico[i-1]=SDL_LoadBMP("ficha_01h2.bmp");
            if(tablero[i]==2)
                tablerografico[i-1]=SDL_LoadBMP("ficha_02h1.bmp");
            if(tablero[i]==-2)
                tablerografico[i-1]=SDL_LoadBMP("ficha_02h2.bmp");
            if(tablero[i]==3)
                tablerografico[i-1]=SDL_LoadBMP("ficha_03h1.bmp");
            if(tablero[i]==-3)
                tablerografico[i-1]=SDL_LoadBMP("ficha_03h2.bmp");
            if(tablero[i]==4)
                tablerografico[i-1]=SDL_LoadBMP("ficha_04h1.bmp");
            if(tablero[i]==-4)
                tablerografico[i-1]=SDL_LoadBMP("ficha_04h2.bmp");
            if(tablero[i]==5)
                tablerografico[i-1]=SDL_LoadBMP("ficha_05h1.bmp");
            if(tablero[i]==-5)
                tablerografico[i-1]=SDL_LoadBMP("ficha_05h2.bmp");
            if(tablero[i]==6)
                tablerografico[i-1]=SDL_LoadBMP("ficha_06h1.bmp");
            if(tablero[i]==-6)
                tablerografico[i-1]=SDL_LoadBMP("ficha_06h2.bmp");
            if(tablero[i]==7)
                tablerografico[i-1]=SDL_LoadBMP("ficha_12h1.bmp");
            if(tablero[i]==-7)
                tablerografico[i-1]=SDL_LoadBMP("ficha_12h2.bmp");
            if(tablero[i]==8)
                tablerografico[i-1]=SDL_LoadBMP("ficha_13h1.bmp");
            if(tablero[i]==-8)
                tablerografico[i-1]=SDL_LoadBMP("ficha_13h2.bmp");
            if(tablero[i]==9)
                tablerografico[i-1]=SDL_LoadBMP("ficha_14h1.bmp");
            if(tablero[i]==-9)
                tablerografico[i-1]=SDL_LoadBMP("ficha_14h2.bmp");
            if(tablero[i]==10)
                tablerografico[i-1]=SDL_LoadBMP("ficha_15h1.bmp");
            if(tablero[i]==-10)
                tablerografico[i-1]=SDL_LoadBMP("ficha_15h2.bmp");
            if(tablero[i]==11)
                tablerografico[i-1]=SDL_LoadBMP("ficha_16h1.bmp");
            if(tablero[i]==-11)
                tablerografico[i-1]=SDL_LoadBMP("ficha_16h2.bmp");
            if(tablero[i]==12)
                tablerografico[i-1]=SDL_LoadBMP("ficha_23h1.bmp");
            if(tablero[i]==-12)
                tablerografico[i-1]=SDL_LoadBMP("ficha_23h2.bmp");
            if(tablero[i]==13)
                tablerografico[i-1]=SDL_LoadBMP("ficha_24h1.bmp");
            if(tablero[i]==-13)
                tablerografico[i-1]=SDL_LoadBMP("ficha_24h2.bmp");
            if(tablero[i]==14)
                tablerografico[i-1]=SDL_LoadBMP("ficha_25h1.bmp");
            if(tablero[i]==-14)
                tablerografico[i-1]=SDL_LoadBMP("ficha_25h2.bmp");
            if(tablero[i]==15)
                tablerografico[i-1]=SDL_LoadBMP("ficha_26h1.bmp");
            if(tablero[i]==-15)
                tablerografico[i-1]=SDL_LoadBMP("ficha_26h2.bmp");
            if(tablero[i]==16)
                tablerografico[i-1]=SDL_LoadBMP("ficha_34h1.bmp");
            if(tablero[i]==-16)
                tablerografico[i-1]=SDL_LoadBMP("ficha_34h2.bmp");
            if(tablero[i]==17)
                tablerografico[i-1]=SDL_LoadBMP("ficha_35h1.bmp");
            if(tablero[i]==-17)
                tablerografico[i-1]=SDL_LoadBMP("ficha_35h2.bmp");
            if(tablero[i]==18)
                tablerografico[i-1]=SDL_LoadBMP("ficha_36h1.bmp");
            if(tablero[i]==-18)
                tablerografico[i-1]=SDL_LoadBMP("ficha_36h2.bmp");
            if(tablero[i]==19)
                tablerografico[i-1]=SDL_LoadBMP("ficha_45h1.bmp");
            if(tablero[i]==-19)
                tablerografico[i-1]=SDL_LoadBMP("ficha_45h2.bmp");
            if(tablero[i]==20)
                tablerografico[i-1]=SDL_LoadBMP("ficha_46h1.bmp");
            if(tablero[i]==-20)
                tablerografico[i-1]=SDL_LoadBMP("ficha_46h2.bmp");
            if(tablero[i]==21)
                tablerografico[i-1]=SDL_LoadBMP("ficha_56h1.bmp");
            if(tablero[i]==-21)
                tablerografico[i-1]=SDL_LoadBMP("ficha_56h2.bmp");
            if((tablero[i]==22)||(tablero[i]==-22)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_00h.bmp");
            if((tablero[i]==23)||(tablero[i]==-23)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_11h.bmp");
            if((tablero[i]==24)||(tablero[i]==-24)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_22h.bmp");
            if((tablero[i]==25)||(tablero[i]==-25)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_33h.bmp");
            if((tablero[i]==26)||(tablero[i]==-26)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_44h.bmp");
            if((tablero[i]==27)||(tablero[i]==-27)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_55h.bmp");
            if((tablero[i]==28)||(tablero[i]==-28)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_66h.bmp");
        }
        if((i>=8&&i<=12)||(i>=15&&i<=20)||(i>=34&&i<=39)||(i>=48&&i<=51))
        {
            if(tablero[i]==0)
                tablerografico[i-1]=SDL_LoadBMP("noficha.bmp");
            if(tablero[i]==1)
                tablerografico[i-1]=SDL_LoadBMP("ficha_01h2.bmp");
            if(tablero[i]==-1)
                tablerografico[i-1]=SDL_LoadBMP("ficha_01h1.bmp");
            if(tablero[i]==2)
                tablerografico[i-1]=SDL_LoadBMP("ficha_02h2.bmp");
            if(tablero[i]==-2)
                tablerografico[i-1]=SDL_LoadBMP("ficha_02h1.bmp");
            if(tablero[i]==3)
                tablerografico[i-1]=SDL_LoadBMP("ficha_03h2.bmp");
            if(tablero[i]==-3)
                tablerografico[i-1]=SDL_LoadBMP("ficha_03h1.bmp");
            if(tablero[i]==4)
                tablerografico[i-1]=SDL_LoadBMP("ficha_04h2.bmp");
            if(tablero[i]==-4)
                tablerografico[i-1]=SDL_LoadBMP("ficha_04h1.bmp");
            if(tablero[i]==5)
                tablerografico[i-1]=SDL_LoadBMP("ficha_05h2.bmp");
            if(tablero[i]==-5)
                tablerografico[i-1]=SDL_LoadBMP("ficha_05h1.bmp");
            if(tablero[i]==6)
                tablerografico[i-1]=SDL_LoadBMP("ficha_06h2.bmp");
            if(tablero[i]==-6)
                tablerografico[i-1]=SDL_LoadBMP("ficha_06h1.bmp");
            if(tablero[i]==7)
                tablerografico[i-1]=SDL_LoadBMP("ficha_12h2.bmp");
            if(tablero[i]==-7)
                tablerografico[i-1]=SDL_LoadBMP("ficha_12h1.bmp");
            if(tablero[i]==8)
                tablerografico[i-1]=SDL_LoadBMP("ficha_13h2.bmp");
            if(tablero[i]==-8)
                tablerografico[i-1]=SDL_LoadBMP("ficha_13h1.bmp");
            if(tablero[i]==9)
                tablerografico[i-1]=SDL_LoadBMP("ficha_14h2.bmp");
            if(tablero[i]==-9)
                tablerografico[i-1]=SDL_LoadBMP("ficha_14h1.bmp");
            if(tablero[i]==10)
                tablerografico[i-1]=SDL_LoadBMP("ficha_15h2.bmp");
            if(tablero[i]==-10)
                tablerografico[i-1]=SDL_LoadBMP("ficha_15h1.bmp");
            if(tablero[i]==11)
                tablerografico[i-1]=SDL_LoadBMP("ficha_16h2.bmp");
            if(tablero[i]==-11)
                tablerografico[i-1]=SDL_LoadBMP("ficha_16h1.bmp");
            if(tablero[i]==12)
                tablerografico[i-1]=SDL_LoadBMP("ficha_23h2.bmp");
            if(tablero[i]==-12)
                tablerografico[i-1]=SDL_LoadBMP("ficha_23h1.bmp");
            if(tablero[i]==13)
                tablerografico[i-1]=SDL_LoadBMP("ficha_24h2.bmp");
            if(tablero[i]==-13)
                tablerografico[i-1]=SDL_LoadBMP("ficha_24h1.bmp");
            if(tablero[i]==14)
                tablerografico[i-1]=SDL_LoadBMP("ficha_25h2.bmp");
            if(tablero[i]==-14)
                tablerografico[i-1]=SDL_LoadBMP("ficha_25h1.bmp");
            if(tablero[i]==15)
                tablerografico[i-1]=SDL_LoadBMP("ficha_26h2.bmp");
            if(tablero[i]==-15)
                tablerografico[i-1]=SDL_LoadBMP("ficha_26h1.bmp");
            if(tablero[i]==16)
                tablerografico[i-1]=SDL_LoadBMP("ficha_34h2.bmp");
            if(tablero[i]==-16)
                tablerografico[i-1]=SDL_LoadBMP("ficha_34h1.bmp");
            if(tablero[i]==17)
                tablerografico[i-1]=SDL_LoadBMP("ficha_35h2.bmp");
            if(tablero[i]==-17)
                tablerografico[i-1]=SDL_LoadBMP("ficha_35h1.bmp");
            if(tablero[i]==18)
                tablerografico[i-1]=SDL_LoadBMP("ficha_36h2.bmp");
            if(tablero[i]==-18)
                tablerografico[i-1]=SDL_LoadBMP("ficha_36h1.bmp");
            if(tablero[i]==19)
                tablerografico[i-1]=SDL_LoadBMP("ficha_45h2.bmp");
            if(tablero[i]==-19)
                tablerografico[i-1]=SDL_LoadBMP("ficha_45h1.bmp");
            if(tablero[i]==20)
                tablerografico[i-1]=SDL_LoadBMP("ficha_46h2.bmp");
            if(tablero[i]==-20)
                tablerografico[i-1]=SDL_LoadBMP("ficha_46h1.bmp");
            if(tablero[i]==21)
                tablerografico[i-1]=SDL_LoadBMP("ficha_56h2.bmp");
            if(tablero[i]==-21)
                tablerografico[i-1]=SDL_LoadBMP("ficha_56h1.bmp");
            if((tablero[i]==22)||(tablero[i]==-22)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_00h.bmp");
            if((tablero[i]==23)||(tablero[i]==-23)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_11h.bmp");
            if((tablero[i]==24)||(tablero[i]==-24)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_22h.bmp");
            if((tablero[i]==25)||(tablero[i]==-25)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_33h.bmp");
            if((tablero[i]==26)||(tablero[i]==-26)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_44h.bmp");
            if((tablero[i]==27)||(tablero[i]==-27)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_55h.bmp");
            if((tablero[i]==28)||(tablero[i]==-28)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_66h.bmp");
        }
        if((i>=21&&i<=23)||(i>=31&&i<=33)||(i==47))
        {
            if(tablero[i]==0)
                tablerografico[i-1]=SDL_LoadBMP("noficha.bmp");
            if(tablero[i]==1)
                tablerografico[i-1]=SDL_LoadBMP("ficha_01v1.bmp");
            if(tablero[i]==-1)
                tablerografico[i-1]=SDL_LoadBMP("ficha_01v2.bmp");
            if(tablero[i]==2)
                tablerografico[i-1]=SDL_LoadBMP("ficha_02v1.bmp");
            if(tablero[i]==-2)
                tablerografico[i-1]=SDL_LoadBMP("ficha_02v2.bmp");
            if(tablero[i]==3)
                tablerografico[i-1]=SDL_LoadBMP("ficha_03v1.bmp");
            if(tablero[i]==-3)
                tablerografico[i-1]=SDL_LoadBMP("ficha_03v2.bmp");
            if(tablero[i]==4)
                tablerografico[i-1]=SDL_LoadBMP("ficha_04v1.bmp");
            if(tablero[i]==-4)
                tablerografico[i-1]=SDL_LoadBMP("ficha_04v2.bmp");
            if(tablero[i]==5)
                tablerografico[i-1]=SDL_LoadBMP("ficha_05v1.bmp");
            if(tablero[i]==-5)
                tablerografico[i-1]=SDL_LoadBMP("ficha_05v2.bmp");
            if(tablero[i]==6)
                tablerografico[i-1]=SDL_LoadBMP("ficha_06v1.bmp");
            if(tablero[i]==-6)
                tablerografico[i-1]=SDL_LoadBMP("ficha_06v2.bmp");
            if(tablero[i]==7)
                tablerografico[i-1]=SDL_LoadBMP("ficha_12v1.bmp");
            if(tablero[i]==-7)
                tablerografico[i-1]=SDL_LoadBMP("ficha_12v2.bmp");
            if(tablero[i]==8)
                tablerografico[i-1]=SDL_LoadBMP("ficha_13v1.bmp");
            if(tablero[i]==-8)
                tablerografico[i-1]=SDL_LoadBMP("ficha_13v2.bmp");
            if(tablero[i]==9)
                tablerografico[i-1]=SDL_LoadBMP("ficha_14v1.bmp");
            if(tablero[i]==-9)
                tablerografico[i-1]=SDL_LoadBMP("ficha_14v2.bmp");
            if(tablero[i]==10)
                tablerografico[i-1]=SDL_LoadBMP("ficha_15v1.bmp");
            if(tablero[i]==-10)
                tablerografico[i-1]=SDL_LoadBMP("ficha_15v2.bmp");
            if(tablero[i]==11)
                tablerografico[i-1]=SDL_LoadBMP("ficha_16v1.bmp");
            if(tablero[i]==-11)
                tablerografico[i-1]=SDL_LoadBMP("ficha_16v2.bmp");
            if(tablero[i]==12)
                tablerografico[i-1]=SDL_LoadBMP("ficha_23v1.bmp");
            if(tablero[i]==-12)
                tablerografico[i-1]=SDL_LoadBMP("ficha_23v2.bmp");
            if(tablero[i]==13)
                tablerografico[i-1]=SDL_LoadBMP("ficha_24v1.bmp");
            if(tablero[i]==-13)
                tablerografico[i-1]=SDL_LoadBMP("ficha_24v2.bmp");
            if(tablero[i]==14)
                tablerografico[i-1]=SDL_LoadBMP("ficha_25v1.bmp");
            if(tablero[i]==-14)
                tablerografico[i-1]=SDL_LoadBMP("ficha_25v2.bmp");
            if(tablero[i]==15)
                tablerografico[i-1]=SDL_LoadBMP("ficha_26v1.bmp");
            if(tablero[i]==-15)
                tablerografico[i-1]=SDL_LoadBMP("ficha_26v2.bmp");
            if(tablero[i]==16)
                tablerografico[i-1]=SDL_LoadBMP("ficha_34v1.bmp");
            if(tablero[i]==-16)
                tablerografico[i-1]=SDL_LoadBMP("ficha_34v2.bmp");
            if(tablero[i]==17)
                tablerografico[i-1]=SDL_LoadBMP("ficha_35v1.bmp");
            if(tablero[i]==-17)
                tablerografico[i-1]=SDL_LoadBMP("ficha_35v2.bmp");
            if(tablero[i]==18)
                tablerografico[i-1]=SDL_LoadBMP("ficha_36v1.bmp");
            if(tablero[i]==-18)
                tablerografico[i-1]=SDL_LoadBMP("ficha_36v2.bmp");
            if(tablero[i]==19)
                tablerografico[i-1]=SDL_LoadBMP("ficha_45v1.bmp");
            if(tablero[i]==-19)
                tablerografico[i-1]=SDL_LoadBMP("ficha_45v2.bmp");
            if(tablero[i]==20)
                tablerografico[i-1]=SDL_LoadBMP("ficha_46v1.bmp");
            if(tablero[i]==-20)
                tablerografico[i-1]=SDL_LoadBMP("ficha_46v2.bmp");
            if(tablero[i]==21)
                tablerografico[i-1]=SDL_LoadBMP("ficha_56v1.bmp");
            if(tablero[i]==-21)
                tablerografico[i-1]=SDL_LoadBMP("ficha_56v2.bmp");
            if((tablero[i]==22)||(tablero[i]==-22)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_00v.bmp");
            if((tablero[i]==23)||(tablero[i]==-23)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_11v.bmp");
            if((tablero[i]==24)||(tablero[i]==-24)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_22v.bmp");
            if((tablero[i]==25)||(tablero[i]==-25)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_33v.bmp");
            if((tablero[i]==26)||(tablero[i]==-26)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_44v.bmp");
            if((tablero[i]==27)||(tablero[i]==-27)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_55v.bmp");
            if((tablero[i]==28)||(tablero[i]==-28)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_66v.bmp");
        }
        if((i==7)||(i>=13&&i<=14)||(i==27)||(i>=40&&i<=41))
        {
            if(tablero[i]==0)
                tablerografico[i-1]=SDL_LoadBMP("noficha.bmp");
            if(tablero[i]==1)
                tablerografico[i-1]=SDL_LoadBMP("ficha_01v2.bmp");
            if(tablero[i]==-1)
                tablerografico[i-1]=SDL_LoadBMP("ficha_01v1.bmp");
            if(tablero[i]==2)
                tablerografico[i-1]=SDL_LoadBMP("ficha_02v2.bmp");
            if(tablero[i]==-2)
                tablerografico[i-1]=SDL_LoadBMP("ficha_02v1.bmp");
            if(tablero[i]==3)
                tablerografico[i-1]=SDL_LoadBMP("ficha_03v2.bmp");
            if(tablero[i]==-3)
                tablerografico[i-1]=SDL_LoadBMP("ficha_03v1.bmp");
            if(tablero[i]==4)
                tablerografico[i-1]=SDL_LoadBMP("ficha_04v2.bmp");
            if(tablero[i]==-4)
                tablerografico[i-1]=SDL_LoadBMP("ficha_04v1.bmp");
            if(tablero[i]==5)
                tablerografico[i-1]=SDL_LoadBMP("ficha_05v2.bmp");
            if(tablero[i]==-5)
                tablerografico[i-1]=SDL_LoadBMP("ficha_05v1.bmp");
            if(tablero[i]==6)
                tablerografico[i-1]=SDL_LoadBMP("ficha_06v2.bmp");
            if(tablero[i]==-6)
                tablerografico[i-1]=SDL_LoadBMP("ficha_06v1.bmp");
            if(tablero[i]==7)
                tablerografico[i-1]=SDL_LoadBMP("ficha_12v2.bmp");
            if(tablero[i]==-7)
                tablerografico[i-1]=SDL_LoadBMP("ficha_12v1.bmp");
            if(tablero[i]==8)
                tablerografico[i-1]=SDL_LoadBMP("ficha_13v2.bmp");
            if(tablero[i]==-8)
                tablerografico[i-1]=SDL_LoadBMP("ficha_13v1.bmp");
            if(tablero[i]==9)
                tablerografico[i-1]=SDL_LoadBMP("ficha_14v2.bmp");
            if(tablero[i]==-9)
                tablerografico[i-1]=SDL_LoadBMP("ficha_14v1.bmp");
            if(tablero[i]==10)
                tablerografico[i-1]=SDL_LoadBMP("ficha_15v2.bmp");
            if(tablero[i]==-10)
                tablerografico[i-1]=SDL_LoadBMP("ficha_15v1.bmp");
            if(tablero[i]==11)
                tablerografico[i-1]=SDL_LoadBMP("ficha_16v2.bmp");
            if(tablero[i]==-11)
                tablerografico[i-1]=SDL_LoadBMP("ficha_16v1.bmp");
            if(tablero[i]==12)
                tablerografico[i-1]=SDL_LoadBMP("ficha_23v2.bmp");
            if(tablero[i]==-12)
                tablerografico[i-1]=SDL_LoadBMP("ficha_23v1.bmp");
            if(tablero[i]==13)
                tablerografico[i-1]=SDL_LoadBMP("ficha_24v2.bmp");
            if(tablero[i]==-13)
                tablerografico[i-1]=SDL_LoadBMP("ficha_24v1.bmp");
            if(tablero[i]==14)
                tablerografico[i-1]=SDL_LoadBMP("ficha_25v2.bmp");
            if(tablero[i]==-14)
                tablerografico[i-1]=SDL_LoadBMP("ficha_25v1.bmp");
            if(tablero[i]==15)
                tablerografico[i-1]=SDL_LoadBMP("ficha_26v2.bmp");
            if(tablero[i]==-15)
                tablerografico[i-1]=SDL_LoadBMP("ficha_26v1.bmp");
            if(tablero[i]==16)
                tablerografico[i-1]=SDL_LoadBMP("ficha_34v2.bmp");
            if(tablero[i]==-16)
                tablerografico[i-1]=SDL_LoadBMP("ficha_34v1.bmp");
            if(tablero[i]==17)
                tablerografico[i-1]=SDL_LoadBMP("ficha_35v2.bmp");
            if(tablero[i]==-17)
                tablerografico[i-1]=SDL_LoadBMP("ficha_35v1.bmp");
            if(tablero[i]==18)
                tablerografico[i-1]=SDL_LoadBMP("ficha_36v2.bmp");
            if(tablero[i]==-18)
                tablerografico[i-1]=SDL_LoadBMP("ficha_36v1.bmp");
            if(tablero[i]==19)
                tablerografico[i-1]=SDL_LoadBMP("ficha_45v2.bmp");
            if(tablero[i]==-19)
                tablerografico[i-1]=SDL_LoadBMP("ficha_45v1.bmp");
            if(tablero[i]==20)
                tablerografico[i-1]=SDL_LoadBMP("ficha_46v2.bmp");
            if(tablero[i]==-20)
                tablerografico[i-1]=SDL_LoadBMP("ficha_46v1.bmp");
            if(tablero[i]==21)
                tablerografico[i-1]=SDL_LoadBMP("ficha_56v2.bmp");
            if(tablero[i]==-21)
                tablerografico[i-1]=SDL_LoadBMP("ficha_56v1.bmp");
            if((tablero[i]==22)||(tablero[i-1]==-22)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_00v.bmp");
            if((tablero[i]==23)||(tablero[i-1]==-23)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_11v.bmp");
            if((tablero[i]==24)||(tablero[i-1]==-24)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_22v.bmp");
            if((tablero[i]==25)||(tablero[i-1]==-25)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_33v.bmp");
            if((tablero[i]==26)||(tablero[i-1]==-26)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_44v.bmp");
            if((tablero[i]==27)||(tablero[i-1]==-27)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_55v.bmp");
            if((tablero[i]==28)||(tablero[i-1]==-28)) // las fichas dobles da igual en que posicion esten
                tablerografico[i-1]=SDL_LoadBMP("ficha_66v.bmp");
        }
        // ahora voy a determinar la posicion de cada ficha del tablero en la imagen
        if(i>=3&&i<=6)
        {
            desttablero[i-1].x=457-65*(i-3);
            desttablero[i-1].y=229;
        }
        if(i==7)
        {
            desttablero[i-1].x=229;
            desttablero[i-1].y=229;
        }
        if(i>=8&&i<=12)
        {
            desttablero[i-1].x=229+65*(i-8);
            desttablero[i-1].y=294;
        }
        if(i>=13&&i<=14)
        {
            desttablero[i-1].x=554;
            desttablero[i-1].y=262-65*(i-13);
        }
        if(i>=15&&i<=20)
        {
            desttablero[i-1].x=522-65*(i-15);
            desttablero[i-1].y=164;
        }
        if(i>=21&&i<=23)
        {
            desttablero[i-1].x=164;
            desttablero[i-1].y=164+65*(i-21);
        }
        if(i>=24&&i<=26)
        {
            desttablero[i-1].x=164+65*(i-24);
            desttablero[i-1].y=359;
        }
        if(i==27)
        {
            desttablero[i-1].x=358;
            desttablero[i-1].y=342;
        }
        if(i>=28&&i<=30)
        {
            desttablero[i-1].x=392+65*(i-28);
            desttablero[i-1].y=359;
        }
        if(i>=31&&i<=33)
        {
            desttablero[i-1].x=554;
            desttablero[i-1].y=392+65*(i-31);
        }
        if(i>=34&&i<=39)
        {
            desttablero[i-1].x=489-65*(i-34);
            desttablero[i-1].y=554;
        }
        if(i>=40&&i<=41)
        {
            desttablero[i-1].x=164;
            desttablero[i-1].y=489-65*(i-40);
        }
        if(i>=42&&i<=46)
        {
            desttablero[i-1].x=197+65*(i-42);
            desttablero[i-1].y=424;
        }
        if(i>=47)
        {
            desttablero[i-1].x=489;
            desttablero[i-1].y=457;
        }
        if(i>=48&&i<=51)
        {
            desttablero[i-1].x=424-65*(i-48);
            desttablero[i-1].y=489;
        }
        desttablero[i-1].w=tablerografico[i-1]->w;
        desttablero[i-1].h=tablerografico[i-1]->h;
        SDL_BlitSurface(tablerografico[i-1],NULL,windowSurface,&desttablero[i-1]);
    }
}
