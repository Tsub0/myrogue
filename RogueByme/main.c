#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include "monstres.h"

#define TAILLE_CARTE 20 // définition de la taille de la carte

// définition de différents types de cases de la carte
#define VIDE '.'
#define MUR '#'
#define JOUEUR '@'
#define MONSTRE 'M'
#define TRESOR 'T'
#define POTION '&'
#define ARMURE '='
#define BASE_VIE_MONSTRE 10

void afficherItem(int id);
void afficherDescription(int id);

char carte[TAILLE_CARTE][TAILLE_CARTE]; // déclaration de la carte

int main(void) {

    srand(time(NULL)); // initialisation de la fonction rand

    char ITEM = 'o';
    // position joueur
    int x = 1;
    int y = 1;
    // position joueur lors de deplacement
    int newX = x;
    int newY = y;

    int armure = 0;

    int hitwall = 0; // Si le joueur touche un mur
    int inventaire = 0; // Si on la fenetre d'inventaire est ouverte
    int selection = 0; // L'item selectionne dans l'inventaire
    int inventaireJoueur[] = {0,0,0,0,0,0}; // L'inventaire du joueur ou sont stockees les id des items
    int equipement = 0; // L'arme du joueur - id
    int J_armure = 0; // id de L'armure du joueur
    // position objet
    int xObj = (rand() % TAILLE_CARTE-4) + 2;
    int yObj = (rand() % TAILLE_CARTE-4) + 2;

    int idObjet = 2; // id objet
    int presenceObjet = 0; // si le joueur est sur la meme case qu'un objet
    // position de la potion
    int xPot = (rand() % TAILLE_CARTE-4) + 2;
    int yPot = (rand() % TAILLE_CARTE-4) + 2;

    int hpJoueur = 25;// points de vie du joueur
    int vagues = 1; // nombre de vagues
    int monstre_1[8] = {TAILLE_CARTE-2,TAILLE_CARTE-2,10,0,0,0,0,0};
    //{x,y,vie monstre,ancienX, ancienY,directionmove,idARME,arme}
    int distancesMonstreHeros[2]; // distances verticales et horizontales entre le monstre et le heros
    int distancesMonstreItem[2];
    float distances[2]; // 0 -> distance monstre heros 1 -> distance monstre objet

    int contact = 0; // si le monstre et le joueur entrent en contact
    int degats[2] = {0,0}; // {degats du monstre, degats du heros}
    int pvPotion=0; // le nombre de pv que la potion soigne
    int nbTours = 0; // le nombre de tours
    int usureArme = 15; // le nombre de coups avant que l'epee ne se casse
    int usureMax = 15;
    int presencePotion=1; // si la potion est presente sur la carte
    int xMur,yMur; // position lorsqu'on place un mur
    int afficherPotion = 0; // si on affiche les positions de la potion
    int maxPv = 25; // Le nombre max de points de vie
    int vagueSuivante = 1;
    int monstreProcheObjet=0;

    int presenceArmure = 0;

    int toutAfficher = 0;

    int armeMonstre = 0;

    //entourage du monstre :
    char m_gauche, m_droite, m_haut, m_bas;

    // on remplit la carte :
    for (int i = 0; i < TAILLE_CARTE; i++) {
        // MURS DE LA CARTE
        for (int j = 0; j < TAILLE_CARTE;j++){
            if (i == 0 || j == 0 || i == TAILLE_CARTE -1 || j == TAILLE_CARTE - 1){
                carte[i][j] = MUR;
            } else {
                carte[i][j] = VIDE;
            }
        }
        // "labyrinthe"
        for (int i = 0;i < TAILLE_CARTE-rand()%TAILLE_CARTE;i++){
            do {
                xMur = (rand() % TAILLE_CARTE-2) + 1;
                yMur = (rand() % TAILLE_CARTE-2) + 1;
            } while((xMur == 1 && yMur == 1) && (xMur == 1 && yMur == 1));
            carte[yMur][xMur] = MUR;
        }
    }
    carte[1][1] = JOUEUR;


    char touche = ' ';

    do {
        system("CLS"); // on efface l'ecran
        if (inventaire==0)
            nbTours++; // Si on est hors de l'inventaire et que la boucle se relance alors on ajoute un tour

        switch(touche){

        case 'g':
            monstre_1[2]+=20;
            break;

        case 'x':
            if (toutAfficher == 0) {
                toutAfficher = 1;
            } else {
                toutAfficher = 0;
            }
            break;

        case 'p': // Si on appuie sur P
            if (afficherPotion==0){
                afficherPotion = 1; // on affiche les coordonnees de la potion
            } else {
                afficherPotion = 0;
            }
            break;

        case 'z':// pour aller vers le haut
            if (inventaire==0){ // si on est dans le jeu
                if (carte[y-1][x]!=MUR) { // pour empêcher de foncer dans un mur
                    newY = y-1;
                } else {
                    hitwall = 1; // Si il y a un mur on le signale
                }
            } else {
                if (selection>0){ // aller vers le haut dans l'inventaire
                    selection--;
                }
            }
            break;
        case 'h':
            hpJoueur = maxPv;
            break;


        case 'r': // reset de la carte si on est coincé
            for (int i = 0; i < TAILLE_CARTE; i++) {
                for (int j = 0; j < TAILLE_CARTE;j++){
                    if (i == 0 || j == 0 || i == TAILLE_CARTE -1 || j == TAILLE_CARTE - 1){
                        carte[i][j] = MUR;
                    } else {
                        carte[i][j] = VIDE;
                    }
                }
                for (int i = 0;i < TAILLE_CARTE-rand()%TAILLE_CARTE;i++){
                    do {
                        xMur = (rand() % TAILLE_CARTE-2) + 1;
                        yMur = (rand() % TAILLE_CARTE-2) + 1;
                    } while((xMur == 1 && yMur == 1) && (xMur == 1 && yMur == 1));
                    carte[yMur][xMur] = MUR;
                }
                vagues = 0;
                nbTours = 0;
                xObj = (rand() % TAILLE_CARTE-2) + 1;
                yObj = (rand() % TAILLE_CARTE-2) + 1;
                idObjet = 2;
                presenceObjet = 0;
                xPot = (rand() % TAILLE_CARTE-4) + 2;
                yPot = (rand() % TAILLE_CARTE-4) + 2;
            }
            newX = 1;
            newY = 1;
            monstre_1[0]=TAILLE_CARTE-2;
            monstre_1[1]=TAILLE_CARTE-2;

            break;
        case 's':
            if (inventaire==0){
                if (carte[y+1][x]!=MUR) {
                    newY = y+1;
                } else {
                    hitwall = 1;
                }
            } else {
                if (selection<5){
                    selection++;
                }
            }
            break;

        case 'q':
            if (inventaire==0){
                if (carte[y][x-1]!=MUR) {
                    newX = x-1;
                } else {
                    hitwall = 1;
                }
            }
            break;

        case 'd':
            if (inventaire==0){
                if (carte[y][x+1]!=MUR) {
                    newX = x+1;
                } else {
                    hitwall = 1;
                }
            }
            break;

        case 'i':
            if (inventaire == 1){
                inventaire = 0;
                selection = 0;
                break;
            } else {
                inventaire = 1;
            }
            break;

        case 'e':
            if (inventaire == 0) {
                if (presenceObjet==1){
                    for (int i = 0;i<6;i++){
                        if (inventaireJoueur[i]==0){
                            if (xObj == x && yObj == y) {
                                inventaireJoueur[i]=idObjet;
                                xObj = 0;
                                yObj = 0;
                                ITEM = '#';
                            } else {
                                inventaireJoueur[i]=1;
                                xPot = 0;
                                yPot = 0;
                                presencePotion = 0;
                            }
                            break;
                        }
                    }

                    presenceObjet=0;
                }
            } else {
                if (presenceObjet == 1) {
                    switch (inventaireJoueur[selection]){

                        case 3:
                            equipement = 3;
                            usureArme = 10;
                            usureMax = 10;
                            break;

                        case 2 :
                            equipement = 2;
                            usureArme = 15;
                            usureMax = 15;
                            break;

                        case 4 :
                            equipement = 4;
                            usureArme = 15;
                            usureMax = 15;
                            break;

                        case 1 :
                            if (vagues<10){
                                pvPotion = 5+rand()%4+vagues;
                            } else {
                                pvPotion = 13+rand()%7;
                            }
                            if (pvPotion+hpJoueur>maxPv){
                                hpJoueur = maxPv;
                            } else {
                                hpJoueur += pvPotion;
                            }

                    }
                    inventaireJoueur[selection]=0;
                }
            }
            break;
        }



        if (nbTours%30==0){
            do {
                carte[yPot][xPot] = VIDE;
                xPot = (rand() % TAILLE_CARTE-2) + 1;
                yPot = (rand() % TAILLE_CARTE-2) + 1;
            } while (carte[yPot][xPot]==MUR);
            presencePotion = 1;
        }
        if (presenceObjet == 0 && nbTours%50==0){
            do {
                carte[yObj][xObj] = VIDE;
                xObj = (rand() % TAILLE_CARTE-2) + 1;
                yObj = (rand() % TAILLE_CARTE-2) + 1;
                ITEM = 'o';
                idObjet = 2+(rand()%3);
            } while (carte[yObj][xObj]==MUR);
            presenceObjet = 1;
        }


        // ========= déplacement du monstre =========

        m_gauche = carte[monstre_1[0]][monstre_1[1]-1];
        m_droite = carte[monstre_1[0]][monstre_1[1]+1];
        m_haut = carte[monstre_1[0]-1][monstre_1[1]];
        m_bas = carte[monstre_1[0]+1][monstre_1[1]];

        distancesMonstreHeros[0] = y-monstre_1[0];
        distancesMonstreHeros[1] = x-monstre_1[1];

        if (distancesMonstreHeros[0]<0){
            distancesMonstreHeros[0]*=-1;
        }

        if (distancesMonstreHeros[1]<0){
            distancesMonstreHeros[1]*=-1;
        }

        distancesMonstreItem[0] = yObj-monstre_1[0];
        distancesMonstreItem[1] = xObj-monstre_1[1];

        if (distancesMonstreItem[0]<0){
            distancesMonstreItem[0]*=-1;
        }

        if (distancesMonstreItem[1]<0){
            distancesMonstreItem[1]*=-1;
        }

        distances[0]=sqrt(pow(distancesMonstreHeros[0],2)+pow(distancesMonstreHeros[1],2));
        distances[1]=sqrt(pow(distancesMonstreItem[0],2)+pow(distancesMonstreItem[1],2));

        if (distances[1]<distances[0] && (xObj != 0 && yObj != 0)){
            monstreProcheObjet = 1;
        } else {
            monstreProcheObjet = 0;
        }
        monstre_1[3]=monstre_1[0];
        monstre_1[4]=monstre_1[1];
        if (inventaire==0){
            if (vagues>5){
                monstre_1[5]=rand()%3;
            } else {
                monstre_1[5]=rand()%2;
            }
            switch(monstre_1[5]){
            case 0 : // MOUVEMENT VERTICAL
                if (monstreProcheObjet==0){
                    if (monstre_1[0]<y) {
                        if (m_bas!=MUR){
                            monstre_1[0]++;
                        } else {
                            if (m_droite != MUR) {
                                monstre_1[1]++;
                            } else {
                                if (m_gauche != MUR)
                                    monstre_1[1]--;
                            }
                        }
                    } else {
                        if (monstre_1[0]>y) {
                            if (m_haut!=MUR){
                                monstre_1[0]--;
                            } else {
                                if (m_gauche!= MUR){
                                    monstre_1[1]--;
                                } else {
                                    if (m_droite)
                                        monstre_1[1]++;
                                }
                            }
                        }                    }
                }else{
                    if (monstre_1[0]<yObj) {
                        if (m_bas!=MUR){
                            monstre_1[0]++;
                        } else {
                            if (m_droite != MUR) {
                                monstre_1[1]++;
                            } else {
                                if (m_gauche != MUR)
                                    monstre_1[1]--;
                            }
                        }
                    } else {
                        if (monstre_1[0]>y) {
                            if (m_haut!=MUR){
                                monstre_1[0]--;
                            } else {
                                if (m_gauche!= MUR){
                                    monstre_1[1]--;
                                } else {
                                    if (m_droite)
                                        monstre_1[1]++;
                                }
                            }
                        }
                    }
                }
                break;
            case 1 : // mouvement horizontal
                if (monstreProcheObjet==0){
                    if (monstre_1[1]<x) {
                        if (m_droite!=MUR){
                            monstre_1[1]++;
                        } else {
                            if (m_haut!=MUR){
                                monstre_1[0]--;
                            } else {
                                if (m_bas!=MUR){
                                    monstre_1[0]++;
                                }
                            }
                        }
                    } else {
                        if (monstre_1[1]>x) {
                            if (m_gauche != MUR) {
                                monstre_1[1]--;
                            } else {
                                if (m_haut!=MUR){
                                    monstre_1[0]--;
                                } else {
                                    if (m_bas!=MUR)
                                        monstre_1[0]++;
                                }
                            }
                        }
                    }
                }else{
                    if (monstre_1[1]<xObj) {
                        if (m_droite!=MUR){
                            monstre_1[1]++;
                        } else {
                            if (m_haut!=MUR){
                                monstre_1[0]--;
                            } else {
                                if (m_bas!=MUR)
                                    monstre_1[0]++;
                            }
                        }
                    } else {
                        if (monstre_1[1]>xObj) {
                            if (m_gauche!=MUR){
                                monstre_1[1]--;
                            } else {
                                if (m_haut != MUR) {
                                    monstre_1[0]--;
                                } else {
                                    if (m_bas != MUR){
                                        monstre_1[0]++;
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            case 2 : // mouvement diagonal
                if (monstreProcheObjet == 0){
                    if (monstre_1[0] && m_bas!=MUR) {

                        monstre_1[0]++;
                    } else {
                        if (monstre_1[0]>y && m_haut!=MUR) {
                            monstre_1[0]--;
                        }
                    }
                    if (monstre_1[1]<x && m_droite!=MUR) {
                        monstre_1[1]++;
                    } else {
                        if (monstre_1[1]>x && m_gauche!=MUR) {
                            monstre_1[1]--;
                        }
                    }
                } else {
                    if (monstre_1[0] && m_bas!=MUR) {

                        monstre_1[0]++;
                    } else {
                        if (monstre_1[0]>yObj && m_haut!=MUR) {
                            monstre_1[0]--;
                        }
                    }
                    if (monstre_1[1]<xObj && m_droite!=MUR) {
                        monstre_1[1]++;
                    } else {
                        if (monstre_1[1]>xObj && m_gauche!=MUR) {
                            monstre_1[1]--;
                        }
                    }
                }
                break;
            }
            if (monstre_1[0] == yObj && monstre_1[1] == xObj) {
                ITEM = '#';
                yObj = 0;
                xObj = 0;
                monstre_1[6] = idObjet;
                armeMonstre = 1;
                switch(idObjet){
                    case 2 :
                        monstre_1[7] = 15;
                        break;
                    case 3 :
                        monstre_1[7] = 10;
                        break;

                    case 4 :
                        monstre_1[7] = 15;
                        break;
                }
            }
        }
        carte[monstre_1[3]][monstre_1[4]] = VIDE;
        carte[y][x] = VIDE;
        carte[yPot][xPot] = POTION;
        carte[yObj][xObj] = ITEM;
        carte[monstre_1[0]][monstre_1[1]] = MONSTRE;
        if (monstre_1[0]==newY && monstre_1[1]==newX){
            contact=1;
            usureArme --;

            if (x<newX) {
                if (monstre_1[1]>1){
                    monstre_1[1]--;
                } else {
                    newX++;
                }
            }
            if (y<newY){
                if (monstre_1[0]>1){
                    monstre_1[0]--;
                } else {
                    newY++;
                }
            }
            if (x>newX) {
                if (monstre_1[1]<TAILLE_CARTE-2){
                    monstre_1[1]++;
                } else {
                    newX--;
                }
            }
            if (y<newY){
                if (monstre_1[0]<TAILLE_CARTE-2){
                    monstre_1[0]++;
                } else {
                    newY--;
                }
            }
        }

        x = newX;
        y = newY;
        carte[y][x] = JOUEUR;
        if (hpJoueur>0){
            if (inventaire == 0){
                printf("\t\t\033[4;31mLE DONJON DES DAMNES\033[0;37m\n");
                printf("\t-= VAGUE : %i  |  TOURS : %i =-\n",vagues,nbTours);
                // affichage carte
                for (int i = 0; i < TAILLE_CARTE; i++) {
                    for (int j = 0; j < TAILLE_CARTE; j++) {
                        switch (carte[i][j]){
                        case '#':
                            printf("\033[0;31m%c ", carte[i][j]);
                            break;

                        case '@':
                            printf("\033[1;93m%c ", carte[i][j]);
                            break;

                        case '&':
                            printf("\033[0;36m%c ", carte[i][j]);
                            break;

                        case 'o':
                            printf("\033[0;34m%c ", carte[i][j]);
                            break;

                        case 'M':
                            printf("\033[1;32m%c ", carte[i][j]);
                            break;



                        default :
                            printf("\033[0;37m%c ", carte[i][j]);
                            break;
                        }
                    }
                    printf("\n");
                }
                printf("\033[37m\n\nMouvements : ZQSD");
                printf("\nInventaire : I");
                printf("\nRamasser : E\tAfficher co potion : P");
                if (afficherPotion == 1){
                    printf("\nLa potion est situee en [%i][%i]",yPot,xPot);
                }
                printf("\nQUITTER : ECHAP");
                printf("\nEquipement : ");
                afficherItem(equipement);
                printf("  %i/%i",usureArme,usureMax);




                printf("\n");
                if (hitwall == 1) {
                    printf("\nJe ne peux pas aller dans cette direction, il y a un mur devant moi !");
                    hitwall = 0;
                }

                if (armeMonstre == 1){
                    printf("\nLe monstre s'est saisi de ");
                    afficherItem(idObjet);
                    printf(" !");
                    armeMonstre = 0;
                }

                if (contact == 1) {
                    printf("Arriere vil monstre !\nVous vous battez avec le monstre.");
                    // Calcul des dégats du monstre
                    if (rand()%5 != 1) { // 1 chance / 5 d'éviter le coup du monstre
                        switch (monstre_1[6]){
                            case 0:
                                degats[0] = 2+rand()%(2+vagues);
                                break;
                            case 2:
                                degats[0] = rand()%(3+vagues)+3;
                                break;
                            case 3:
                                degats[0] = rand()%(3+vagues)+5;
                                break;
                            case 4:
                                degats[0] = rand()%(3+vagues)+3;
                                break;
                            if (monstre_1[7]>0){
                                monstre_1[7]--;
                                if (monstre_1[7]== 0){
                                    printf("L'arme du monstre se brise !");
                                    monstre_1[6]=0;
                                }
                            }

                        }

                    } else {
                        printf("Vous evitez le monstre de justesse !");
                        degats[0] = 0;
                    }
                    if (rand()%8 != 1){ // 1 chance / 8 d'eviter
                        switch (equipement){
                            case 3:
                                degats[1] = 6+rand()%6;
                                break;
                            case 2:
                                degats[1] = 4+rand()%4;
                                break;

                            case 0:
                                degats[1] = 1+rand()%4;
                                break;

                            case 4:
                                degats[1] = 4+rand()%4;
                        }

                    } else {
                        printf("\nLe monstre esquive !");
                        degats[1] = 0;
                    }
                    hpJoueur -= degats[0];
                    monstre_1[2] -= degats[1];
                    printf("\nVous prenez %i degats de la part du monstre, %i pv restants. \nVous avez inflige %i degats au monstre.",degats[0],hpJoueur,degats[1]);
                    if (monstre_1[2]<=0){
                        printf("Vous avez vaincu le monstres et vous passez a la prochaine vague !");
                        maxPv++;
                        vagues++;
                        monstre_1[0]=13+rand()%6;
                        monstre_1[1]=13+rand()%6;
                        monstre_1[2]=BASE_VIE_MONSTRE+vagues;
                        monstre_1[6]=0;
                        monstre_1[7]=0;
                        getch();
                        vagueSuivante = 1;


                    }
                    contact = 0;
                }
                printf("\nHP : %i/%i          HP MONSTRE : %i/%i",hpJoueur,maxPv,monstre_1[2],BASE_VIE_MONSTRE+vagues-1);

                if (usureArme == 0) {
                    printf("\nLa lame de votre epee se brise sous vos yeux ! Trouvez en rapidement une autre !");
                    equipement = 0;
                    ITEM = 'o';
                    do {
                        xObj = (rand() % TAILLE_CARTE-2) + 1;
                        yObj = (rand() % TAILLE_CARTE-2) + 1;
                    } while(carte[yObj][xObj]==MUR);

                }
                if ((xObj == x && yObj == y)||(xPot == x && yPot == y)){
                    printf("\nSur cette case il y a : ");
                    if (xObj == x && yObj == y) {
                        afficherItem(idObjet);
                    } else {
                        afficherItem(1);
                    }
                    presenceObjet = 1;
                } else {
                    presenceObjet = 0;
                }

                if (toutAfficher == 1){
                    printf("\n\n\033[0;34mSi besoin d'une info :\n");
                    printf("Le monstre est situe en : [%i][%i]\n",monstre_1[0],monstre_1[1]);
                    printf("Il est equipe de l'arme :");
                    afficherItem(monstre_1[6]);
                    printf("   %i",monstre_1[7]);
                    printf("\nIl se deplace dans le sens : ");
                    switch(monstre_1[5]){
                    case 0:
                        printf("vertical \n");
                        break;
                    case 1:
                        printf("horizontal \n");
                        break;
                    case 2:
                        printf("diagonal \n");
                        break;
                    }
                    printf("L'id de l'objet est : %i",idObjet);
                    printf("\n\n");
                    printf("HEAL : H\n");
                    printf("RESET : R\n");
                    printf("MONSTRE + PV : G\n");

                    printf("\033[0;37m");
                }

            } else {

            //     == INVENTAIRE ==
            // affichage inventaire
                printf("\t# INVENTAIRE #");
                printf("\n\n");
                for (int i=0;i<6;i++){
                    printf("%i.",i+1); // On affiche les 6 cases de l'inventaire
                    afficherItem(inventaireJoueur[i]); // On affiche les items qui y vont (rien si l'id = 0)
                    if (i == selection){ // Si l'item en question est celui selectionne
                        printf(" <-"); // alors on affiche une fleche a l'utilisateur
                    }
                    if (i != 0){
                        presenceObjet = 1;
                    } else {
                        presenceObjet = 0;
                    }
                    printf("\n");

                }

                printf("\n\nNaviguer dans l'inventaire : ZS\nRetourner au jeu : I");
                if (presenceObjet == 1){
                    printf("\nUtiliser/equiper ");
                    afficherItem(inventaireJoueur[selection]);
                    printf("  : E ");
                    printf("\nHP : %i/%i",hpJoueur,maxPv);
                }
                printf("\n\n");
                afficherDescription(inventaireJoueur[selection]);
            }
        } else { // Si le hpJoueur est inferieur a 0
            printf("=====================================\n");
            printf("          VOUS ETES MORT !\n");
            printf("=====================================\n");
            break;
        }
        if (vagueSuivante!=1){
            touche = getch();

        }else{
            system("CLS");
            afficherMenace(1,0,0);
            printf("\n\nCLIQUEZ N'IMPORTE OU POUR CONTINUER");
            getch();
            vagueSuivante=0;
        }


    } while (touche != 27); // Si on appuie sur ECHAP alors cela arrete directement le programme

    return 0; // fin du programme
}

void afficherItem(int id){
    /*
    afficherItem(id) prend en argument l'identifiant d'un item et
    affiche simplement son nom
    */
    switch(id){
        case 0 :
            printf("Rien");
            break;
        case 2 :
            printf("Epee");
            break;
        case 1 :
            printf("Potion");
            break;
        case 3 :
            printf("Hallebarde");
            break;
        case 4 :
            printf("Masse d'arme");
            break;
    }
}

void afficherDescription(int id) {
    /*
    afficherDescription(id) prend l'identifiant d'un item en argument
    A partir de l'id il affiche la description de l'item sous la forme
    item : [description]
    */
    afficherItem(id);
    switch(id){
        case 0 :
            printf(" : Literalement, rien.");
            break;
        case 2 :
            printf(" : Une epee qui vous permettra de taper vos ennemis 15 fois avant de se casser.");
            break;
        case 1 :
            printf(" : Cette potion vous heal un certain nombre de points de vie sans depasser vos pv max.");
            break;
        case 3 :
            printf(" : Une hallebarde, moins de durabilite que l'epee mais plus de degats !");
            break;
        case 4 :
            printf(" : La masse d'arme a une plus grande durabilité que l'épée et fait tout autant de degats.");
    }
}
