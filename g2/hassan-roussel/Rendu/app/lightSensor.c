//Fichier pour utiliser la sensibilisation de la lumière

#include "lightSensor.h"
#include "grovepi.h"

//Compilation : gcc grovepi_ultrasonic.c grovepi.c -Wall -o grovepi_ultrasonic
//Execution : sudo ./grovepi_ultrasonic

#define us_cmd 7

	int lumiereEteinte(int pinLight){
	  return (analogRead(pinLight)<150); // quand le capteur a une valeur inférieure à 150 on considère que la pièce est allumée (de manière naturelle ou artificielle)
	}

/* 
 int main(){
	if(init()==-1)
	  exit(1);

	int pinLight=0;
	pinMode(pinLight,0);
	printf("Je rentre dans le programme");
	while(1){
	  if(isLight(pinLight)){
	    printf("%d\n",analogRead(pinLight));
	  }
	pi_sleep(100);
	}

	return 1;
}
*/		
