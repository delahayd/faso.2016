//GrovePi Example for using the digital write command

#include "grovepi.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
//Compilation : gcc grovepi_ultrasonic.c grovepi.c -Wall -o grovepi_ultrasonic
//Execution : sudo ./grovepi_ultrasonic

#define us_cmd 7

int main(void)
{		


	




	//Exit on failure to start communications with the GrovePi
	if(init()==-1)
		exit(1);
	
	int PIN = 4; // Capteur branché sur le port D4 (digital 4)
	int data;
	
	//Initilisation de variable et des structures pour la date
	
    	time_t temps;
  	struct tm date;
	int i=0;
	int moyenne=0;
	int k=0;
	int z=0;
	int tab[10];

	for(i=0;i<10;i+=1){
		write_block(us_cmd, PIN, 0, 0);
		pi_sleep(200);
		read_byte();
		read_block();
		data=r_buf[1]* 256 + r_buf[2];
		tab[i]=data;
		moyenne=moyenne+tab[i];
		printf("%d \n", moyenne);
	}
	moyenne=moyenne/10;
	printf("Moyenne finale : %d \n", moyenne);


	while(1) // boucle infinie
	{
	  write_block(us_cmd, PIN, 0, 0);
	  pi_sleep(200);
	  read_byte();
	  read_block();
	  data=r_buf[1]* 256 + r_buf[2];

		// On récupère la date et l'heure actuelle.
	        time(&temps);
       		 date=*localtime(&temps);

	  if(data<(moyenne-(moyenne/5))){

		for(k=0;k<5;k+=1){
			
			char s[128];
			time(&temps);
                 	 date=*localtime(&temps); 	 

			strftime(s, 128, "raspistill -t 2000 -v -o ./photos/photosMail/IMG_%Y%m%d_%H%M%S.jpg", &date);
			system(s);
			pi_sleep(1000);
		}
		system("./CompileMail"); // Envoie les photos du dossier ./photos/photosMail par mail
		system("rm -f ./photos/photosMail/IMG*"); // Supprime les photos du dossier photosMail qui ont été envoyées

		for(z=0;z<20;z+=1){
			char p[128];
			time(&temps);
                         date=*localtime(&temps); 
			strftime(p, 128, "raspistill -t 2000 -v -o /var/www/html/photos/IMG_%Y%m%d_%H%M%S.jpg", &date);
			system(p);
                        pi_sleep(1000*15); //attend 15 secondes avant de reprendre une photo
		}
	  pi_sleep(10*60*1000); // attend 10 min avant de relancer le systeme
		}
	}
   	return 1;
}
