#include "BDD.h"

// ---- CONSTANTES ---- //
const char* CHEMIN_ALIMENTS = "data/aliments.txt";
const char* CHEMIN_PESEES = "data/pesees.txt";
const char* CHEMIN_ALIMENTS_TEMP = "data/aliments.txt.tmp";
const char* CHEMIN_PESEES_TEMP = "data/pesees.txt.tmp";

const char* CHEMIN_IMAGES_ALIMENTS = "data/images_aliments/";

const char* ENTETE_ALIMENTS = "ID_ALIMENT;NOM_ALIMENT;COULEUR_ALIMENT;DUREE_PEREMPTION";
const char* ENTETE_PESEES = "ID_PESEE;QUANTITE_PESEE;DESCRIPTION_PESEE;DATE_PESEE;ID_ALIMENT_PESEE";

// ---- LECTURE ---- //
int nbLignesFichier(FILE* fichier) {
    int nbLignes = 0;
    char* a = NULL;
    a = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    while(fgets(a, TAILLE_MAX_LIGNE, fichier) != NULL) {
        nbLignes++;
    }
    fseek(fichier,0,0);
    return nbLignes;
}

char* lireLigne(FILE* fichier, int n) {
    char* res = NULL;
    res = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    int max = nbLignesFichier(fichier);
    // On cherche la ligne correspondante
    if (fichier && n <= max) {
        while(n>0) {
            fgets(res,TAILLE_MAX_LIGNE,fichier);
            n--;
        }
    }
    fseek(fichier,0,0);
    return res;
}

int getIdMax(char* type) {
    assert(type != NULL);
    const char* chemin = NULL;
    if (strcmp(type,"aliments") == 0) {
        chemin = CHEMIN_ALIMENTS;
    }
    else if (strcmp(type,"pesees") == 0) {
        chemin = CHEMIN_PESEES;
    }
    else {
        return -1;
    }
    FILE* fichier = fopen(chemin,"r+");
    assert(fichier != NULL);
    int nbLignes = nbLignesFichier(fichier);
    char* ligne = lireLigne(fichier,nbLignes);
    int idMax = atoi(strtok(ligne,";"));
    fseek(fichier,0,0);
    return idMax;
}

char* lireLigneParId(FILE* fichier, int id) {
    char* ligneLu = NULL;
    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    int idLu;
    int max = nbLignesFichier(fichier);
    fseek(fichier,0,0);

    // On cherche la ligne correspondante
    if (fichier) {
        int n = 1;
        fseek(fichier,0,0);
        while(n <= max && idLu != id) {
            ligneLu = lireLigne(fichier,n);
            idLu = atoi(strtok(lireLigne(fichier,n),";"));
            n++;
        }
    }

    fseek(fichier,0,0);
    return ligneLu;
}

// Lecture Aliments
int* getIdsAliments(int nbAliments){
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r");

    // On retourne 5 aliments maximum
    int nbAlimentsTotal = nbAliments;
    int nbAlimentsTrouves = 0;

    int* listeIds = NULL;
    listeIds = malloc(nbAlimentsTotal*sizeof(int));
    int i=0;
    // Initialisation des ids à 0
    for (i=0; i<nbAlimentsTotal ;i++) {
        listeIds[i]=0;
    }

    char* ligneLu = NULL;
    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));

    int idLu;

    // On lit le fichier à partir de la ligne 2 (premier tuple)
    i=2;
    while (i <= nbLignesFichier(fichier) && nbAlimentsTrouves < nbAlimentsTotal) {
        ligneLu = lireLigne(fichier,i);
        idLu = atoi(strtok(ligneLu,";"));
        nbAlimentsTrouves++;
        listeIds[nbAlimentsTrouves-1] = idLu;
        i++;
    }
    // Fin de boucle : tout le fichier est parcouru
    fclose(fichier);

    return listeIds;
}

char* getNomAliment(int id) {
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r");
    char* ligneLu = NULL;
    char* nomLu;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    nomLu = malloc(30*sizeof(char));

    ligneLu = lireLigneParId(fichier,id);

    strtok(ligneLu,";");        // id
    nomLu = strtok(NULL,";");   // nom
    fclose(fichier);
    return nomLu;
}

Couleur* getCouleurAliment(int id) {
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r");
    char* ligneLu = NULL;
    char* couleurLu;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneLu = lireLigneParId(fichier,id);
    fclose(fichier);

    strtok(ligneLu,";");    // id
    strtok(NULL,";");       // nom
    couleurLu = strtok(NULL,";");

    // Splitage de la couleur
    char* r = NULL;
    r = malloc(3*sizeof(char));
    char* g = NULL;
    g = malloc(3*sizeof(char));
    char* b = NULL;
    b = malloc(3*sizeof(char));

    r = strtok(couleurLu,"-");
    g = strtok(NULL,"-");
    b = strtok(NULL,"-");

    // Conversion char* en Couleur*
    Couleur* coul = initCouleur();
    setRCoul(atoi(r),coul);
    setGCoul(atoi(g),coul);
    setBCoul(atoi(b),coul);

    return coul;
}

int getDureePeremptionAliment(int id) {
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r");
    char* ligneLu = NULL;
    char* dureePchar;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneLu = lireLigneParId(fichier,id);
    fclose(fichier);

    strtok(ligneLu,";");    // id
    strtok(NULL,";");       // nom
    strtok(NULL,";");       // couleur
    dureePchar = strtok(NULL,";");

    // Conversion char* en int
    int dureeP;
    dureeP = atoi(dureePchar);

    return dureeP;
}

int* getIdAlimentParCouleur(Couleur* coul, int precision) {
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r");

    // On retourne 5 aliments maximum
    int nbAlimentsTotal = 5;
    int nbAlimentsTrouves = 0;

    int* listeIds = NULL;
    listeIds = malloc(nbAlimentsTotal*sizeof(int));
    int i=0;
    // Initialisation des ids à 0
    for (i=0; i<nbAlimentsTotal; i++) {
        listeIds[i]=0;
    }

    char* ligneLu = NULL;
    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));

    int idLu;

    Couleur* couleurLu = initCouleur();

    // Conversion HSL de la couleur passée en paramètre
    float rapRal = (float)getRCoul(coul)/255.0;
    float rapGal = (float)getGCoul(coul)/255.0;
    float rapBal = (float)getBCoul(coul)/255.0;

    float hAl; float sAl; float lAl;

    // Calcul Cmax
    float cMaxAl;
    if(rapRal > rapGal) {
        if(rapRal > rapBal) cMaxAl = rapRal;
        else cMaxAl = rapBal;
    }
    else {
        if(rapGal > rapBal) cMaxAl = rapGal;
    }

    // Calcul Cmin
    float cMinAl;
    if(rapRal < rapGal){
        if(rapRal < rapBal) cMinAl = rapRal;
        else cMinAl = rapBal;
    }
    else {
        if(rapGal < rapBal) cMinAl = rapGal;
    }

    float delta = cMaxAl - cMinAl;

    // Calcul H
    if(cMaxAl == rapRal) hAl = 60.0* ( (rapGal - rapBal)/delta );
    if(cMaxAl == rapGal) hAl = 60.0*( ( (rapBal - rapRal) /delta) + 2.0);
    if(cMaxAl == rapBal) hAl = 60.0*( ( (rapRal - rapGal) /delta) + 4.0);

    if(hAl < 0) hAl += 360;

    // Calcul L
    lAl = (cMaxAl + cMinAl) / 2.0;

    // Calcul S
    if (delta == 0) sAl = 0;
    else {
        float soust = 2*lAl-1;
        if (soust < 0) soust = -soust;
        sAl = delta / (1 - soust);
    }

    printf("\nHSL photo : %f %f %f", hAl,sAl,lAl);
    // On lit le fichier à partir de la ligne 2 (premier tuple)
    i=2;
    while (i <= nbLignesFichier(fichier) && nbAlimentsTrouves < nbAlimentsTotal) {
        ligneLu = lireLigne(fichier,i);
        idLu = atoi(strtok(ligneLu,";"));

        setRCoul(getRCoul(getCouleurAliment(idLu)),couleurLu);
        setGCoul(getGCoul(getCouleurAliment(idLu)),couleurLu);
        setBCoul(getBCoul(getCouleurAliment(idLu)),couleurLu);

        // On regarde si la couleur est proche de celle demandée (conversion en HSL)
        // Conversion HSL de la couleur passée en paramètre
        float rapRbdd = (float) (getRCoul(getCouleurAliment(idLu))/255.0);
        float rapGbdd = (float) (getGCoul(getCouleurAliment(idLu))/255.0);
        float rapBbdd = (float) (getBCoul(getCouleurAliment(idLu))/255.0);

        float hBdd; float sBdd; float lBdd;

        // Calcul Cmax
        float cMaxBdd;
        if(rapRbdd > rapGbdd) {
            if(rapRbdd > rapBbdd) cMaxBdd = rapRbdd;
            else cMaxBdd = rapBbdd;
        }
        else {
            if(rapGbdd > rapBbdd) cMaxBdd = rapGbdd;
        }

        // Calcul Cmin
        float cMinBdd;
        if(rapRbdd < rapGbdd){
            if(rapRbdd < rapBbdd) cMinBdd = rapRbdd;
            else cMinBdd = rapBbdd;
        }
        else {
            if(rapGbdd < rapBbdd) cMinBdd = rapGbdd;
        }

        float deltaB = cMaxBdd - cMinBdd;

        // Calcul H
        if(cMaxBdd == rapRbdd) hBdd = 60.0* ( (rapGbdd - rapBbdd)/deltaB );
        if(cMaxBdd == rapGbdd) hBdd = 60.0*( ( (rapBbdd - rapRbdd) / deltaB) + 2.0);
        if(cMaxBdd == rapBbdd) hBdd = 60.0*( ( (rapRbdd - rapGbdd) / deltaB) + 4.0);

        if(hBdd < 0) hBdd += 360;

        // Calcul L
        lBdd = (cMaxBdd + cMinBdd) / 2.0;

        // Calcul S
        if (deltaB == 0) sBdd = 0;
        else {
            float soustB = 2*lBdd-1;
            if (soustB < 0) soustB = -soustB;
            sBdd = deltaB / (1 - soustB);
        }

        // On regarde si la couleur est proche de celle demandée
        /*
        if (abs(getRCoul(couleurLu) - getRCoul(coul)) <= precision) {
            if (abs(getGCoul(couleurLu) - getGCoul(coul)) <= precision) {
                if (abs(getBCoul(couleurLu) - getBCoul(coul)) <= precision) {
                    nbAlimentsTrouves++;
                    listeIds[nbAlimentsTrouves-1] = idLu;
                }
            }
        }
        */

        float seuilH = 5;
        float seuilS = 0.20;
        float seuilL = 0.20;

        printf("\nHSL %s : %f %f %f",getNomAliment(idLu),hBdd,sBdd,lBdd);

        // Le H est cyclique
        float ecartH = abs(hAl - hBdd);
        if(360.0 - ecartH < 180.0) {
            ecartH = 360.0 - ecartH;
        }

        if (ecartH < seuilH) {
            if (abs(sAl - sBdd) < seuilS) {
                if (abs(lAl - lBdd) < seuilL) {
                    nbAlimentsTrouves++;
                    listeIds[nbAlimentsTrouves-1] = idLu;
                }
            }
        }


        i++;
    }
    // Fin de boucle : tout le fichier est parcouru
    fclose(fichier);

    return listeIds;
}

// Lecture Pesees
char* getQuantitePesee(int id) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r");
    char* ligneLu = NULL;
    char* quantiteLu;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneLu = lireLigneParId(fichier,id);

    strtok(ligneLu,";");            // id
    quantiteLu = strtok(NULL,";");  // quantite
    fclose(fichier);
    return quantiteLu;
}

char* getDescriptionPesee(int id) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r");
    char* ligneLu = NULL;
    char* descriptionLu;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneLu = lireLigneParId(fichier,id);

    strtok(ligneLu,";");    // id
    strtok(NULL,";");       // quantite
    descriptionLu = strtok(NULL,";");   // description
    fclose(fichier);
    return descriptionLu;
}

char* getDatePesee(int id) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r");
    char* ligneLu = NULL;
    char* dateLu;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneLu = lireLigneParId(fichier,id);
    strtok(ligneLu,";");    // id
    strtok(NULL,";");       // quantite
    strtok(NULL,";");       // description
    dateLu = strtok(NULL,";");   // date
    fclose(fichier);

    return dateLu;
}

char* getIdAlimentPesee(int id) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r");
    char* ligneLu = NULL;
    char* idAlimentLu;

    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneLu = lireLigneParId(fichier,id);

    strtok(ligneLu,";");    // id
    strtok(NULL,";");       // quantite
    strtok(NULL,";");       // description
    strtok(NULL,";");       // date
    idAlimentLu = strtok(NULL,";");   // id_aliment
    fclose(fichier);
    return strtok(idAlimentLu,"\n");
}

// ---- MODIFICATION ---- //
int setQuantitePesee(int id, int nouvQte) {
    // ouvrir fichier des pesees.
    FILE* fichier = fopen(CHEMIN_PESEES,"r");

    // modifie l'attribut quantite
    char* ligneModifiee = NULL;
    ligneModifiee = malloc(TAILLE_MAX_LIGNE*sizeof(char));

    char* idChar;
    idChar = malloc(sizeof(id));
    sprintf(idChar,"%d",id);

    ligneModifiee = idChar;
    strcat(ligneModifiee,";");

    char* nouvQteChar;
    nouvQteChar = malloc(sizeof(nouvQte));
    sprintf(nouvQteChar,"%d",nouvQte);

    strcat(ligneModifiee, nouvQteChar);
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,getDescriptionPesee(id));
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,getDatePesee(id));
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,getIdAlimentPesee(id));

    // recopier le fichier dans le temp
    FILE* fichierTemp = fopen(CHEMIN_PESEES_TEMP,"a");

    char* ligneLue = NULL;
    ligneLue = malloc(TAILLE_MAX_LIGNE*sizeof(char));

    char* ligneRef = lireLigneParId(fichier,id);

    while(fgets(ligneLue,TAILLE_MAX_LIGNE, fichier) != NULL) {
        if(strcmp(ligneLue,ligneRef) != 0) {
            fprintf(fichierTemp,"%s",ligneLue);
        }
        else {
            fprintf(fichierTemp,"%s",ligneModifiee);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    int res = 1;
    if(remove(CHEMIN_PESEES) != 0 || rename(CHEMIN_PESEES_TEMP,CHEMIN_PESEES) != 0) {
        res = 0;
    }
    return res;

}

int setDatePesee(int id, char* nouvDate) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r");

    char* ligneModifiee = NULL;
    ligneModifiee = malloc(TAILLE_MAX_LIGNE*sizeof(char));

    char* idChar;
    idChar = malloc(sizeof(id));
    sprintf(idChar, "%d",id);

    ligneModifiee = idChar;
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,getQuantitePesee(id));
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,getDescriptionPesee(id));
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,nouvDate);
    strcat(ligneModifiee,";");

    strcat(ligneModifiee,getIdAlimentPesee(id));

    // recopier le fichier dans le temp
    FILE* fichierTemp = fopen(CHEMIN_PESEES_TEMP,"a");

    char* ligneLue = NULL;
    ligneLue = malloc(TAILLE_MAX_LIGNE*sizeof(char));

    char* ligneRef = lireLigneParId(fichier,id);

    while(fgets(ligneLue,TAILLE_MAX_LIGNE, fichier) != NULL) {
        if(strcmp(ligneLue,ligneRef) != 0) {
            fprintf(fichierTemp,"%s",ligneLue);
        }
        else {
            fprintf(fichierTemp,"%s",ligneModifiee);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    int res = 1;
    if(remove(CHEMIN_PESEES) != 0 || rename(CHEMIN_PESEES_TEMP,CHEMIN_PESEES) != 0) {
        res = 0;
    }
    return res;

}

// ---- ECRITURE ---- //
int ecrireDonneeAliment(char* nom, Couleur* couleur, int dureeP) {
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r+");
    assert(fichier != NULL);
    fseek(fichier,0,SEEK_END);

    char buffer[TAILLE_MAX_LIGNE] = "\n";

    // Obtention de l'id du nouvel aliment
    int id = getIdMax("aliments") + 1;
    char *idchar = NULL;
    idchar = malloc(10*sizeof(char));
    sprintf(idchar,"%d",id);

    // Cast dureeP en char*
    char *dureePchar = NULL;
    dureePchar = malloc(3*sizeof(dureeP));
    sprintf(dureePchar,"%d",dureeP);

    // Construction du tuple
    strcat(buffer,idchar);
    strcat(buffer,";");
    strcat(buffer,nom);
    strcat(buffer,";");
    strcat(buffer,toCharCouleur(couleur));
    strcat(buffer,";");
    strcat(buffer,dureePchar);

    fprintf(fichier,"%s",buffer);
    fclose(fichier);
    return 1;
}

int ecrireDonneePesee(int quantite,char* description,int id_aliment) {
    FILE* fichier = fopen(CHEMIN_PESEES,"r+");

    // Contrôles
    assert(fichier != NULL);

    // Saut de ligne avant insertion et formatage des données
    char buffer[TAILLE_MAX_LIGNE]="\n";

    // Obtention de l'id de la nouvelle pesée
    int id = getIdMax("pesees") + 1;
    fseek(fichier,0,SEEK_END);
    char *idchar = NULL;
    idchar = malloc(10*sizeof(char));
    sprintf(idchar,"%d",id);

    // Conversion des données int en char
    char *quantite_char = NULL;
    quantite_char = malloc(100*sizeof(char));
    char *id_aliment_char = NULL;
    id_aliment_char = malloc(10*sizeof(char));
    sprintf(quantite_char,"%d",quantite);
    sprintf(id_aliment_char,"%d",id_aliment);

    // Ecriture dans le fichier (+ conversion des NULL en " ")
    strcat(buffer,idchar);
    strcat(buffer,";");

    if (strcmp(quantite_char,"") == 0) {
         strcat(buffer," ");
    }
    else {
         strcat(buffer,quantite_char);
    }
    strcat(buffer,";");

    if (strcmp(description,"") == 0) {
         strcat(buffer," ");
    }
    else {
         strcat(buffer,description);
    }

    strcat(buffer,";");

    // Date au moment de l'enregistrement (en secondes depuis 1er janvier 1970)
    long int date = (long int)time(NULL);
    char* dateStr = malloc(12*sizeof(int));
    sprintf(dateStr,"%ld",date);
    strcat(buffer,dateStr);

    strcat(buffer,";");
    strcat(buffer,id_aliment_char);

    fprintf(fichier,"%s",buffer);
    fclose(fichier);
    return 1;
}

// ---- SUPPRESSION ---- //
int supprimerDonneeAliment(int id){
    FILE* fichier = fopen(CHEMIN_ALIMENTS,"r+");

    // Obtention ligne à Supprimer
    char* ligneASupprimer = NULL;
    ligneASupprimer = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneASupprimer = lireLigneParId(fichier,id);

    FILE* fichierTemp = fopen(CHEMIN_ALIMENTS_TEMP,"a");

    // Recopie du fichier dans le fichier .tmp sauf la ligne à supprimer
    char* ligneLu = NULL;
    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    while(fgets(ligneLu, TAILLE_MAX_LIGNE, fichier) != NULL) {
        if(strcmp(ligneLu,ligneASupprimer) != 0) {
            fprintf(fichierTemp,"%s",ligneLu);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    int res = 1;
    if(remove(CHEMIN_ALIMENTS) != 0 || rename(CHEMIN_ALIMENTS_TEMP,CHEMIN_ALIMENTS) != 0) {
        res = 0;
    }
    return res;
}

int supprimerDonneePesee(int id){
    FILE* fichier = fopen(CHEMIN_PESEES,"r+");

    // Obtention ligne à Supprimer
    char* ligneASupprimer = NULL;
    ligneASupprimer = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    ligneASupprimer = lireLigneParId(fichier,id);

    FILE* fichierTemp = fopen(CHEMIN_PESEES_TEMP,"a");


    // Recopie du fichier dans le fichier .tmp sauf la ligne à supprimer
    char* ligneLu = NULL;
    ligneLu = malloc(TAILLE_MAX_LIGNE*sizeof(char));
    while(fgets(ligneLu, TAILLE_MAX_LIGNE, fichier) != NULL) {
        if(strcmp(ligneLu,ligneASupprimer)) {
            fprintf(fichierTemp,"%s",ligneLu);
        }
    }

    fclose(fichier);
    fclose(fichierTemp);

    int res = 1;
    if(remove(CHEMIN_PESEES) != 0 || rename(CHEMIN_PESEES_TEMP,CHEMIN_PESEES) != 0) {
        res = 0;
    }
    return res;
}

void reinitBDD() {
    FILE* fichierTempPesees = fopen(CHEMIN_PESEES_TEMP,"a");
    fprintf(fichierTempPesees,"%s",ENTETE_PESEES);

    if(remove(CHEMIN_PESEES) != 0 || rename(CHEMIN_PESEES_TEMP,CHEMIN_PESEES) != 0) {
        printf("\nErreur reinit pesees.txt.");
    }
    fclose(fichierTempPesees);

    FILE* fichierTempAliments = fopen(CHEMIN_ALIMENTS_TEMP,"a");
    fprintf(fichierTempAliments,"%s",ENTETE_ALIMENTS);

    if(remove(CHEMIN_ALIMENTS) != 0) {
        printf("\nErreur suppression aliments.txt.");
    }

    if(rename(CHEMIN_ALIMENTS_TEMP,CHEMIN_ALIMENTS) != 0) {
        printf("\nErreur rename aliments.txt.");
    }
    fclose(fichierTempAliments);
}
