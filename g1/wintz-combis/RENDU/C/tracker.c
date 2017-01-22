#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define pi 3.14159265358979323846

int envoyer_donnee(char result[6][100]){
  /*On construit la chaine de caractère pour l'utiliser en ligne de commande */
  char *commandLine = "curl --data \"action=SEND_POS&user=Lolo&lat=";
  char lat[30];
  char lng[30];
  strcat(commandLine,result[2]);
  strcat(commandLine,"&lng=");
  strcat(commandLine,result[4]);
  strcat(commandLine,"&date=");
  strcat(commandLine,result[0]);
  strcat(commandLine,"\" http://www.wintz-combis.16mb.com/Application_Web/controleur/controleur-carte.php");

  //on envoi la requete POST sur le serveur.
  system(commandLine);
  return 0;
}

int parserLigne(char *ligne, char result[6][100]){
  /**
  * Sépare la chaine lu dans le fichier /dev/ttyAMA0
  * et met chaque partie das un tableau de chaine de caractères
  **/

  int i=6;
  int j =0;
  int compteVirgule = 0;

   while (compteVirgule<6){
     i++;
     int j = 0;
      while (ligne[i] != ',') {
          result[compteVirgule][j] = ligne[i];
          i++;
          j++;
      }
      result[compteVirgule][j] ='\0';
      compteVirgule++;
  }
  int longueur = 0;
  longueur = strlen(result[0]);
  result[0][6] = '\0';
  /**
  * Conversion de la lat On sépare le string en 2
  **/
  char lat1[3];
  int longLat = 0;
  longLat = strlen(result[2]);
  int l = 0;
  while (l<2) {
    lat1[l] = result[2][l];
    l++;
  }
  char lat2[10];
  while (l<longLat) {
    lat2[l] = result[2][l];
    l++;
  }
  float lat;
  lat = (float)*lat1+*lat2/60;
  return 0;
}

/**
* Fonctions de conversion de coordonnées et de calcul de distance
**/
double deg2rad(double deg) {
  return (deg * pi / 180);
}

double rad2deg(double rad) {
  return (rad * 180 / pi);
}

int distance(char* latitude,char* longitude,double prec){
  /**
  * Fonction qui converti lat et lng en coordonnées degrés décimaux, calcule la distance au point d'arrivée.
  * et la compare à prec
  **/

  int res;
  /**
  * Conversion en degrés décimaux
  **/
  double lat = atof(latitude);
  lat = (lat/100) + (lat - lat/100)/60;
  double lng = atof(longitude);
  lng = (lng/100) + (lng - lng/100)/60;

  double theta, dist;
  theta = lng - 4.35;
  /**
  * Formule de calcul de la distance avec les coordonnées GPS de 2 points
  **/
  dist = sin(deg2rad(lat)) * sin(deg2rad( 43.833328)) + cos(deg2rad(lat)) * cos(deg2rad(43.833328)) * cos(deg2rad(theta));
  dist = acos(dist);
  dist = rad2deg(dist);
  dist = dist * 60 * 1.1515;
  dist = dist * 1.609344;

  /**
  * Comparaison et renvoie du réslultat
  **/
  if (dist > prec) {
    res = 1;
  }
  else { res = 0;}
  prec = dist;
  return res;
}


int main() {
  /**
  * Boucle principale. Le processus recommence tant que le Raspberry
  *  est allumé ou que le programme n'est pas arrêté
  **/

  /**
  * n est un incrément pour trouver la bonne ligne dans le fichier /dev/ttyAMA0
  **/
  int n = 0;
  /**
  * point est un double contenant la distance du point précédent envoyé sur le serveur par rapport au point d'arrivée.
  **/
  double prec = -1.0;

  while (1){
    /**
    * D'abord on lit les données envoyées par le GPS dans le fichier /dev/ttyAMA0
    **/
    FILE* fichier;
    int i;
    char chaine[100];
    fichier  = fopen("/dev/ttyAMA0","r");
    /**
    * On teste le résultat de l'ouverture du fichier
    **/
    if(fichier != NULL){

        while (i<=n){
          /**
          * On cherche la n-ième ligne qui commence par $GPRMC
          **/
          fgets(chaine,100,fichier);
          if (chaine[0] == '$' && chaine[1] == 'G' && chaine[2] == 'P' && chaine[3] == 'R' && chaine[4] == 'M' && chaine [5] == 'C'){
            if(i == n){
              n = n+1;
              /**
              * On a récupéré la bonne ligne on va donc la parser
              **/
              char result[6][100];
              parserLigne(chaine,result);
              /**
              * On a parsé la chaine et mis le résultat dans res, il nous reste plus qu'a envoyer les données sur le serveur.
              **/
              envoyer_donnee(result);
              /**
              * Il ne nous reste qu'à calculer la distance par rapport au point d'arrivée.
              **/
              int dist = distance(result[2],result[4],prec);
              if(dist = 1){
                system("python python/grove_buzzer.py");
              }
            }
            else{
              i = i+1;
            }
          }
        }
      fclose(fichier);
    }
  }
  return 0;
}
