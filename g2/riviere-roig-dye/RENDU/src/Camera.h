#ifndef DEF_Camera
#define DEF_Camera

// EN-TETE Camera.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "BDD.h"

// ---- FONCTIONS ---- //

/**
	@brief Prend une photo
    @param char* idPesee, l'id de la pesée qui donnera son nom à la photo
	@return bool, 1 si la prise de photo s'est bien passée, 0 sinon
*/
int prendrePhoto(char* idPesee);

#endif
