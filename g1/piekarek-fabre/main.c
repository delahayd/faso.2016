
//main du projet Fas
#include "grovepi.h"
#include "projectHeader.h"

//Compilation : gcc grovepi_ultrasonic.c grovepi.c -Wall -o grovepi_ultrasonic
//Execution : sudo ./grovepi_ultrasonic

#define us_cmd 7


void calculDistance(Ultrason *capteur){
	write_block(us_cmd, (*capteur).PORT, 0, 0);
	pi_sleep(10);
	read_byte();
	read_block();
	(*capteur).distance = r_buf[1] * 256 + r_buf[2];
		// on modifie l'attribut distance  du capteur
} 


int main (void){
	if(init()==-1){
		exit(1); // s'il y a une erreur
	}

	int GUIRLANDE = 2; 
	// la guirlande est branché sur le port D2 
	int LUMI = 2; 
	// capteur de luminosité branché sur le port A2

		 
	int  distance; // distance entre l'obstacle et l'ultrason
	int luminosite; // luminosite ambiante

 
	Ultrason u1 = {4, 41, "Tout droit'"}; // creation d'une structure
	Ultrason u2 = {7, 41, "A Gauche'"};
	Ultrason u3 = {3, 41, "A droite'"};
	Ultrason ultrasons []={u1,u2,u3} ;// creation d'un tableau de structure
	const int nbCapteur=2 ;  // nombre de capteur ultrasons
	const char * pathCmd = "/home/nepo/projet/sortieJack.sh ";
		// chemin absolu 
	 



	pinMode(GUIRLANDE,1);  // indique que le port 2 est utilisé en SORTIE
	pid_t p;

	int estAllume = 0;
	while(1){ // boucle infinie 
		//int *res =  capteurIn (ULTRASON);
		// recupere les information sur le port ULTRASON
	 	//distance=res[0] * 256 + res[1];

		// recupere la  luminosite
	 	//printf("Distance : %d cm\n", distance);
		//printf("Luminosite: %d \n", luminosite);


			luminosite = analogRead(LUMI);
			//printf("luminosite %d",luminosite);
			if(luminosite<600){
				if(estAllume == 0){
					digitalWrite(GUIRLANDE,1);
					estAllume=1;
				}
			}else{
				if(estAllume == 1){
					digitalWrite(GUIRLANDE,0);
					estAllume = 0;
				}
			}


			
			int i=0;
			for (i=0; i<nbCapteur; i++){
				calculDistance(&ultrasons[i]);
				if(ultrasons[i].distance <=40)
		 		{
					char script[1024]=""; 
					// string permettra de lancer le script sortieJack

			
					strcat(script, pathCmd);						//concatene des chaine de caractere a la chaine script			system(script);
					//concatene des chaine de caractere a la chaine script			system(script);
					strcat(script,"'obstacle ");
					strcat(script, ultrasons[i].orientation );

					system(script); // execute le script

				}
			
			}

		

		

		
		pi_sleep(5);
	}
	return 1; 

} 


