//GrovePi Example for using the digital write command

#include "grovepi.h"

//Compilation : gcc grovepi_buzzer.c grovepi.c -Wall -o grovepi_buzzer
//Execution : sudo ./grovepi_buzzer

int main(void)
{		
	//Exit on failure to start communications with the GrovePi
	if(init()==-1)
		exit(1);
	
	int LED = 3; // LED branchée sur le port D3 (digital 3)
	//Set pin mode to output
	pinMode(LED,1);  // indique que ce port est utilisé en SORTIE
	while(1) // boucle infinie
	{
	  digitalWrite(LED,1); // envoie "HIGH" sur le port LED (allume la LED)
	  pi_sleep(500); // attend 500ms
	  digitalWrite(LED,0); // envoie "LOW" : éteind la LED
	  pi_sleep(500); // attend 500ms
	}
   	return 1;
}
