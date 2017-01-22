#include <stdio.h>
#include <stdlib.h>
#include "library/grovepi.h"

//Connexion : ssh -Y faizabenchraa@162.38.111.124
//Pwd : faizabenchraa 
//Compilation : gcc security_main.c library/grovepi.c -o security_main
//Execution : sudo ./security_main
//Affichage : xdg-open photo.jpg
//Recuperation des photos : scp faizabenchraa@162.38.111.124:museum_security/photos/*.jpg ~

#define us_cmd 7

int main(void)
{
	//Exit on failure to start communications with the GrovePi
	if(init()==-1)
		exit(1);

	int PIN = 4; // Capteur branché sur le port D4 (digital 4)
	int data;

	//Augmenter le son au maximum
	system("amixer -D pulse sset Master 100%") ;
	
	while(1) // boucle infinie
	{
	  write_block(us_cmd, PIN, 0, 0);
	  pi_sleep(200);
	  read_byte();
	  read_block();
	  data=r_buf[1]* 256 + r_buf[2];
	  printf("%d %d\n", r_buf[1], r_buf[2]);
	  printf("Distance : %d cm\n", data);
		if ((data>100.0) && (data<=150.0)){
			system("omxplayer resources/alarme_boosted.wav") ; //lit le message audio
		}
		else if (data<=100.0){
			// -t : temps de capture (ms). -v : pour afficher les détails. -vf -hf : inverser l'image.
			//Pour les videos : raspivid -t 5000 -o video.h264 
			system("raspistill -t 500 -v -vf -hf -o photos/$(date +'%Y-%m-%d_%H%M').jpg") ;
			//appel script python pour l'envoi
			system("python resources/envoyer.py photos/$(date +'%Y-%m-%d_%H%M').jpg") ;
			system("xdg-open photos/$(date +'%Y-%m-%d_%H%M').jpg") ;//juste pour les tests
		}
	  pi_sleep(500); // attend 500ms
	}
   	return 1;
}
