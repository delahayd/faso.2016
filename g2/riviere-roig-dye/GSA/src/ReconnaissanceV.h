#ifndef DEF_ReconnaissanceV
#define DEF_ReconnaissanceV

// EN-TETE ReconnaissanceV.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Couleur.h"
#include "BDD.h"
#include "ImageBMP.h"

// ---- CONSTANTES ---- //

// Ces constanctes sont utilisées par plusieurs fonctions comme "seuil" de détection des couleurs
const int PRECISION_COULEUR_FOND_UNI;
const int PRECISION_COULEUR_HORS_FOND;
const int PRECISION_COULEUR_RECHERCHE_ALIMENT;

// ---- FONCTIONS ---- //

/**
	@brief Teste si la couleur de fond est clairement discernable ou pas
	@param ImageBMP* image, l'image que l'on souhaite analyser
	@return int, 1 (True) si une couleur de fond a été repérée, sinon 0 (False)
*/
int estUni(ImageBMP* image);

/**
	@brief Renvoie la couleur dominante de l'image (moyenne des 3 composantes RGB)
	@param ImageBMP* image, l'image que l'on souhaite analyser
	@return Couleur* , la couleur dominante de l'image
*/
Couleur* couleurDominante(ImageBMP* image);

/**
	@brief Renvoie la couleur dominante de l'image (moyenne des 3 composantes RGB), sans tenir compte de la couleur du fond
	@param ImageBMP* image, l'image que l'on souhaite analyser
	@param Couleur* couleurFond, la couleur du fond de l'image
	@return Couleur*, la couleur dominante de l'image, sans prendre en compte le fond
*/
Couleur* couleurDominanteHorsFond(ImageBMP* image, Couleur* couleurFond);

/**
    @brief Renseigne sur la présence (ou non) d'au moins un aliment ayant une couleur proche du paramètre
	@param Couleur* coul, la couleur que l'on souhaite utiliser pour chercher des aliments
	@return int, 1 (True) s'il existe au moins un aliment proche de la couleur, 0 (False)
*/
int rechercheAliment(Couleur* coul);

#endif
