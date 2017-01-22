#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



int main(){
	FILE* fichier=NULL;
	FILE* fichierHashtag=NULL;
	system("python init.py"); // execution prog python pour initialiser au dernier tweet
	fichierHashtag=fopen("Hashtag.txt","w+");
	char hash[30]=""; // creation chaine de caractere pour le #
	printf("Entrez le hashtag :");
	scanf("%s",hash); // demande de rentrer le #
	fputs(hash,fichierHashtag); // ecrit le # dans le fichier
	fclose(fichierHashtag);
	while(1){
		system("python recup.py"); // execution du programme python pour recuperer les tweets
		sleep(10);
		fichier=fopen("Listetweet.txt","r+");
		char line[150];
		while(fgets(line, sizeof line, fichier)!=NULL){
			char commande[300]=""; // creation de la chaine de caractere pour la lecture orale du tweet
                        char afficheTweet[300]=""; // creation de la chaine de caractere pour affiche le tweet
                        strcat(commande,"sudo pico2wave -l fr-FR -w halloworld.wav \""); // debut de la commande pour creer le fichier utilise pour la lecture orale du tweet
                        strcat(commande,line); // ajout du nom de la personne qui a tweet dans le fichier de lecture orale
			strcat(afficheTweet,line); // ajout du nom de de la personne qui a tweet pour l'affichage du tweet
			afficheTweet[strlen(afficheTweet)-1]='\0'; // ajoute 0 à la fin pour signaler fin de la chaine de caractere pour l'affichage du tweet
			strcat(afficheTweet," a tweeté : \n");
			commande[strlen(commande)-1]='\0'; // ajout 0 a la fin pour signaler fin de la chaine de caractere pour la lecture orale
                        strcat(commande," a tweeté : ");
                        fgets(line, sizeof line, fichier); // recuperation de la ligne associer a chaque tweet dans le fichier
			strcat(afficheTweet,line); // ajout du tweet pour l'affichage du tweet
			strcat(commande,line); // ajout du tweet dans la commande pour la lecture orale
                        commande[strlen(commande)-1]='\0';
                        strcat(commande,"\" \n");
			system("sudo mplayer police.mp3"); // alarme sonore du tweet
			system("sudo ./grovepi_led"); // fait clignoter la LED
                        system(commande);
			printf(afficheTweet); // affichage tweet
			system("sudo omxplayer -o local halloworld.wav"); // lecture orale tweet
                       	sleep(2);
		}
		fclose(fichier);
		remove("Listetweet.txt");
	}
	return 0;
}
