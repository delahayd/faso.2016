
#include "grovepi.h"
#include "grovepi.c"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define com "communication.txt"

//Compilation : gcc grovepi_ultrasonic.c grovepi.c -Wall -o grovepi_ultrasonic
//Execution : sudo ./grovepi_ultrasonic
	
int main(void){
	int current = 1;
	//while(1){
		int valid = -1;
		while(valid == 0){

			if(distance(4,7) < 10){
				menuUp();
			}
			if(distance(5,7) < 10){
				menuDown();
			}
			if(distance(6,7) < 10){
				valid = validate();
			}

			if(checkVibration() == 1){
				buzz();
			}
		}
		pauseMenu();
		
		char currentCh[1];
		sprintf(currentCh, "%d", current);	
		if(writeFile(com,currentCh,1) == -1){ // On ecrit le numero de l'oeuvre
			return -1;
		}
		
		//int system(const char *command);
		//system("scp link.txt maximekevin@162.38.111.9:");
		
		while(readFile(com,1) != 0){ //On attend que la commande ai fini
			
		}
	//}
}

void menuUp(){
	
}

void menuDown(){
	
}

void pauseMenu(){
	
}

int checkVibration(){
	return 0
}

int validate(){
	return 0;
}

void buzz(){
	
}

int distance(int PIN, int us_cmd){
	if(init()==-1)
		exit(1);

	write_block(us_cmd, PIN, 0, 0);
	pi_sleep(200);
	read_byte();
	read_block();
	return r_buf[1]* 256 + r_buf[2];
}

int writeFile(char* filename, char buffer[]){
	FILE *fp;
	fp = fopen(filename,"w");
	int nbwrite = fwrite(buffer, 1, sizeof(buffer), fp);
	fclose(fp);
	if(nbwrite == sizeof(buffer))
		return 0;	
	return -1;
}

int readFile(char* filename, int curseur){
	FILE * fp;
	fp = fopen(filename, "r");
	int x;
	for(x = 0; x < curseur -1; x = x +1){
		fgetc(fp);
	}
	int tmp = (int)(fgetc(fp)) - 48;
	fclose(fp);
	return tmp;
}
