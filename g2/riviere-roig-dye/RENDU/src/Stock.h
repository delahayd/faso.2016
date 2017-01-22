#ifndef DEF_Stock
#define DEF_Stock

// EN-TETE Stock.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "BDD.h"


// ---- CONSTANTES ---- //

// ---- Outils ---- //

// ---- FONCTIONS ---- //

/**
    @brief renvoie le tableau des ids de pesées ordonné par leur durée avant Peremption (en secondes).
    Si limite est supérieur au nombre de pesées, on renvoie toutes les pesées ordonnées.
    @param int limite, le nombre d'id d'aliments à charger
    @return long int**, le tableau [id de la pesée => durée avant Péremption]
*/
long int** getTabIdDureeAvantPer(int limite);


#endif
