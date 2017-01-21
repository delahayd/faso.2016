#ifndef DEF_BDD
#define DEF_BDD

// EN-TETE BDD.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#include "Couleur.h"

// ---- CONSTANTES ---- //
const char* CHEMIN_ALIMENTS;
const char* CHEMIN_PESEES;
const char* CHEMIN_ALIMENTS_TEMP;
const char* CHEMIN_PESEES_TEMP;

const char* CHEMIN_IMAGES_ALIMENTS;

const char* ENTETE_ALIMENTS;
const char* ENTETE_PESEES;
#define TAILLE_MAX_LIGNE 300

// ---- FONCTIONS ---- //

// ---- Lecture ---- //
/**
    @brief renvoie le nombre de lignes que contient un fichier
    @param FILE* fichier, le fichier à analyser
    @return int, le nombre de lignes du fichier
*/
int nbLignesFichier(FILE* fichier);

/**
    @brief renvoie la ligne du fichier pointé
    @param FILE*, fichier le fichier que l'on souhaite lire
    @param int n, le numéro de la ligne que l'on souhaite lire
    @return char*, la ligne issue du fichier
*/
char* lireLigne(FILE* fichier, int n);

/**
    @brief renvoie l'id maximum contenu dans le fichier aliments.txt ou pesees.txt
    @param char* type, le nom du fichier dont on souhaite connaître l'idMax (aliments ou pesees)
    @return int, l'id maximum utilisé dans le fichier analysé
*/
int getIdMax(char* type);

/**
    @brief renvoie le tuple sans l'id du fichier spécifié
    @param FILE* fichier, le fichier dont on veut extraire une ligne
    @param int id, l'id du tuple que l'on souhaite obtenir
    @return char*, le tuple complet sans l'id spécifié extrait du fichier
*/
char* lireLigneParId(FILE* fichier, int id);

// ALIMENTS
/**
    @brief renvoie le nom de l'aliment ciblé par l'id
    @param int id, l'id de l'aliment ciblé
    @return char*, le nom de l'aliment
*/
char* getNomAliment(int id);

/**
    @brief renvoie la couleur de l'aliment ciblé par l'id
    @param int id, l'id de l'aliment
    @return char*, la couleur de l'aliment (format r-g-b)
*/
Couleur* getCouleurAliment(int id);

/**
    @brief renvoie la durée de péremption de l'aliment ciblé par l'id
    @param int id, l'id de l'aliment
    @return int, la durée de péremption de l'aliment
*/
int getDureePeremptionAliment(int id);

/**
    @brief renvoie la liste des id des aliments (id1;id2;id3...) qui ont une couleur proche de la couleur spécifiée
    @param Couleur* coul, la couleur dont on cherche des aliments
    @param int, precision sur la couleur (pour la couleur 50-50-50, une precision de 10 cherche toutes les couleurs entre 40-40-40 et 60-60-60)
    @return int*, la liste des ids des aliments une couleur proche de celle spécifiée (5 aliments retournés, avec des id=0 si pas trouvé)
*/
int* getIdAlimentParCouleur(Couleur* coul,int precision);

// PESEES
/**
    @brief renvoie la quantite de la pesee ciblée par l'id
    @param int id, l'id de la pesee
    @return char*, la quantite pesee
*/
char* getQuantitePesee(int id);

/**
    @brief renvoie la description de la pesee ciblée par l'id
    @param int id, l'id de la pesee
    @return char*, la description de la pesee
*/
char* getDescriptionPesee(int id);

/**
    @brief renvoie la date de la pesee ciblée par l'id
    @param int id, l'id de la pesee
    @return char*, la date de la pesee (nb de sec depuis le 1er janvier 1970)
*/
char* getDatePesee(int id);

/**
    @brief renvoie l'id de l'aliment de la pesee ciblée par l'id
    @param int id, l'id de la pesee
    @return char*, l'id de l'aliment pesee
*/
char* getIdAlimentPesee(int id);

// ----- Modification ---- //
/**
    @brief Permet de modifier la quantité d'un aliment pesé
    @param int id, le numero id de l'aliment dont on veut changer la quantité
    @param int nouvQte, la nouvelle quantité de l'aliment
    @return bool, 1 si modification ok, sinon 0
*/
int setQuantitePesee(int id, int nouvQte);

/**
    @brief Permet de modifier la date d'enregistrement d'un aliment pesé
    @param int id, le numero id de l'aliment dont on veut changer la date d'enregistrement
    @return bool, 1 si modification ok, sinon 0
*/
int setDatePesee(int id, char* nouvDate);

// ----- Ecriture ---- //
/**
    @brief écrit un tuple aliment (ID / NOM / COULEUR)
    @param char* nom, le nom de l'aliment
    @param Couleur* couleur, la couleur de l'aliment (format : R-G-B)
    @param int dureeP, la durée de péremption moyenne de l'aliment
    @return bool, 1 si écriture ok, sinon 0
*/
int ecrireDonneeAliment(char* nom, Couleur* couleur, int dureeP);

/**
    @brief écrit un tuple pesee dans la BDD. La date enregistrée est la date courante
    @param int quantite, la quantité d'aliment pesée
    @param char* description, la description de la pesée
    @param int id_aliment, l'id de l'aliment pesé
    @return bool, 1 si écriture ok, sinon 0
*/
int ecrireDonneePesee(int quantite, char* description, int id_aliment);

// ----- Suppression ---- //
/**
    @brief supprime le tuple Aliment spécifié par l'id
    @param int id, l'id du tuple aliment à supprimer
    @return bool, 1 si suppression ok, sinon 0
*/
int supprimerDonneeAliment(int id);

/**
    @brief supprime le tuple Pesée spécifié par l'id
    @param int id, l'id du tuple pesée à supprimer
    @return bool, 1 si suppression ok, sinon 0
*/
int supprimerDonneePesee(int id);

/**
    @brief supprime toutes les entrées de pesees.txt et aliments.txt
*/
void reinitBDD();

#endif
