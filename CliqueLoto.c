#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <time.h>

#include "InterfaceLoto.h"
#include "loto.h"
#include "tiragee.h"


/**Choix du nombre de grille*/
SDL_Rect cliqueSourisLoto1(Tableau pseudo, SDL_Surface *ecran, SDL_Surface *imageDeFond, SDL_Rect positionFond, SDL_Event event, TAB t){

    if(event.button.x>1143 && event.button.x<1294 && event.button.y>670 && event.button.y<705)
    {
        positionFond.x = -1;
        positionFond.y = -1;
        return positionFond;
    }
    if(event.button.x>389 && event.button.x<406 && event.button.y>217 && event.button.y<255){
        positionFond = cliqueSourisLoto2(pseudo,ecran,imageDeFond,positionFond,t,1);
    }
    if(event.button.x>684 && event.button.x<705 && event.button.y>218 && event.button.y<250){
        positionFond = cliqueSourisLoto2(pseudo,ecran,imageDeFond,positionFond,t,2);
    }
    if(event.button.x>944 && event.button.x<967 && event.button.y>214 && event.button.y<249){
        positionFond = cliqueSourisLoto2(pseudo,ecran,imageDeFond,positionFond,t,3);
    }
    return positionFond;
}

/**Fonction qui s'occupe du jeu du loto*/
SDL_Rect cliqueSourisLoto2(Tableau pseudo, SDL_Surface *ecran, SDL_Surface *imageDeFond, SDL_Rect positionFond, TAB t, int choix){
    positionFond.x = 0;
    positionFond.y = 0;
    imageDeFond = SDL_LoadBMP("loto/bingo2.bmp");
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    SDL_Flip(ecran);
    positionFond.x = 400;
    positionFond.y = 50;
    imageDeFond = SDL_LoadBMP("loto/grille.bmp");
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    SDL_Flip(ecran);
    if(choix==2 || choix==3){
        positionFond.x = 400;
        positionFond.y = 250;
        imageDeFond = SDL_LoadBMP("loto/grille.bmp");
        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
        SDL_Flip(ecran);
        if(choix==3){
            positionFond.x = 400;
            positionFond.y = 450;
            imageDeFond = SDL_LoadBMP("loto/grille.bmp");
            SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
            SDL_Flip(ecran);
        }
    }
    positionFond.x = 1130;
    positionFond.y = 400;
    SDL_Color color = {255, 0, 0};
    TTF_Font *police = TTF_OpenFont("font/arialunicode.ttf",40);
    imageDeFond = TTF_RenderText_Blended(police, "1", color);
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond); // On blitte par-dessus l'�cran
    SDL_Flip(ecran);

    Compteur cpt;
    cpt[0]=0;
    srand(time(NULL)); // Necessaire pour la generation aleatoire (ligne a executer 1 seule fois)
    init(9,9,t);
    Tirage tab;
    initialisationTirage(&tab);
    int numTirage; //numero du tirage actuel
    int victoire = -1; //1 si victoire 0 defaite car pas tous les nums -1 defaite car tous les tirages ont ete effectues

    genererCartons(t,choix);

    numTirage=numtire(&tab);
    majtirage(numTirage,&tab);
    ecrireLoto(t,ecran,imageDeFond,positionFond,choix,tab);


    clock_t t1,t2;
    t1 = clock();

    SDL_Event event;
    while(positionFond.x>=0 && positionFond.y>=0)
    {
        SDL_PollEvent(&event);
        t2 = clock();
        if((int)((t2-t1)/CLOCKS_PER_SEC)>3){
            tab = suivant(ecran,imageDeFond,positionFond,t,choix,tab);
            t1 = t2;
        }
        switch(event.type)
        {
            case SDL_MOUSEBUTTONUP:
            {
                if(event.button.x>133 && event.button.x<452 && event.button.y>676 && event.button.y<705){
                    positionFond.x = -2;
                    positionFond.y = -2;
                    return positionFond;
                    break;
                }
                else if(event.button.x>1143 && event.button.x<1294 && event.button.y>670 && event.button.y<705){
                    positionFond.x = -1;
                    positionFond.y = -1;
                    return positionFond;
                    break;
                }
                else{
                    positionFond = cliqueSourisLoto3(tab,ecran,imageDeFond,positionFond,event,t,choix);
                    if(positionFond.x>=0 && tab.nbtirage<91){
                        ecrireLoto(t,ecran,imageDeFond,positionFond,choix,tab);
                        if(verifierVictoire(t,choix)){
                            positionFond.x = 110;
                            positionFond.y = 250;
                            imageDeFond = TTF_RenderText_Blended(police, "Gagn�", color);
                            SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond); // On blitte par-dessus l'�cran
                            SDL_Flip(ecran);
                            cpt[0]=scorefinal(t,choix,tab);
                            enregistrerScore(pseudo, cpt[0]);
                            tab.nbtirage = 91;
                        }
                    }
                }
                break;
            }
            default : break;
        }
    }
}


/**Fonction qui v�rifie si une case cliqu� correspond avec le num�ro tir� et dans ce cas, lui donne l'�tat 2*/
SDL_Rect cliqueSourisLoto3(Tirage tab, SDL_Surface *ecran, SDL_Surface *imageDeFond, SDL_Rect positionFond, SDL_Event event, TAB t, int choix){
    int longueur_case,hauteur_case,hauteur_grille;
    hauteur_grille = 0;
    if(tab.nbtirage<91){
    for(int i=0;i<choix;i++)
    {
        hauteur_case = 0;
        for(int l=0;l<3;l++)
        {
            longueur_case = 0;
            for(int j=0;j<9;j++)
            {
                if(event.button.x>400+longueur_case && event.button.x<=460+longueur_case && event.button.y>50+hauteur_case+hauteur_grille && event.button.y<=110+hauteur_case+hauteur_grille)
                {
                    if(tab.tab[tab.nbtirage-1] == t[l+(3*i)][j].valeur){
                        t[l+(3*i)][j].etat = 2;
                   }
                    return positionFond;
                }
                longueur_case += 60;
            }
            hauteur_case +=60;
        }
        hauteur_grille += 200;
    }
    }
    return positionFond;
}
