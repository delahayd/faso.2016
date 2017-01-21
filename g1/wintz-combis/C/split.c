#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



int main(int argc, char *argv[])

{
      char *coord = "$GPRMC,114306.000,A,4337.9823,N,00351.7667,E,0.00,344.00,190117,,,A*67";
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
          result[compteVirgule][j] ='\0';
          compteVirgule++;
      }
      int longueur = 0;
      longueur = strlen(result[0]);
      printf("%s\n%d\n", result[0], longueur);
      result[0][6] = '\0';
      printf("%s\n%d\n", result[0], longueur);
      // Conversion de la lat
      // On sépart le string en 2
      char lat1[3];
      int longLat = 0;
      longLat = strlen(result[2]);
      int l = 0;
      while (l<2) {
        lat1[l] = result[2][l];
        l++;
      }
      char lat2[10];
      printf("valeur de lat1 : %s\n", lat1);
      printf("valeur de l : %d\n", l);
      while (l<longLat) {
        lat2[l] = result[2][l];
        printf("valeur de lat2 : %s\n", lat2);
        l++;
      }
      printf("valeur de lat2 : %s\n", lat2);
      float lat;
      lat = (float)*lat1+*lat2/60;
      printf("valeur de lat : %slf\n", lat);
    return 0;

}
