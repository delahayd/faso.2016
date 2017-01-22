#include <stdio.h>
#include <stdlib.h>

int main(void)
{

//ON RECUPERE L'EMAIL DE L'UTILISATEUR
	FILE* fichier_usermail = NULL;
	fichier_usermail = fopen("/var/www/html/usermail.txt", "r+"); //on ouvre et on stock le fichier dans la variable fichier_usermail
	char usermail[360] = "";

        if (fichier_usermail != NULL)
	   {
		fgets(usermail, 360, fichier_usermail); //on stock l'adresse mail dans la variable usermail
		
		fclose(fichier_usermail);
    	    }
	else
	  {  // On affiche un message d'erreur
		printf("Impossible de lire le fichier username.txt");
	  }

//On l'envoie
	char s[360];
	printf("Envoi en cours à %s...", usermail);
	sprintf(s,"echo \"Ci-joint les photos prises de l'intrusion\" | mutt -s \"Intrusion détecté\" -a ./photos/photosMail/IMG_* -- %s",usermail);
	system(s);
	printf("Ok");

return 1;
}
