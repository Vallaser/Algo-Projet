#include "loto.h"
#include "tiragee.h"


//Verifie pour une, deux ou trois grilles   qu'elles contiennent uniquement des nombres contenus dans le tableau des tirages effectues   1 si vrai    0 si faux
int verifierVictoire_aux(TAB t, int yStart, int yEnd) {  //ystart et yend sont les entiers qui delimitent quelle partie du tableau il faut verifier (en fonction du nombre de grilles)
    for (int y=yStart; y<=yEnd; y++){
        for (int x=0; x<9; x++) {
            if (t[y][x].valeur!=0) {
                if (!t[y][x].etat==2) {  //si le nombre n'est pas "d�couvert", fin de la fonction, retourne 0
                    return 0;
                }
            }
        }
    }
    return 1;
}

int verifierVictoire(TAB t, int nbCartons) {
    switch(nbCartons) {
        case 1 :
            verifierVictoire_aux(t, 0, 2);
            break;
        case 2 :
            verifierVictoire_aux(t, 0, 5);
            break;
        case 3 :
            verifierVictoire_aux(t, 0, 8);
            break;
        default :
            verifierVictoire_aux(t, 0, 8);
            break;
    }
}

//Verifie si un nombre est present dans une grille    1 si vrai 0 sinon
int estDejaPresent(TAB t, int yStart, int yEnd, int nombre, int col) {
    for (int i=yStart; i<=yEnd; i++) {
        if (t[i][col].valeur == nombre) {
                return 1;
        }
    }
    return 0;
}

//Verifie si la colonne o� doit �tre place le nombre est pleine ou pas   1 si vrai 0 sinon
int colonneRemplie(TAB t, int yStart, int yEnd, int nombre, int col) {
    for (int i=yStart; i<=yEnd; i++) {
        if (t[i][col].valeur == 0) {
            return 0;
        }
    }
    return 1;
}

//compte le nombre de valeurs dans une ligne du tableau
int compter(TAB t, int ligne) {
    int cpt = 0;
    for (int i=0; i<9; i++) {
        if (t[ligne][i].valeur != 0) {
            cpt++;
        }
    }
    return cpt;
}

//retourne 1 si il y a une place disponible dans la colonne citee qui est valide, cad si la ligne ou la place se situe il y a moins de 5 valeurs
int placeDispoValide(TAB t, int yStart, int yEnd, int col) {
    for (int i=yStart; i<=yEnd; i++) {
        if (t[i][col].valeur==0 && compter(t, i)<5) {
            return 1;
        }
    }
    return 0;
}

//Genere une grille avec toutes les contraintes du loto   (retourne 1 si generation effectu�e, 0 sinon)
int generer(TAB t, int yStart, int yEnd) { //yStart et yEnd entiers qui delimitent la partie du tableau a generer (ex 0 et 2 si une seule grille)
    if (yEnd - yStart == 2) { //verification car on genere une grille � la fois
        int cpt = 0; //nombre de nombres places dans la grille
        while (cpt<15) {
            int nbr = getRandom(1,90);
            int col;
            if (nbr==90) {
                col = 8;
            } else {
                col = nbr/10;
            }

            if (estDejaPresent(t, yStart, yEnd, nbr, col)==0 && colonneRemplie(t, yStart, yEnd, nbr, col)==0 && placeDispoValide(t, yStart, yEnd, col)==1) {
                int lig;
                do {
                    lig = getRandom(yStart, yEnd);
                }while (compter(t, lig)>=5 || t[lig][col].valeur != 0);
                t[lig][col].etat = 1;
                t[lig][col].valeur = nbr;
                cpt++;
            }
        }
        return 1;
    } else {
        return 0;
    }
}

//genere le nombre de cartons demandes (par defaut 3)
int genererCartons(TAB t, int nbCartons) {
    switch(nbCartons) {
        case 1 :
            generer(t, 0, 2);
            break;
        case 2 :
            generer(t, 0, 2);
            generer(t, 3, 5);
            break;
        case 3 :
            generer(t, 0, 2);
            generer(t, 3, 5);
            generer(t, 6, 8);
            break;
        default :
            generer(t, 0, 2);
            generer(t, 3, 5);
            generer(t, 6, 8);
            break;
    }
}

void loto() {
    srand(time(NULL)); // Necessaire pour la generation aleatoire (ligne a executer 1 seule fois)

    TAB tab;
    init(9,9,tab);
    Tirage t;
    initialisationTirage(&t);
    int numTirage; //numero du tirage actuel
    int choix; // choix du joueur
    int victoire = -1; //1 si victoire 0 defaite car pas tous les nums -1 defaite car tous les tirages ont ete effectues

    int nbCartons;
    do {
        printf("Combien de cartons de loto voulez-vous ? 1, 2 ou 3 ?\n");
        scanf("%d",&nbCartons);
    }while (nbCartons!=1 && nbCartons!=2 && nbCartons != 3);

    genererCartons(tab, nbCartons);

    printf("DEBUT DU JEU\n\n");

    while(t.nbtirage<90){
        //effectuer un tirage
        numTirage=numtire(&t);
        majtirage(numTirage,&t);
        printf("\nLe numero du Tirage est : %d\n",numTirage);
        //afficher le tableau
        affiche(tab);
        printf("\n0 : tirage suivant");
        printf("\n1 : j'ai ce numero !");
        printf("\n2 : j'ai gagne !\n");
        scanf("%d",&choix);
        if (choix==2) {
            victoire = verifierVictoire(tab, nbCartons); // A REVOIR
            break;
        } else if (choix==1) {
            //appeler fonction qui verifie que le numTirage est dans la grille et passe l'etat � 2
        }
    }
    if (victoire == 1) {
        printf("VOUS AVEZ GAGNE !\n Nombre de tirages : %d", t.nbtirage);
    } else if (victoire == 0){
        printf("VOUS AVEZ PERDU !\n Vos cartons ne sont pas remplis !\n Nombre de tirages : %d", t.nbtirage);
    } else {
        printf("VOUS AVEZ PERDU !\n Tous les nombres ont ete tires !\nNombre de tirages : %d", t.nbtirage);
    }

    printf("\nFIN DU JEU\n\n");
}

