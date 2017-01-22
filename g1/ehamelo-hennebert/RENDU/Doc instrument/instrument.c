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
	int test=0;

	if(init()==-1)
                exit(1);
        
	int LED = 3; // LED branchée sur le port D3 (digital 3)
        //Set pin mode to input
        pinMode(LED,0);  // indique que ce port est utilisé en Entrée
        
	 //Exit on failure to start communications with the GrovePi
        if(init()==-1)
                exit(1);
	int PIN = 4; // Capteur branché sur le port D4 (digital 4)
        int data;
	char *note;
	int valeur=digitalRead (LED);// prend la valeur 1 que si on appuye sur le bouton
	
	do{       
	if((valeur==0) && ( test <200 )) // boucle condition d'arrêt : on a appuyé sur le bouton. Mais notre bouton ne fonctionnait pas, on a fait la condition avec un compteur " test" qui demande s'incrémente à chaque tout de boucle
        {
        //valeur=digitalRead (LED);
          write_block(us_cmd, PIN, 0, 0);
          pi_sleep(50);
          read_byte();
          read_block();
          data=r_buf[1]* 256 + r_buf[2];
        
	  if (data<5)
	  {note="60";}
	  else if ( data <10)
	  {note="62";}
	  else if  (data<17){
	  note="64";}
	  else if (data<24){
	  note="65";}
	  else if (data<31){
	  note="67";}
	  else if(data<38){
	  note="69";}
	  else if(data<45){
	  note="71";}
	  else if(data<52){
          note="72";}
	  else {
	  note ="10";}
	  FILE *f = fopen("musique_live.txt","w");
	  fprintf(f, "%s.\n", note);
	  fclose(f);
	  FILE *f2 = fopen("musique.txt","a");
	  fprintf(f2,"%s.\n",note);
	  fclose(f2);  
	  test +=1;
        }
	else{
	char *message ="arrêt";
	FILE *f = fopen("musique_live.txt","a");
	fprintf(f,"%s.\n",message);
	fclose(f);
	touche= 'a';}
	}while (touche ==' ');
	pi_sleep(100);
	printf(" Joli Morceau ! Voulez vous le réécouter ? Si oui, rappuyez donc sur le bouton!\n");
	int i = 10;
	do{
	printf("%i\n",i);
	i=i-1;
	pi_sleep(1000);}
	while(valeur==0 &&i>0);

	if ((valeur ==1) && (i<10)) /*si on appuye sur le bouton avant la fin du compte à rebours*/
	{//http://melem.developpez.com/tutoriels/langage-c/fichiers/?page=cours#LI-E
	char src[FILENAME_MAX]= "musique.txt";
    	FILE *fsrc  = fopen(src, "rb");
	char dest[FILENAME_MAX]="musique_live.txt";
        FILE *fdest = fopen(dest, "wb");
        int compt;
        while ((compt = getc(fsrc)) != EOF)
        	{putc(compt, fdest);
		}
	fclose(fdest);
        fclose(fsrc);
	}
	system ("sudo rm musique.txt");
	return 1;
	}

