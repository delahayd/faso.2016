#include "grovepi.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


//Compilation : gcc instrument.c grovepi.c -Wall -o instrument
//Execution : sudo ./instrument

#define us_cmd 7
 
int main(void)
{

char touche=' ';
printf("faisons un peu de musique\n");


//touche= getchar();	
	if(init()==-1)
                exit(1);
        int LED = 3; // LED branchée sur le port D3 (digital 3)
        //Set pin mode to input
        pinMode(LED,0);  // indique que ce port est utilisé en Entrée
        int valeur=digitalRead (LED);// prend la valeur 1 que si on appuye sur le bouton
	do{
	if (valeur==1)
	{printf("Le bouton marche");
	touche ='a';}
	}while (touche==' ');
	return 1;

}
