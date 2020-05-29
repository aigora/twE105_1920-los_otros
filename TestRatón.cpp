#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argv, char** args)
{
    SDL_Surface *windowSurface=NULL;
    SDL_Event windowEvent;

    if(SDL_Init(SDL_INIT_EVERYTHING)<0) // se ejecutará en el caso de que no se halla iniciado correctamente la libreria SDL
    {
        printf("No se pudo iniciar SDL: %s\n",SDL_GetError());
        exit(1);
    }
    SDL_Window *window=SDL_CreateWindow("Domino", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 750, 750, SDL_WINDOW_ALLOW_HIGHDPI);
    windowSurface=SDL_GetWindowSurface(window);
    if(window==NULL) // si no se ha podido crear la ventana emergente
    {
        printf("No pude cargar ventana:", SDL_GetError());
        exit(1);
    };
    bool running = true;
    int x;
    int y;
    Uint32 start;

    while(running)
    {
        start = SDL_GetTicks();
        while(SDL_PollEvent(&windowEvent))
        {
            switch(windowEvent.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = windowEvent.button.x;
                    y = windowEvent.button.y;
                    printf("x: %i    y: %i\n", x, y);
                    break;
            }
        }
    }
return 0;
}
