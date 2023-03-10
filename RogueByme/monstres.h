void creerNomMonstre();
void afficherMenace();
void afficherCouleur(int genre,int pluriel);
void afficherAdj();
void afficherMiseEnGarde();
void afficherGriffes();
void afficherPelage();
void afficherPeau();
void afficherYeux();
void afficherPlumage();
void afficherCrocs();
void suiteMiseEnGarde();

void suiteMiseEnGarde(){
    switch(rand()%5){
        case 0 :
            printf("est dans les parages");
            break;
        case 1 :
            printf("approche");
            break;
        case 2 :
            printf("arrive");
            break;
        case 3 :
            printf("debarque");
            break;
        case 4 :
            printf("est apparu");
            break;
    }

    if (rand()%2==0){
        printf(" !");
    } else {
        printf("...");
    }

    printf("\n");


}
void afficherMenace(int griffes,int pelage,int plumage){
    afficherMiseEnGarde();
    afficherAdj();
    creerNomMonstre();
    suiteMiseEnGarde();
    afficherPeau();
    afficherYeux();
    afficherCrocs();
    if (griffes != 0)
        afficherGriffes();
    if (pelage !=0)
        afficherPelage();
    if (plumage!=0)
        afficherPlumage();

}

void afficherPelage(){
    printf("Son pelage est ");
    afficherCouleur(0,0);
    printf(". ");
}

void afficherPeau(){
    printf("Sa peau est ");
    afficherCouleur(1,0);
    printf(". ");
}

void afficherGriffes(){
    printf("Ses griffes sont ");
    afficherCouleur(1,1);
    printf(". ");
}

void afficherYeux(){
    printf("Ses yeux sont ");
    afficherCouleur(0,1);
    printf(". ");
}

void afficherCrocs(){
    printf("Ses crocs sont ");
    afficherCouleur(0 ,1);
    printf(". ");
}

void afficherPlumage(){
    printf("Ses plumes sont ");
    afficherCouleur(1,1);
    printf(". ");
}

void creerNomMonstre(){
    char voyelles[6] = {'a','e','i','o','u','y'};
    char consonnes[18] = {'b','c','d','f','g','j','k','l','m','n','p','r','s','t','v','w','x','z'};
    int voy = rand()%2;
    int nbLettres = rand()%4 + 5;
    char lettre;
    int lettreH=0;

    if (voy == 1){
        printf("%c",voyelles[rand()%6]-32);
    } else {
        printf("%c",consonnes[rand()%18]-32);
    }

    for (int i = 0; i<nbLettres;i++){
         // on fait une voyelle dans ce cas
         voy++;
         if (voy%2==0){
            lettre = consonnes[rand()%18];
            printf("%c",lettre);
            if (lettre == 's' || lettre == 'p' || lettre == 'c'){
                if (rand()%6==0)
                    printf("h");
            }
            if (i!=nbLettres){
                if (lettre == 'f' || lettre == 'r' || lettre == 't' || lettre == 's' || lettre == 'n' || lettre == 'm' || lettre == 'p'){
                    if (rand()%4==0){
                        printf("%c",lettre);
                    }
                }
            }
         } else {
            lettre = voyelles[rand()%6];
            printf("%c",lettre);
         }
    }
    printf(" ");
}

void afficherCouleur(int genre,int pluriel){// 0 = masculin 1 = feminin
    int couleur = rand()%11;
    switch(couleur){
        case 0 :
            printf("bleu");
            break;
        case 1 :
            printf("jaune");
            break;
        case 2 :
            printf("rose");
            break;
        case 3 :
            printf("violet");
            break;
        case 4 :
            printf("orange");
            break;
        case 5 :
            printf("brun");
            break;
        case 6 :
            printf("gris");
            break;
        case 7 :
            printf("mauve");
            break;
        case 8 :
            printf("rouge");
            break;
        case 9 :
            printf("blanc");
            break;
        case 10 :
            printf("noir");
            break;
    }
    if  (genre==1) {
        switch(couleur){
            case 0 :
                printf("e");
                break;
            case 3 :
                printf("te");
                break;
            case 5 :
                printf("e");
                break;
            case 6 :
                printf("e");
                break;
            case 9 :
                printf("he");
                break;
            case 10 :
                printf("e");
        }
    }
    if (pluriel == 1)
        if (couleur==6 && genre == 0){
            printf("");
        } else {
            printf("s");
        }
}

void afficherMiseEnGarde(){
    switch(rand()%10){
        case 0:
            printf("Prenez garde, ");
            break;
        case 1:
            printf("Attention, ");
            break;
        case 2:
            printf("Faites attention, ");
            break;
        case 3:
            printf("Gare a vous, ");
            break;
        case 4:
            printf("Faites tres attention, ");
            break;
        case 5:
            printf("Mefiez vous, ");
            break;
        case 6:
            printf("Verifiez vos arrieres, ");
            break;
        case 7:
            printf("Soyez vigilant... ");
            break;
        case 8:
            printf("Prenez garde... ");
            break;
        case 9:
            printf("Mefiez vous... ");
            break;
    }
}

void afficherAdj(){
    switch(rand()%11){
        case 0:
            printf("l'ignoble ");
            break;
        case 1:
            printf("le terrible ");
            break;
        case 2:
            printf("le terrifiant ");
            break;
        case 3:
            printf("l'infame ");
            break;
        case 4:
            printf("le degoutant ");
            break;
        case 5:
            printf("le putride ");
            break;
        case 6:
            printf("le detestable ");
            break;
        case 7:
            printf("l'immoral ");
            break;
        case 8:
            printf("l'agressif ");
            break;
        case 9:
            printf("le malveillant ");
            break;
        case 10:
            printf("le cupide ");
            break;
    }
}
