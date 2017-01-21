#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// http://paristech.institutoptique.fr/site.php?id=469&fileid=2739

// Permet de récupèrer les données d'un fichier texte où sont stocker les coords GPS
// Une fois le texte récupérer, on la supprime du fichier.
void main() {
  // //Lance le programme pyhton qui recupère les données GPS et les ecrits dans le fichier texte
  // system("python ../Python/GPS.py");
  // //On Récupère en C les données inscrites dans le fichier
  // int i;
  // double tab[2];
  // FILE *fichier;
  //
  // fichier = fopen("coordGPS.txt", "r");
  // if (fichier != NULL) {
  //   for (i=0; i<2; i++) {
  //     fscanf(fichier, "%lf\n", tab+i);
  //   }
  //   fclose(fichier);
  // }
  // Cood GPS que l'on va spliter
  char *coord = "$GPRMC,124306.000,A,4337.9823,N,00351.7667,E,0.00,344.00,190117,,,A*67";
  char result[6][30];

  int i=6; // prend succes les valeurs de coord
  int j =0; //parcourt les cara de chaque fois de result
  int compteVirgule = 0;

   while (compteVirgule<6){
     i++;
     int j = 0; //parcourt les cara de chaque mot de result
      while (coord[i] != ',') {
          result[compteVirgule][j] = coord[i];
          i++;
          j++;
      }
      compteVirgule++;
  }
  result[0][6] = '\0';
  /*On construit la chaine de caractère pour l'utiliser en ligne de commande */
  char commandLine[43] = "curl --data \"action=SEND_POS&user=Lolo&lat=";
  char lat[30];
  char lng[30];
  // sprintf(lat,"%lf",tab[0]);
  // sprintf(lng,"%lf",tab[1]);
  // sprintf(lat,"%lf",result[2]);
  // sprintf(lng,"%lf",result[4]);
  strcat(commandLine,result[2]);
  strcat(commandLine,"&lng=");
  strcat(commandLine,result[4]);
  char date[5] = "today";
  strcat(commandLine,"&date=");
  strcat(commandLine,result[0]);
  strcat(commandLine,"\" http://www.wintz-combis.16mb.com/Application_Web/controleur/controleur-carte.php");

  //on envoi la requete POST sur le serveur.
  system(commandLine);
  // On supprime la ligne dans le fichier
    // fichier = fopen("coordGPS.txt", "w");
    // fclose(fichier);
}
