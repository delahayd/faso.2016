
#include "grovepi.h"
#include "grovepi.c"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define com "communication.txt"

//Compilation : gcc grovepi_ultrasonic.c grovepi.c -Wall -o grovepi_ultrasonic
//Execution : sudo ./grovepi_ultrasonic
	
int main(void){
	  int elementCourant = 2, i = 0, taille = 3;
	int tolerance = 1;
	  char *elems[] = {"Elément 1", "Elément 2", "Elément 3"};
	  show(elems, taille, elementCourant);

	  //Pour tester les fonctions : 8 Pour monter, 2 pour descendre, 0 pour pause, 5 pour quitter
	  //Ces fonctions seront ensuite appelées en fonction des retours des fonctions du capteur ultrason
	int distanceMax = 25;
	while(1){
		int valid = 0;
		show(elems,taille,elementCourant);
		while(distance(4,7) >= distanceMax - 1 && distance(4,7) <= distanceMax + 1){
			
		}
		int distancePrec = distance(4,7);
		while(valid == 0){
			int distanceCourante = distance(4,7);
			if(distanceCourante < distancePrec - tolerance){
				if(elementCourant != taille){
					MenuDown(elems, taille, &elementCourant);
				}
			}
			if(distanceCourante > distancePrec + tolerance){
				if(elementCourant != 1){
					MenuUp(elems, taille, &elementCourant);
				}
			}
			if(distanceCourante ==  distanceMax){ 
				valid = elementCourant;
			}
			
			distancePrec = distanceCourante;
		}
		//Pause();
		
		char currentCh[1];
		sprintf(currentCh, "%d", valid);	
		if(writeFile(com,currentCh,1) == -1){ // On ecrit le numero de l'oeuvre
			return -1;
		}
		printf("%d \n", readFile(com,1));
		int system(const char *command);
		system("expect borneScript.exp");
		system("clear");
		printf("Pause !\n");
		while(readFile(com,1) != 0){ //On attend que la commande ai fini
			
		}
	}
}

void show(char **elems, int t, int e)
{
  int i;
  system("clear");
  for(i = 0; i < t; i++){
    if(e-1 == i)
      printf("%s  <---\n", elems[i]);
    else
      printf("%s\n", elems[i]);
  }
  printf("\n\n\n");
}

//Pré-requis: On a vérifié avant que l'élement courant n'est pas le premier
int MenuUp(char **elems, int t, int *elementCourant)
{
  *elementCourant = *elementCourant - 1;
  show(elems, t, *elementCourant);
  return *elementCourant;
}

//Pré-requis: On a vérifié avant que l'élement courant n'est pas le dernier
int MenuDown(char **elems, int t, int *elementCourant)
{
  *elementCourant = *elementCourant + 1;
  show(elems, t, *elementCourant);
  return *elementCourant;
}

int courant(int elementCourant)
{
  return elementCourant;
}

void Pause(){
  //Pour le test on utilise 0 pour arrêter la pause, ensuite on utilisera les fonctions des capteurs
  int p = 1;
  while(p != 0){
    system("clear");
    printf("Pause\n");
    scanf("%d", &p);
  }
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
