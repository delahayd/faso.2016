#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// http://paristech.institutoptique.fr/site.php?id=469&fileid=2739

// Permet de récupèrer les données d'un fichier texte où sont stocker les coords GPS
// Une fois le texte récupérer, on la supprime du fichier.
void main() {
  //Lance le programme pyhton qui recupère les données GPS et les ecrits dans le fichier texte
  system("python ../Python/GPS.py");
  //On Récupère en C les données inscrites dans le fichier
  int i;
  double tab[2];
  FILE *fichier;

  fichier = fopen("coordGPS.txt", "r");
  if (fichier != NULL) {
    for (i=0; i<2; i++) {
      fscanf(fichier, "%lf\n", tab+i);
    }
    fclose(fichier);
  }
  /*On construit la chaine de caractère pour l'utiliser en ligne de commande */
  char commandLine[43] = "curl --data \"action=SEND_POS&user=Lolo&lat=";
  char lat[15];
  char lng[15];
  sprintf(lat,"%lf",tab[0]);
  sprintf(lng,"%lf",tab[1]);
  strcat(commandLine,lat);
  strcat(commandLine,"&lng=");
  strcat(commandLine,lng);
  char date[5] = "today";
  strcat(commandLine,"&date=");
  strcat(commandLine,date);
  strcat(commandLine,"\" http://www.wintz-combis.16mb.com/Application_Web/controleur/controleur-carte.php");

  //on envoi la requete POST sur le serveur.
  system(commandLine);
  // On supprime la ligne dans le fichier
    fichier = fopen("coordGPS.txt", "w");
    fclose(fichier);
}
