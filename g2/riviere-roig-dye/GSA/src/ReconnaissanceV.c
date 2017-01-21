#include "ReconnaissanceV.h"

// ---- CONSTANTES ---- //
const int PRECISION_COULEUR_FOND_UNI = 50;
const int PRECISION_COULEUR_HORS_FOND = 180;
const int PRECISION_COULEUR_RECHERCHE_ALIMENT = 10;

// ---- FONCTIONS ---- //

// Fonction racine carré rapide
float fast_sqrtf(float number) {
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = * ( long * ) &y;         // evil floating point bit level hacking
	i = 0x5f3759df - ( i >> 1 ); // what the fuck?
	y = * ( float * ) &i;
	y = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
    y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration

	return 1/y;
}
// -----------------------------------

int estUni(ImageBMP* image) {
    int res = 0;

    // On récupère la couleur moyenne de l'image
    Couleur* coulDominante = couleurDominante(image);
    int moyenneR = getRCoul(coulDominante);
    int moyenneG = getGCoul(coulDominante);
    int moyenneB = getBCoul(coulDominante);

    // Calcul des variances / écarts-type
    float varR = 0;
    float varG = 0;
    float varB = 0;

    int i;
    for(i=0; i < (image->hauteur * image->largeur) ; i++) {
        varR = varR + (getRCoul(image->couleurs[i]) - moyenneR) * (getRCoul(image->couleurs[i]) - moyenneR);
        varG = varG + (getGCoul(image->couleurs[i]) - moyenneG) * (getGCoul(image->couleurs[i]) - moyenneG);
        varB = varB + (getBCoul(image->couleurs[i]) - moyenneB) * (getBCoul(image->couleurs[i]) - moyenneB);
    }

    varR = varR / (image->hauteur * image->largeur);
    varG = varG / (image->hauteur * image->largeur);
    varB = varB / (image->hauteur * image->largeur);

    float ecarR = fast_sqrtf(varR);
    float ecarG = fast_sqrtf(varG);
    float ecarB = fast_sqrtf(varB);

    // Condition sur l'écart-type (à ajuster)
    if (ecarR + ecarG + ecarB < PRECISION_COULEUR_FOND_UNI) {
        res = 1;
    }

    return res;
}

Couleur* couleurDominante(ImageBMP* image) {
    // Calcul des moyennes pour chaque composante
    float moyenneR = 0;
    float moyenneG = 0;
    float moyenneB = 0;

    int i;
    for(i=0; i < (image->hauteur * image->largeur) ; i++) {
        moyenneR += getRCoul(image->couleurs[i]);
        moyenneG += getGCoul(image->couleurs[i]);
        moyenneB += getBCoul(image->couleurs[i]);
    }

    moyenneR = moyenneR / (image->hauteur * image->largeur);
    moyenneG = moyenneG / (image->hauteur * image->largeur);
    moyenneB = moyenneB / (image->hauteur * image->largeur);

    Couleur* coulDominante = initCouleur();
    setRCoul((int)moyenneR,coulDominante);
    setGCoul((int)moyenneG,coulDominante);
    setBCoul((int)moyenneB,coulDominante);

    return coulDominante;
}

Couleur* couleurDominanteHorsFond(ImageBMP* image, Couleur* couleurFond) {
    // Initialisation moyenneRGB de l'aliment
    float moyenneRAliment = 0;
    float moyenneGAliment = 0;
    float moyenneBAliment = 0;

    // Récupère les composantes RGB du pixel analysé
    int valeurRPixel;
    int valeurGPixel;
    int valeurBPixel;

    // Compte le nb de pixels composants l'aliment
    int cptPixelsAliment = 0;

    // Stocke la différence entre la valeurPixel et PRECISION_COULEUR_HORS_FOND
    int diffR;
    int diffG;
    int diffB;

    int i;
    for(i=0; i < (image->hauteur * image->largeur) ; i++) {
        valeurRPixel = getRCoul(image->couleurs[i]);
        valeurGPixel = getGCoul(image->couleurs[i]);
        valeurBPixel = getBCoul(image->couleurs[i]);

        // Différence entre pixel et fond
        diffR = valeurRPixel - getRCoul(couleurFond);
        diffG = valeurGPixel - getGCoul(couleurFond);
        diffB = valeurBPixel - getBCoul(couleurFond);

        // Valeur absolue
        if(diffR < 0) {
            diffR = -diffR;
        }
        if(diffG < 0) {
            diffG = -diffG;
        }
        if(diffB < 0) {
            diffB = -diffB;
        }

        // Si la somme des différences est supérieur au seuil, alors ce sont des pixels de l'aliment.
        if (diffR + diffG + diffB > PRECISION_COULEUR_HORS_FOND) {
            moyenneRAliment += valeurRPixel;
            moyenneGAliment += valeurGPixel;
            moyenneBAliment += valeurBPixel;
            cptPixelsAliment ++;
        }
    }

    // Calcul des moyennes pour chaque composante des pixels de l'aliment
    if(cptPixelsAliment != 0) {
        moyenneRAliment = moyenneRAliment / cptPixelsAliment;
        moyenneGAliment = moyenneGAliment / cptPixelsAliment;
        moyenneBAliment = moyenneBAliment / cptPixelsAliment;
    }

    Couleur* coulDominanteAliment = initCouleur();
    setRCoul((int)moyenneRAliment,coulDominanteAliment);
    setGCoul((int)moyenneGAliment,coulDominanteAliment);
    setBCoul((int)moyenneBAliment,coulDominanteAliment);

    return coulDominanteAliment;
}

int rechercheAliment(Couleur* coul) {
    int res = 0;
    int* listeAlim = getIdAlimentParCouleur(coul,PRECISION_COULEUR_RECHERCHE_ALIMENT);
    if(listeAlim != NULL){
        res = 1;
    }
    return res;
}
