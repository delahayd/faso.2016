//GrovePi Example for using the analogic read command

#include "grovepi.h"

//Compilation : gcc grovepi_sound.c grovepi.c -Wall -o grovepi_sound
//Execution : sudo ./grovepi_sound

int main(void)
{
  //Exit on failure to start communications with the GrovePi
  if(init()==-1)
    exit(1);

  // Capteur de son sur le port A0 en lecture
  int PIN = 0;
  pinMode(PIN,0);

  // LED sur le port D5 en écriture
  int LED = 5;
  pinMode(LED,1);

  // The threshold to turn the led on 400.00 * 5 / 1024 = 1.95v
  int threshold_value = 400;

  int value;
  while(1)
    {
      value = analogRead(PIN);
      printf("Sensor value = %d\n", value);
      if (value > threshold_value)
        digitalWrite(LED,1);
      else
        digitalWrite(LED,0);
      pi_sleep(500);
    }
    return 1;
}
