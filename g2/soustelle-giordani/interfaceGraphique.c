#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

// Compilation : gcc interfaceGraphique.c -o interfaceGraphique `pkg-config --cflags --libs gtk+-2.0`

void showCurrent(char **elems, GtkWidget **pLabel, int *elementCourant); //Affichage
void OnDestroy(GtkWidget *pWidget, gpointer pData);
int MenuUp(char **elems, GtkWidget **pLabel, int *elementCourant); //Monter dans la liste d'éléments
int MenuDown(char **elems, GtkWidget **pLabel, int *elementCourant); //Descendre dans la liste d'éléments
void Pause(); //Mettre le programme en pause
int courant(int elementCourant); //Connaître l'élément courant
int fenetre(int argc,char **argv);

int main(int argc,char **argv)
{
  fenetre(argc, argv);
  return 0;
}

int fenetre(int argc,char **argv)
{
  //Initialisation
  gtk_init(&argc, &argv);
  int elementCourant = 3, i, taille = 5;
  GtkWidget *pWindow;
  GtkWidget *pLabel[taille];
  GtkWidget *pBox;
  gchar* sUtf8;
  char *elems[] = {"Elément 1", "Elément 2", "Elément 3", "Elément 4", "Elément 5"};

  //Fenetre
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(pWindow), "Projet FASO");
  gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);

  //Labels - UTF8
  for(i = 0; i < taille; i++){
    sUtf8 = g_locale_to_utf8(elems[i], -1, NULL, NULL, NULL);
    pLabel[i] = gtk_label_new(sUtf8);
  }
  g_free(sUtf8);
  for(i = 0; i < taille; i++){
    gtk_label_set_use_markup(GTK_LABEL(pLabel[i]), TRUE);
  }

  //Afficher l'élement courant
  showCurrent(elems, pLabel, &elementCourant);

  //Box
  pBox = gtk_vbox_new(TRUE,0);
  for(i = 0; i < taille; i++){
    gtk_box_pack_start(GTK_BOX(pBox), pLabel[i], TRUE, TRUE, 0);
  }

  gtk_container_add(GTK_CONTAINER(pWindow), pBox);

  //test des fonctions
  printf("%d\n", elementCourant); //Element de base
  MenuDown(elems, pLabel, &elementCourant);
  MenuDown(elems, pLabel, &elementCourant);
  MenuUp(elems, pLabel, &elementCourant);
  MenuDown(elems, pLabel, &elementCourant);
  printf("%d\n", elementCourant); //Element final
  gtk_widget_show_all(pWindow);
  g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);
  gtk_main();
  return EXIT_SUCCESS;
}

void showCurrent(char **elems, GtkWidget **pLabel, int *elementCourant)
{
  char temp[300] = {};
  strcat(temp, "<span background=\"#8f8f8f\"><b>");
  strcat(temp, elems[*elementCourant-1]);
  strcat(temp, "</b></span>");
  gchar* newLabel = temp;
  gtk_label_set_markup(GTK_LABEL(pLabel[*elementCourant-1]), newLabel);
}

//Pré-requis: On a vérifié avant que l'élement courant n'est pas le premier
int MenuUp(char **elems, GtkWidget **pLabel, int *elementCourant)
{
  gtk_label_set_markup(GTK_LABEL(pLabel[*elementCourant-1]), elems[*elementCourant-1]);
  *elementCourant = *elementCourant - 1;
  showCurrent(elems, pLabel, &(*elementCourant));
  return *elementCourant;
}

//Pré-requis: On a vérifié avant que l'élement courant n'est pas le dernier
int MenuDown(char **elems, GtkWidget **pLabel, int *elementCourant)
{
  gtk_label_set_markup(GTK_LABEL(pLabel[*elementCourant-1]), elems[*elementCourant-1]);
  *elementCourant = *elementCourant + 1;
  showCurrent(elems, pLabel, &(*elementCourant));
  return *elementCourant;
}

int courant(int elementCourant)
{
  return elementCourant;
}

void OnDestroy(GtkWidget *pWidget, gpointer pData)
{
  gtk_main_quit();
}
