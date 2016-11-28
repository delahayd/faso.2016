//GrovePi Example for using the digital write command

#include "grovepi.h"

//Compilation : gcc grovepi_led.c grovepi.c -Wall -o grovepi_led
//Execution : sudo ./grovepi_led

int main(void)
{		
	//Exit on failure to start communications with the GrovePi
	if(init()==-1)
		exit(1);
	
	int LED = 2; // LED branchée sur le port D2 (digital 2)
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
