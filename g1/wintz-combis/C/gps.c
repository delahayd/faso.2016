// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <time.h>
//
// // Récupère à l'infini les coord GPS
// void main() {
//
//
//     char tab[80];
//
// // $GPRMC,114306.000,A,4337.9823,N,00351.7667,E,0.00,344.00,190117,,,A*67
//
//       tab[1] = system("sudo grep -e ^\$GPRMC /dev/ttyAMA0 | head -n 1")
//       printf(tab[1]);
//
// }
// i

#include <stdio.h>
#include <stdlib.h>

int main(void){

        FILE* fichier;
        int i;
        char chaine[100] = "";
        fichier  = fopen("test.txt","r");
        if(fichier != NULL){
                for(i=0;i<5;i++){
                        fgets(chaine,100,fichier);
                        printf("%s",chaine);
                }
                fclose(fichier);
        }
        return 0;
}
