//GrovePi Example for using the digital write command

#include "grovepi.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Compilation : gcc grovepi_ultrasonic.c grovepi.c -Wall -o grovepi_ultrasonic
//Execution : sudo ./grovepi_ultrasonic

#define us_cmd 7

/*
*Récupère la distance renvoyée par le capteur dont le PIN est passé en paramètre
*/
int capteur(int PIN){
	int data;
        write_block(us_cmd, PIN, 0, 0);
        pi_sleep(20);
        read_byte();
        read_block();
        data=r_buf[1]* 256 + r_buf[2];
        printf("%d %d\n", r_buf[1], r_buf[2]);
	printf("Distance : %d cm\n", data);
	pi_sleep(50); // attend 100ms
	return data;
}

/*
*Modifie la valeur dans le fichier nbpers correspondant à notre module nbpersonnes sur l'application
*/
int modifValeur(int val){
	FILE* fichier = NULL;
	int nbpersonnes;
	fichier = fopen("../MagicMirror/modules/default/nbpersonnes/nbpers.txt", "r");
	fscanf(fichier, "%d", &nbpersonnes);
	fclose(fichier);
	fichier = fopen("../MagicMirror/modules/default/nbpersonnes/nbpers.txt", "w");
	nbpersonnes = nbpersonnes + val;
	fprintf(fichier, "%d\n", nbpersonnes);
	fclose(fichier);
	pi_sleep(500);
}

/*
*Regarde si le capteur détecte une présence. Donc si la distance est inférieure à 30 (dans notre cas)
*/
int estModifie(int pin){
	if(capteur(pin) < 30){
		return 1;
	}else{
		return 0;
	}
}




int main(void)
{
        //Exit on failure to start communications with the GrovePi
        if(init()==-1){
                exit(1);
	}

	int cap1, cap2, etat1, etat2, dist;

	//Les deux variables prennent les pin de nos deux capteurs en valeur
	cap1 = 7;
	cap2 = 8;

	sleep(1);

	//Boucle infinie pour récupérer les données des capteurs 
	while(1){

		etat1 = estModifie(cap1); // Prend la valeur 1 si la distance est modifiée, 0 sinon
		etat2 = estModifie(cap2);
		if(etat1==1 || etat2==1){ // Si un des capteurs détecte une présence
			if(etat1==1){ // Si c'est le capteur 1
				while(etat1==1){ // Il attend que la personne située devant soit partie
					etat1 = estModifie(cap1);
				}
				while(etat2==0 && etat1==0){ // Il attend que l'un des capteurs soit actif
					etat1 = estModifie(cap1);
					etat2 = estModifie(cap2);
				}
				if(etat1==1){ // Si c'est encore le capteur 1 qui est modifié (finalement la personne ne rentre pas)
				        while(etat1==1){ // Il attend que la personne située devant parte
                                	        etat1 = estModifie(cap1);
                                	}
					etat1 = 0; // On retourne au cas de base
					etat2 = 0; 
				}else if(etat2==1){ // Si le capteur 2 détecte à son tour
                                        while(etat2==1){ // Il attend que la personne devant parte
                                                etat2 = estModifie(cap2);
                                        }
					modifValeur(1); // Alors la personne entre donc on appelle la fonction avec la valeur 1 pour faire nbpersonne+1
					etat1 = 0;
					etat2 = 0;
				}
			}else if(etat2==1){ // Si c'est le capteur 2 qui détecte en premier une présence
                                while(etat2==1){ // Il attend que la personne partie
                                        etat2 = estModifie(cap2);
                                }
				while(etat2==0 && etat1==0){ // Il attend que l'un des capteurs soit actif
                                        etat1 = estModifie(cap1);
                                        etat2 = estModifie(cap2);
                                }
                                if(etat2==1){ // Si c'est encore le capteur 2 qui est modifié (donc personne ne sort)
                                        while(etat2==1){ // Il attend que la personne devant parte
                                                etat2 = estModifie(cap2);i
                                        }
                                        etat1 = 0; // On revient au cas de base
                                        etat2 = 0;
                                }else if(etat1==1){ // Si le capteur 1 détecte à son tour
					while(etat1==1){ // Il attend que la personne devant parte
                                                etat1 = estModifie(cap1);
                                        }
                                        modifValeur(-1); // Alors la personne sort donc on appelle la fonction avec la valeur -1 pour faire nbpersonnes-1
                                        etat1 = 0;
                                        etat2 = 0;
                                }
			}
		}
	}
	return 0;
}
