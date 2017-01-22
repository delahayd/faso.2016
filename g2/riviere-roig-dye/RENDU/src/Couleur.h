#ifndef DEF_Couleur
#define DEF_Couleur

// EN-TETE Couleur.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// ---- CONSTANTES ---- //

// ---- STRUCTURE ---- //
/** @struct Couleur
 *  @brief Structure definissant une couleur au format R-G-B
 *  @var Couleur::rCoul
 *  Valeur de Rouge (compris entre 0 et 255)
 *  @var Couleur::gCoul
 *  Valeur de Vert (compris entre 0 et 255)
 *  @var Couleur::bCoul
 *  Valeur de Bleu (compris entre 0 et 255)
 */
typedef struct Couleur {
    int rCoul;
    int gCoul;
    int bCoul;
} Couleur;

// ---- FONCTIONS ---- //

// Init + destroy
/**
	@brief Constructeur de Couleur (sans paramètres)
	@return Couleur *
*/
Couleur* initCouleur();

/**
	@brief Constructeur de Couleur (avec paramètres)
	@param int r, la valeur de rouge de la couleur
	@param int g, la valeur de bleu de la couleur
	@param int b, la valeur de vert de la couleur
	@return Couleur *
*/
Couleur* initCouleurAvecParam();

/**
	@brief Destructeur de Couleur (lib�re la m�moire)
	@param Couleur* coul, la couleur � d�truire
*/
void destroyCouleur(Couleur* coul);

// Print
/**
	@brief Transforme la couleur en chaine de caract�res
	@param Couleur* coul
	@return char*, la couleur en chaine de caract�res ("42-255-0")
*/
char* toCharCouleur(Couleur* coul);

//Getters
/**
	@brief Recup�re rCoul d'une Couleur
	@param Couleur* couleur, la couleur � lire
	@return int rCoul, la valeur de rouge de la Couleur
*/
int getRCoul(Couleur* couleur);

/**
	@brief Recup�re gCoul d'une Couleur
	@param Couleur* couleur, la couleur � lire
	@return int gCoul, la valeur de rouge de la Couleur
*/
int getGCoul(Couleur* couleur);

/**
	@brief Recup�re bCoul d'une Couleur
	@param Couleur* couleur, la couleur � lire
	@return int bCoul, la valeur de rouge de la Couleur
*/
int getBCoul(Couleur* couleur);

// Setters
/**
	@brief Edition de rCoul dans la structure
	@param int r, la valeur de rouge � setter (compris entre 0 et 255)
	@param Couleur* couleur, la couleur � modifier
	@return int, 1 si 0 <= r <= 255 sinon
*/
int setRCoul(int r,Couleur* couleur);

/**
	@brief Edition de gCoul dans la structure
	@param int g, la valeur de vert � setter (compris entre 0 et 255)
	@param Couleur* couleur, la couleur � modifier
	@return int, 1 si 0 <= g <= 255 sinon
*/
int setGCoul(int g,Couleur* couleur);

/**
	@brief Edition de bCoul dans la structure
	@param int b, la valeur de bleu � setter (compris entre 0 et 255)
	@param Couleur* couleur la couleur � modifier
	@return int, 1 si 0 <= b <= 255 sinon
*/
int setBCoul(int b,Couleur* couleur);

#endif
