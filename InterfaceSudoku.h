/*

    Head du fichier InterfaceSudoku.h

*/
#include "Grille.h"


#ifndef INTERFACESUDOKU_H_INCLUDED
#define INTERFACESUDOKU_H_INCLUDED

typedef struct{
    int x;
    int y;
}Coordonees;


void interSudoku(SDL_Surface *ecran, SDL_Surface *imageDeFond, SDL_Rect positionFond);
SDL_Rect cliqueSouris(SDL_Surface *ecran, SDL_Surface *imageDeFond, SDL_Rect positionFond, SDL_Event event,TAB t);
void ecrire(TAB t, SDL_Surface *ecran, SDL_Surface *imageDeFond);
void remplirTEST(TAB t);
Coordonees appuiTouche(SDL_Rect positionFond);
#endif // INTERFACESUDOKU_H_INCLUDED
