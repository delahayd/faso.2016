#include <SDL2/SDL.h>
#include <stdio.h>
#include "ReconnaissanceV.h"
#include "Stock.h"
#include "Camera.h"
#include "Sdl_init.h"

// ---- CONSTANTES ---- //
const char* CHEMIN_PHOTO_FOND;
const char* CHEMIN_PHOTO_ALIMENT;

/**
	@brief Modifie le rendu pour le menu de choix d'action
	@return 1 si on doit aller au menu, 2 si à la peser, 3 si au stock, 0 pour quitter
*/
int menu();

/**
	@brief Modifie le rendu pour la page de pesee
	@return 1 si on doit aller au menu, 2 si à la peser, 3 si au stock, 0 pour quitter
*/
int peser();

/**
	@brief Modifie le rendu pour la page des stocks
	@return 1 si on doit aller au menu, 2 si à la peser, 3 si au stock, 0 pour quitter
*/
int stock();

/**
	@brief Convertie une durée en heure en un rapport en % sur deux semaines
	@param int duree Une durée exprimé en heure
	@return int un pourcentage sous forme d'un int compris entre 0 et 100
*/
int rapport14J(int duree);
