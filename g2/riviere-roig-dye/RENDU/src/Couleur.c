#include "Couleur.h"

Couleur* initCouleur(){
    Couleur* coul = malloc(sizeof(Couleur));
    return coul;
}

Couleur* initCouleurAvecParam(int r, int g, int b) {
    Couleur* coul = initCouleur();
    setRCoul(r,coul);
    setGCoul(g,coul);
    setBCoul(b,coul);
    return coul;
}

void destroyCouleur(Couleur* coul) {
    free(coul);
    coul = NULL;
}

char* toCharCouleur(Couleur* coul) {
    char* chaine;
    chaine = malloc(20*sizeof(char));

    int rcoul = getRCoul(coul);
    int gcoul = getGCoul(coul);
    int bcoul = getBCoul(coul);

    sprintf(chaine,"%d-%d-%d",rcoul,gcoul,bcoul);

    return chaine;
}

// GETTERS
int getRCoul(Couleur* couleur){
    return couleur->rCoul;
}

int getGCoul(Couleur* couleur){
    return couleur->gCoul;
}

int getBCoul(Couleur* couleur){
    return couleur->bCoul;
}

// SETTERS
int setRCoul(int r,Couleur* couleur){
    int res = 0;
    if(r>=0 && r<=255) {
        couleur->rCoul = r;
        res = 1;
    }
    return res;
}

int setGCoul(int g,Couleur* couleur) {
    int res = 0;
    if(g>=0 && g<=255) {
        couleur->gCoul = g;
        res = 1;
    }
    return res;
}

int setBCoul(int b,Couleur* couleur) {
    int res = 0;
    if(b>=0 && b<=255) {
        couleur->bCoul = b;
        res = 1;
    }
    return res;
}
