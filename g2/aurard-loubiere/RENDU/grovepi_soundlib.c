//GrovePi Example for using the analogic read command

#include "grovepi.h"

//Compilation : gcc grovepi_sound.c grovepi.c -Wall -o grovepi_sound
//Execution : sudo ./grovepi_sound
#define us_cmd 7
int recupValSon(void){
	//Exit on failure to start communications with the GrovePi
	if(init()==-1)
	exit(1);

	// Capteur de son sur le port A0 en lecture
	int PIN = 0;
	pinMode(PIN,0);

	// LED sur le port D5 en ecriture
	//  int LED = 5;
	//  pinMode(LED,1);

	// The threshold to turn the led on 400.00 * 5 / 1024 = 1.95v
	int threshold_value = 150;

  	int value;
  
	value = analogRead(PIN);
	printf("Sensor value = %d\n", value);
	if (value > threshold_value)
		// digitalWrite(LED,1);
		printf("son \n" );
	else{
		// digitalWrite(LED,0);
		printf("pasSon \n");
	 	pi_sleep(200);
	}

	return value;
}


int recupValUltraSon(void){
	//Compilation : gcc grovepi_sound.c grovepi.c -Wall -o grovepi_sound
//Execution : sudo ./grovepi_sound


	//Exit on failure to start communications with the GrovePi
	if(init()==-1)
		exit(1);
	
	int PIN = 4; // Capteur branché sur le port D4 (digital 4)
	int data;
	 // boucle infinie
	
	  write_block(us_cmd, PIN, 0, 0);
	  pi_sleep(200);
	  read_byte();
	  read_block();
	  data=r_buf[1]* 256 + r_buf[2];
	  printf("%d %d\n", r_buf[1], r_buf[2]);
	  printf("Distance : %d cm\n", data);
	  pi_sleep(500); // attend 500ms
	

	return data;
}
