#ifndef DEF_ImageBMP
#define DEF_ImageBMP

// EN-TETE ImageBMP.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Couleur.h"

// ---- CONSTANTES ---- //

// ---- STRUCTURE ---- //
/** @struct ImageBMP
 *  @brief Structure définissant une image au format Bitmap
 *  @var Couleur** couleurs, l'image représentée par un tableau de pixels R-G-B (objet Couleur)
 *  @var int taille_image, la taille de l'image (sans l'en-tête)
 *  @var int taille_fichier, la taille totale du fichier
 *  @var unsigned char* entete, l'en-tête du fichier bitmap
 */
typedef struct ImageBMP {
    Couleur** couleurs;
    int taille_image;
    int taille_fichier;
    int largeur;
    int hauteur;
    unsigned char* entete;
} ImageBMP;

// ---- FONCTIONS ---- //

/**
	@brief Constructeur de ImageBMP
	@param FILE* fichier, le fichier .bmp que l'on veut transformer en ImageBMP
	@return ImageBMP*
*/
ImageBMP* initImageBMP(FILE* fichier);

/**
	@brief Destructeur de ImageBMP (libère mémoire)
	@param ImageBMP* image, l'image à détruire
*/
void destroyImageBMP(ImageBMP* image);

// Affichage de l'imageBMP
/**
	@brief Transforme la structure imageBMP en une chaine de caractères
	@param ImageBMP* image
	@return char*, les caractéristiques de l'image
*/
char* toCharImageBMP(ImageBMP* image);

// STRUCTURE D'UN FICHIER BITMAP : http://sitelec.org/cours/abati/bmp.htm
/**
	@brief Récupère l'en-tête d'un fichier .bmp
	@param FILE* image, l'image à charger
	@return un tableau de char contenant l'en-tête du fichier
*/
unsigned char* getEnTete(FILE* image);

/**
	@brief Renseigne sur la largeur de l'image
	@param FILE* image, l'image à analyser
	@return int, la largeur de l'image (en pxl)
*/
int getLargeurBMP(FILE* image);

/**
	@brief Renseigne sur la hauteur de l'image
	@param FILE* image, l'image à analyser
	@return int, la hauteur de l'image (en pxl)
*/
int getHauteurBMP(FILE* image);

/**
	@brief Retourne la taille de l'image
	@param FILE* image, l'image à analyser
	@return long, la taille de l'image
*/
long getTailleImage(FILE* image);

/**
	@brief Retourne la taille du fichier BMP
	@param FILE* image, l'image à analyser
	@return long, la taille du fichier BMP
*/
long getTailleFichier(FILE* image);

/**
	@brief Charge les données d'une image BITMAP (.bmp) dans un tableau de Couleurs
	@param FILE* image, l'image à charger
	@return Couleur**, un tableau de Couleur* représentant l'image pixel par pixel
*/
Couleur** getDonnees(FILE* image);

#endif
