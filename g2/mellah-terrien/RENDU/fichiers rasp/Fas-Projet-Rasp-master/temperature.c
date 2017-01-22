//GrovePi Example for using the analogic read command

#include "grovepi.h"
#include "math.h"
#include "curl/curl.h"
#include "stdio.h"
#include "string.h"

//Compilation : gcc grovepi_sound.c grovepi.c -Wall -o grovepi_sound
//Execution : sudo ./grovepi_sound

int main(void)
{
  //Exit on failure to start communications with the GrovePi
  if(init()==-1)
  {
    exit(1);
  }
  else 
  {
  // Capteur de son sur le port A0 en lecture
  int PIN = 0;
  pinMode(PIN,0);


  float value;

      value = analogRead(PIN);

      float temperature=1.0/(log((100000*(1023.0/(value)-1.0))/100000.0)/4275+1/298.15)-273.15;
      printf("Sensor value = %f\n", temperature);
        char temp[100]="";
	sprintf(temp,"%f",temperature);
        char lien[200];
        strcat(lien,"curl www.jamesterrien.fr/controller/Controller_Add_Temperature.php?temp=");
        strcat(lien,temp);

	system(lien);
	printf(lien);
    
  return 1; 
   }
}

