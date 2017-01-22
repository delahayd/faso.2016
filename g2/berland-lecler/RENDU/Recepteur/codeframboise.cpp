#include "affichage_lcd.h"
#include <i2c-dev.h>
int pinIR = 1;
int pinboutonplus = 6;
int pinboutonmoins = 7;
int pinboutonvalider = 8;
int delai = 300;
int duree = 30;
int seuil=230;
bool* tab=new bool[6];
int attente = 100;
int sallemax = 3;


int decode()
{   //Convertit le code "hexet" en un chiffre, le numero de la salle
	int k = 0;
	if (tab[1]) k+=1;
	if (tab[2]) k+=2;
	if (tab[3]) k+=4;
	if (tab[4]) k+=8;
	return k;
}


void recevoir()
// Attendre le premier 1 envoye par la LED IR
{
	// Effectue un nombre maximal de tentatives de reception (10)
	int cpt = 0;
	while(analogRead(pinIR)<seuil) && (cpt < 10)
	{
		cpt +=1;
		sleep(5);
	}
	int t=0;
	while (t!=6)
	{
		tab[t]=analogRead(pinIR)>=seuil;
		t++;
		sleep(duree);
	}
}



int decoder()// Decodage
/* Retourne le numero de la salle recu, 0 si erreur de reception (delai depasse, code invalide) */
{
	// Effectue un nombre maximal de tentatives de reception et de decodage
	int cpt = 0;
	do
	{
		recevoir();
		cpt +=1;
	}while ((!tab[0] || !tab[5]) && cpt < attente);
	if(!tab[0] or !tab[5])
		return 0;
	return decode();
}




int demander(const char* c) //Demande une destination a l'utilisateur #-> Int entre 1 et 3, le numero de salle
/* c contient le texte a afficher a l'utilisateur */
{ 
	int retour = 1;
	const char* c = "";
	do
	{
		sprintf (c,"%d",retour);
		afficher(c);
		if((digitalRead(pinboutonplus) == HIGH) && (retour < sallemax)) 
		{
			retour ++;
			sleep(500);
		}
		if((digitalRead(pinboutonmoins) == HIGH) && (retour > 1))
		{
			retour --;
			sleep(500);
		}

	}while(digitalRead(pinboutonvalider) == LOW);
	return retour;
}


bool salleX(int x)
{
	//Affiche la ou est la destination par rapport a la salle actuelle
	int n = decoder();
	bool T = false;
	bool abandon = false;
	while ((not T) && (not abandon))
	{
		sleep(2000);
		reset_couleur();
		effacer();
		if (n == x)
		{
			afficher("Bonne salle");
			couleur(1);
			T = true;
		}
		else if (n != 0)
		{
			afficher("Mauvaise salle");
			couleur(2);
		}
		else
		{
			// Declencher erreur, abandon
			abandon = true;
		}
	}
	return abandon;
}



int main()
{
	// Ce programme n'est pas cense s'arreter, il n'est pas redemarrable par l'utilisateur
	while (true)
	{
		initlcd();
		reset_couleur();
		int depart = demander("salle actuelle");
		int destination = demander("destination");
		pinMode(pinIR,INPUT);
		while (destination == depart)
		{
			destination = demander("recommencez");
		}
		int salle = depart;
		switch(salle)
		{
			case 1:
			{
				if (destination == 2)
				{
					salleX(2);	
				}
				else if(destination == 3)
				{
					if (salleX(2))
						break;
					salleX(3);
				}
				break;
			}
			case 2:
			{
				if (destination == 1)
				{
					salleX(1);
				}
				else if(destination == 3)
				{
					salleX(3);
				}
				break;
			}
			case 3:
			{
				if (destination == 2)
				{
					salleX(2);
				}
				else if(destination == 1)
				{
					if (salleX(2))
						break;
					salleX(1);
				}
				break;
			}
			default:
			{
				break;
			}
		}
		depart = destination;
		sleep(1000);
		reset_couleur();
	}
	return 0;
}
