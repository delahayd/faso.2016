#include "affichage_lcd.h"
#include "grovepi.h"
#include <stdlib.h>
#include <stdio.h>

void initlcd()
/*Initialise l'ecran*/
{
	system("i2cset -y 1 0x62 0x00 0x00");
	system("i2cset -y 1 0x62 0x01 0x00");

	system("i2cset -y 1 0x3e 0x80 0x01");
	system("i2cset -y 1 0x3e 0x80 0x0F");
	system("i2cset -y 1 0x3e 0x80 0x38");
}

void afficher(char* c)
/* Recoit une chaine de caracteres et l'affiche en utilisant les commandes systeme. */
{
	if(c!=NULL)
	{
		const char* cmd="i2cset -y 1 0x3e 0x40 ";
		char str[3] = "";
		int i=0;
		while (c[i]!='\0')
		{
			sprintf(str,"%d", c[i]);
			system(strcat(cmd,str));
		}
	}
}

void effacer()
/*Reinitialise l'ecran lcd*/
{
	initlcd();
}


void couleur(int c)
/*Change la couleur de l'ecran lcd : 1 pour le vert et 2 pour le rouge, autre chose pour reinitialiser */
{
	switch (c)
	{
		case 1: //couleur verte
		{

		}
		case 2: //couleur rouge
		{

		}
		default:
		{
			reset_couleur();
		}
	}

}

void reset_couleur()
/* Reinitialise la couleur de fond de l'ecran */
{




}