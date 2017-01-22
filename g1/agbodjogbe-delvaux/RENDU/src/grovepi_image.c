#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#include "grovepi.h"

void change_image(int commande){
	char new_image[256];
	sprintf(new_image," nohup eog --fullscreen ../image/imageColor_%d.png &",commande);
	system(new_image);

}

int definirCouleur(int actu){
	int a = actu; // Le volume envoyé a l'instant par le capteur
	int numImage = 0;
	int personne = 50;
	int seuil_0 = personne;
	int seuil_1 = personne * 2;
	int seuil_2 = personne * 4;
	int seuil_3 = personne * 6;
	int seuil_4 = personne * 8;
	int seuil_5 = personne * 10;
	int seuil_6 = personne * 12;
	int seuil_7 = personne * 14;
	int seuil_8 = personne * 16;
	int seuil_9 = personne * 18;
	int seuil_10 = personne * 20;

	if(a>seuil_0){
		numImage = 0;
	}
	if(a>seuil_1){
		numImage = 1;
	}
	if(a>seuil_2){
		numImage = 2;
	}
	if(a>seuil_3){
		numImage = 3;
	}
	if(a>seuil_4){
		numImage = 4;
	}
	if(a>seuil_5){
		numImage = 5;
	}
	if(a>seuil_6){
		numImage = 6;
	}
	if(a>seuil_7){
		numImage = 7;
	}
	if(a>seuil_8){
		numImage = 8;
	}
	if(a>seuil_9){
		numImage = 9;
	}
	if(a>seuil_10){
		numImage = 10;
	}
	return numImage;
}

int main(){

	int commande = 1;
	int commandeprec = 1;
	//Exit on failure to start communications with the GrovePi
  	if(init()==-1)
    		exit(1);
    // Capteur de son sur le port A0 en lecture
  	int PIN = 1;
  	pinMode(PIN,0);
  	int value;
  	change_image(1);
  	sleep(5);
	while(1){

		value = analogRead(PIN);
		printf("Sensor value = %d\n", value);
		commande = definirCouleur(value);
		if (commandeprec != commande){
			commandeprec = commande;
			change_image(commande);
		}
		sleep(2);
		
	
	}	
	return 0;
	
}
