#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


#include "Menu.h"

/*void pause() //permet de faire une boucle infini
{
    int continuer = 1;
    SDL_Event event;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT: continuer = 0;
        }
    }
}*/





int main(int argc, char *argv[])
{

    SDL_Surface *ecran = NULL, *imageDeFond = NULL;
    SDL_Rect positionFond;


    positionFond.x = 0;
    positionFond.y = 0;



    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ecran = SDL_SetVideoMode(1366, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN); //d�finit la taille de la fen�tre ainsi que son mode

    menuPrincipal(ecran,imageDeFond,positionFond);

    TTF_Quit();
    SDL_Quit(); //quitte l'interface graphique

    return EXIT_SUCCESS;
}
