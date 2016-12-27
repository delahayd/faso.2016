#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Compilation : gcc interfaceConsole.c -o interfaceConsole

void show(char **pLabel, int t, int e); //Affichage
int MenuUp(char **elems, int t, int *elementCourant); //Monter dans la liste d'éléments
int MenuDown(char **elems, int t, int *elementCourant); //Descendre dans la liste d'éléments
void Pause(); //Mettre le programme en pause
int courant(int elementCourant); //Connaître l'élément courant

int main(int argc,char **argv)
{
  int elementCourant = 3, i = 0, taille = 5;
  char *elems[] = {"Elément 1", "Elément 2", "Elément 3", "Elément 4", "Elément 5"};
  show(elems, taille, elementCourant);

  //Pour tester les fonctions : 8 Pour monter, 2 pour descendre, 0 pour pause, 5 pour quitter
  //Ces fonctions seront ensuite appelées en fonction des retours des fonctions du capteur ultrason
  while(i != 5){
    scanf("%d", &i);
    if(i == 8)
      MenuUp(elems, taille, &elementCourant);
    else if(i == 2)
      MenuDown(elems, taille, &elementCourant);
    else if(i == 0)
      Pause();
      show(elems, taille, elementCourant);
  }
  return 0;
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
