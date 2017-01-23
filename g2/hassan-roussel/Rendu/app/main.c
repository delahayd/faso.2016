// main.c

#include "lightSensor.h"
#include "detectPassage.h"

//Compilation : gcc grovepi_ultrasonic.c grovepi.c -Wall -o grovepi_ultrasonic
//Execution : sudo ./grovepi_ultrasonic

#define us_cmd 7

int detectPersonne(){
	system("python detectPresence.py");
        //Lire le fichier contenant le booleen
        FILE *fp;
        char buff[255];
        fp = fopen("presence.txt", "r");
        fscanf(fp, "%s", buff);
        fclose(fp);
        return buff[0] == 'T';
}

int main(void)
{
	//Exit on failure to start communications with the GrovePi
	if (init()==-1)
		exit(1);
	
	printf("Ne vous mettez pas devant la caméra, une photo va être prise");
	//Capteur de lumière sur le port A0 en lecture
	int pinLight =0;
	pinMode(pinLight,0);

	//Capteur ultrason branché sur le port D4 (digital 4)
	int pinUltrason=4;
	system("raspistill -w 1024 -h 768 -o background.jpg");
	printf("La caméra a bien été prise");
	while (1){ // On fait tourner le programme en continue
	  	//printf("%d\n",afficherPassage(pinUltrason));
		if (detectPassage(pinUltrason)){
			if (lumiereEteinte(pinLight)){
				system("yee --ip=192.168.43.236 toggle");
				//printf("Par la condition lumière éteinte");
			}
			else{
			  if (!detectPersonne()){
			  	system("yee --ip=192.168.43.236 toggle");
				//printf("Par la condition detecte une personne");
			  }
			}
		pi_sleep(200); // attend 2 secondes
		}
	}
   	return 1;
}
