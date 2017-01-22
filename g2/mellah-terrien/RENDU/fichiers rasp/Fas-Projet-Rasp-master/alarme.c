//GrovePi Example for using the digital write command

#include "grovepi.h"
#include "math.h"
#include "curl/curl.h"
#include "stdio.h"
#include "string.h"


//Compilation : sudo gcc alarme.c grovepi.c -Wall -o alarme
//Execution : sudo ./alarme



int main(void)
{
        //Exit on failure to start communications with the GrovePi
        if(init()==-1)
        {
                exit(1);
        }

                int PIN = 7; // Capteur de mouvement branché sur le port D7 (digital 7)
                int data;

                int LED = 4; // LED branchée sur le port D4 (digital 4)
                pinMode(LED,1);

                int BUZZER = 3;// Buzzer branché sur le port D3 (digital 3)
                pinMode(BUZZER,1);

                char liena[100];
                strcat(liena,"curl www.jamesterrien.fr/controller/Controller_Add_Alarm.php");

                system(liena);// Appelle le lien donné, qui va ajouter une nouvelle activation à la BD 
                printf(liena);

                digitalWrite(BUZZER,1); // envoie "HIGH" sur le port LED 
                pi_sleep(200); // attend 500ms
                digitalWrite(BUZZER,0); // envoie "LOW" : éteind la LED
		// LED et buzzer annoncent à l'utilisateur que la tâche a été éxecutée 
                
		printf("\n");
		printf("Alarme en cours d'activation ... \n");
		pi_sleep(5000); //Laisser le temps de quitter le domicile
		printf("Alarme activée !!! \n");

		int n=0; //On initialise un compteur à 0 afin de detecter 4 mouvements afin de s'assurer de ne pas déclencher l'alarme pour rien
                while (n<3)
                {
                        digitalWrite(LED,1);
                        data=digitalRead(PIN);

                        printf("Mouvement : %d cm\n", data);// Affiche 1 sur l'écran de contrôle lorsqu'un mouvement est detecté, 0 sinon

                        if (data>0)
                        {
                                n=n+1; // Si il y a eu un mouvement, n prend n+1
                        }
                         else if (n>0)
                        {
                                n=n-1; // Si il n'y a pas de mouvement, n prend n-1 afin de ne pas mémoriser les mouvements insignifiants
                        }

                        pi_sleep(200); // attend 500ms
                        digitalWrite(LED,0); // envoie "LOW" : éteind la LED
                        pi_sleep(200); // attend 500ms
                }

		//On sort de la boucle, donc un mouvement signifiant a été detecté (n>3) donc on rentre dans le processus d'ajout d'incident

                char status[]="en_cours";
                char lien[170];
                strcat(lien,"curl www.jamesterrien.fr/controller/Controller_Add_Incident.php?status=");
                strcat(lien,status);

                system(lien); // Ce lien va mettre à jour le statut de l'incident : il devient en cours
                printf(lien);
		printf("\n");

		system("echo 'ALERTE INTRUSION ! Quelqu'un s'est introduit chez vous de façon frauduleuse.A plus ;)' | gammu --sendsms TEXT 0659734752");
		//On envoie un SMS au propriétaire pour l'informer d'une intrusion dans son domicile


		int tentative = 0; //On initialise un compteur à 0 qui servira à donner 3 tentatives au visiteur pour déverouiller l'alarme
		int test = 0; //On initialise test à False qui permettra de determiner si le code est juste ou pas
		int code; //On déclare un entier code qui correspond au entré par le visiteur
		int trest = 3;
	
		while (tentative<3 && test==0) 
		{	
			digitalWrite(BUZZER,1); // envoie "HIGH" sur le port LED 
	                pi_sleep(200); // attend 500ms
	                digitalWrite(BUZZER,0); // envoie "LOW" : éteind la LED
			pi_sleep(200);
			digitalWrite(BUZZER,1); // envoie "HIGH" sur le port LED 
	                pi_sleep(200); // attend 500ms
            		digitalWrite(BUZZER,0); // envoie "LOW" : éteind la LED

			printf("Rentrez le code à 4 chiffres\n"); //On affiche la demande de code
			scanf("%d",&code); //On enregistre la donnée du visiteur dans la variable code

			if (code==1234) //On test si le code entré est le bon (ici 1234)
			{
				test=1; //Si le code est juste, test devient True 
			}
			else //Le code entré n'est pas le bon
			{
				tentative=tentative+1; //On ajoute 1 au nombre de tentatives effectuées
				trest=trest-1; //On calcule le nombre de tentatives restantes
				
				printf("Code Erroné !\n"); //On affiche au visiteur que le code est erroné
				printf("Attention ! Il ne vous reste plus que %d tentatives\n", trest); //On indique au visiteur le nombre d'essais restants

				if (tentative==1)
				{
					char statusb[]="echec_tentative";
			                char lienb[120];
			                strcat(lienb,"curl www.jamesterrien.fr/controller/Controller_Update_Status.php?status=");
			                strcat(lienb,statusb);
			
			                system(lienb); //On met à jour le statut de l'incident en GET : il devient echec tentative
                			printf(lienb);
					printf("\n");
				}

				
				
			}
		}
		//On sort de la boucle car le code entré par le visiteur est juste en moins de 3 tentatives ou que trois tentatives infructueuses ont été effectuées on rentre donc dans le processus de fin d'incident
		
		if (test==1)
		{
			digitalWrite(BUZZER,1); // envoie "HIGH" sur le port LED 
		        pi_sleep(600); // attend 500ms
		        digitalWrite(BUZZER,0); // envoie "LOW" : éteind la LED
			//On active la LED et le buzzer pour indiquer au visiteur que le code est juste
		
			printf("Code correct ! \n");
		
			char statusc[]="resolu";
		        char lienc[200];
		        strcat(lienc,"curl www.jamesterrien.fr/controller/Controller_Update_Status.php?status=");
		        strcat(lienc,statusc);
		
		        system(lienc); //On met à jour le statut de l'incident : il devient résolu
		        printf(lienc);
			
			printf("\n");
			
			char liend[130];
		        strcat(liend,"curl www.jamesterrien.fr/controller/Controller_Stop_Alarm.php");
		
		        system(liend); //On appelle un lien qui va mettre fin à la procédure d'incident lancée au début
		        printf(liend);
			printf("\n");
		
			system("echo 'Incident Resolu ! Un code valide a été saisi. '| gammu --sendsms TEXT 0659734752"); //On prévient le propriétaire que l'incident est clos au cas où ce n'était pas lui elle qui était dans son domicile
		
		}
		else
		{
			digitalWrite(BUZZER,1); // envoie "HIGH" sur le port LED 
		        pi_sleep(200); // attend 200ms
		        digitalWrite(BUZZER,0); // envoie "LOW" : éteind la LED
			pi_sleep(200); // attend 200ms
			digitalWrite(BUZZER,1); // envoie "HIGH" sur le port LED 
		        pi_sleep(200); // attend 200ms
		        digitalWrite(BUZZER,0); // envoie "LOW" : éteind la LED
			pi_sleep(200); // attend 200ms
			digitalWrite(BUZZER,1); // envoie "HIGH" sur le port LED 
		        pi_sleep(200); // attend 200ms
		        digitalWrite(BUZZER,0); // envoie "LOW" : éteind la LED
			pi_sleep(200); // attend 200ms
			digitalWrite(BUZZER,1); // envoie "HIGH" sur le port LED 
		        pi_sleep(200); // attend 200ms
		        digitalWrite(BUZZER,0); // envoie "LOW" : éteind la LED
			//On active la LED et le buzzer pour indiquer au visiteur que le code est faux
		
			printf("Code incorrect ! Vos 3 essais ont été utilisés ! \n");
		
			char statuse[]="Code_incorrect";
		        char liene[200];
		        strcat(liene,"curl www.jamesterrien.fr/controller/Controller_Update_Status.php?status=");
		        strcat(liene,statuse);
		
		        system(liene); //On met à jour le statut de l'incident : statut -> code incorrect
		        printf(liene);
			
		
			system("echo 'Trois codes ont été tentés, sans succès ! Nous vous invitons à appeler la police '| gammu --sendsms TEXT 0659734752"); //On prévient le propriétaire que l'incident est grave
		
		}
		
                return 1;

}

