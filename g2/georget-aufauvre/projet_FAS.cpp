/* Projet FASKAS 
 * Par GEORGET Toinon et AUFAUVRE Alex*/ 


#include "eHealth.h"
#include "stdio.h"
#include "time.h"

using namespace std; 

void setup()
{
Serial.begin(115200);


}

void initTab(float tab[],int taille)
{	//données : tableau de float non affecté, entier taille du tableau 
	//résultat : tableau de float initialisé à 0 pour toutes ses cases 
	for(int i=0; i<taille; i++)
	{
		tab[i]=0;
		
	}
	 
}



void insertVal(float tab[], float val, int taille){
	//données : tableau de float ordonné de manière croissante contennant les 10 plus grosses valeurs de conductance déjà récupérée, 
        // la conductance de type float supérieur à t[0] à ajouter 
	// résultat : le tableau de float avec la conductance ajoutée à sa place dans le tableau 
	int i=1; 
	while(val>tab[i]&& i<taille)
	{
		tab[i-1]=tab[i]; 
		i++;
	}
	
	tab[i-1]=val;
	

}

float moyTab(float tab[], int taille){
	//donnée : tableau de float et sa taille 
	//résultat : float moy des valeurs du tableau 
	float moy=0;
	for(int i=0; i<taille ; i++)
	{
		moy+=tab[i];
		
		
	}
	return moy/float(taille);
}




//PROGRAMME PRINCIPAL 



int main(void) 
{ 	setup();
	double tempsDep=time(NULL); //temps de départ aux secondes actuelles 
	double tempsCourant;
	double tempsEcoule; 
	double dureeInit=30; //durée du calibrage 
	double dureeExp=180; //durée de l'expérience 
	int tailleInit = 10; //nombre de mesures que l"on veut garder du calibrage 
	int tailleExp = 30; //nombre de mesures que l'on veut garder de l'expérience
	
	//préparation à la mesure de la conductance 
	float conductance; 	
	float TabCondInit[tailleInit]; //tableau des mesures de calibrage de la conductance 
	float TabCondExp[tailleExp]; //tableau des mesures de l'expérience pour la conductance
	initTab(TabCondInit,tailleInit); //initialisation du tableau de calibrage à 0 
	initTab(TabCondExp,tailleExp); //initialisation du tableau de l'expérience à 0 
	
	//préparation à la mesure de la température 
	float temp;
	float TabTempInit[tailleInit];//tableau des mesures de calibrage de la température 
	float TabTempExp[tailleExp]; //tableau des mesures de l'exoérience pour la température
	initTab(TabTempInit,tailleInit); //initialisation du tableau de calibrage à 0
	initTab(TabTempExp, tailleExp); //initialisation du tableau de l'expérience à 0 
	
	
	
	
	//CALIBRAGE 
	while(tempsEcoule<dureeInit) //tant que le temps écoulé est inférieur à la durée du calibrage 
	{
		//on récupère les données des (taille) valeurs les plus hautes 
		tempsCourant=time(NULL);
		tempsEcoule=tempsCourant-tempsDep;
		

		printf("le temps est de %f \n" ,(double) tempsEcoule);
		delay(1000); //attente d'une seconde 
		printf("la conductance min est de %.2f \n", TabCondInit[0]); 
		printf("la température min est de %.2f \n", TabTempInit[0]); 
		//on récupère la conductance
		conductance = eHealth.getSkinConductance(); 
		//on récupère la température
		temp = eHealth.getTemperature();  
		
		if(conductance>TabCondInit[0])//si la conductance obtenue est supérieure à la plus petite valeur du tableau 
			{ 	//on insère la conductance à sa place dans le tableau 
				insertVal(TabCondInit,conductance,tailleInit);
		
			}
			
		if(temp>TabTempInit[0]) //si la température est supérieure à la plus petite valeur du tableau 
			{ //on insère la température à sa place dans le tableau 
				insertVal(TabTempInit, temp, tailleInit);
			}
	
	
	
	
	
	
	}
	
	//CALCUL RESULTAT CALIBRAGE 
	//on calcule la moyenne de la conductance de calibrage
	float moyCondInit = moyTab(TabCondInit,tailleInit); 
	printf("moyenne conductance initiale %.2f \n", moyCondInit); 
	//on calcule la moyenne de la température calibrage 
	float moyTempInit = moyTab(TabTempInit, tailleInit);
	printf("moyenne de la température initiale %.2f \n", moyTempInit);
	
	//remise à 0 des horloges 
	tempsDep=time(NULL);
	tempsEcoule=0;
	
	

	//EXPERIENCE 
	while(tempsEcoule<dureeExp)
	{	//tant que le temps écoulé est inférieur à la durée de l'expérience 

		tempsCourant=time(NULL);
		tempsEcoule=tempsCourant-tempsDep;


		printf("le temps est de %.1f \n" ,(double) tempsEcoule);
		delay(1000); //attente d'une seconde 
		//on récupère la conductance 
		conductance = eHealth.getSkinConductance();
		//on récupère la température
		temp = eHealth.getTemperature();  
		
		printf("la conductanceest de %.2f\n", conductance); 
		if(conductance>TabCondExp[0])//si la conductance est supérieure à la plus petite déjà obtenue 
			{ //on l'insère à sa place dans le tableau
				insertVal(TabCondExp,conductance,tailleExp);
				printf("la conductance min est de %.2f\n", TabCondExp[0]); 
			}
		
		if(temp>TabTempExp[0])//si la conductance est supérieure à la plus petite déjà obtenue 
			{ //on l'insère à sa place dans le tableau
				insertVal(TabTempExp,temp,tailleExp);
				printf("la conductance min est de %.2f\n", TabTempExp[0]); 
			}
	}
	
	//CALCUL RESULTAT EXPERIENCE 
	//calcul de la moyenne de la conductance sur l'expérience 
	float moyCondExp= moyTab(TabCondExp,tailleExp);
	printf("moyenne conductance expérience %.2f \n", moyCondExp); 
	// calcul sur pourcentage d'augmentation de la conductance par rapport au calibrage 
	float stressCond = moyCondExp/moyCondInit;
	
	printf("Votre transpiration a augmenté de %.2f % \n", stressCond); 
	
	//calcul de la moyenne de la température sur l'expérience 
	float moyTempExp= moyTab(TabTempExp,tailleExp);
	printf("moyenne température expérience %.2f \n", moyCondExp); 
	// calcul sur pourcentage d'augmentation de la température par rapport au calibrage 
	float stressTemp = moyTempExp/moyTempInit;
	
	printf("Votre température a augmenté de %.2f % \n", stressTemp); 

	
	

	return 0;
	
}





