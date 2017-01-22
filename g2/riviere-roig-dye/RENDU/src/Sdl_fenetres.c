#include "Sdl_fenetres.h"

// ---- CONSTANTES ---- //
const char* CHEMIN_PHOTO_FOND = "data/images_aliments/fond.bmp";
const char* CHEMIN_PHOTO_ALIMENT = "data/images_aliments/aliment.bmp";

// ---- FONCTIONS ---- //

int menu() {
	SDL_Surface* screenSurface;
	SDL_Surface* texteAjout;
	SDL_Surface* texteInv;
	SDL_Rect pos;

	// Fond d'écran
	screenSurface = SDL_GetWindowSurface(getwindow());
	SDL_Surface *fond_ecran = SDL_LoadBMP("data/images/fond_ecran.bmp");
	SDL_Rect pos_fond_ecran;
	pos_fond_ecran.x = 0; pos_fond_ecran.y = 0;
	SDL_BlitSurface(fond_ecran,NULL,screenSurface,&pos_fond_ecran);

	// Boutons menu
	SDL_Rect buttEnreg; SDL_Rect buttInv;
	buttEnreg.x=40; buttEnreg.y=40; buttEnreg.w=350; buttEnreg.h=400;
	buttInv.x=400; buttInv.y=40; buttInv.w=350; buttInv.h=400;

	SDL_FillRect(screenSurface,&buttEnreg,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&buttInv,SDL_MapRGB(screenSurface->format,211, 84, 0));

	// Texte boutons
	SDL_Color couleurBlanc = {255, 255, 255};
	texteAjout = TTF_RenderText_Blended(getpolice(), "Ajout d'un aliment", couleurBlanc);
	texteInv = TTF_RenderText_Blended(getpolice(), "Mon stock", couleurBlanc);

	int larg = texteAjout->w;
	int haut = texteAjout->h;
	pos.x=buttEnreg.x + ((buttEnreg.w-larg)/2); pos.y=buttEnreg.y + ((buttEnreg.h-haut)/2);

	SDL_BlitSurface(texteAjout,NULL,screenSurface,&pos);

	larg = texteInv->w;
	haut = texteInv->h;
	pos.x =buttInv.x + ((buttInv.w-larg)/2); pos.y=buttInv.y + ((buttInv.h-haut)/2);
	SDL_BlitSurface(texteInv,NULL,screenSurface,&pos);

	SDL_UpdateWindowSurface(getwindow());

	SDL_Event event;
	int loop = 1;
	while(loop == 1) {
		int x = -1; int y = -1;

	    SDL_WaitEvent(&event);
	    switch(event.type)
	    {
	        case SDL_MOUSEBUTTONUP:
	        	x = event.button.x;
	            y = event.button.y;
	            break;
	        case SDL_FINGERDOWN:
	        	x = event.tfinger.x;
	            y = event.tfinger.y;
	            break;
	        case SDL_KEYDOWN:
	            switch(event.key.keysym.sym)
	            {
	            	case SDLK_ESCAPE:
	                    loop= 0;
	                    return 0;
	                    break;
	                }
	                break;
	    }

	    if((x>=buttEnreg.x)&&(x<=(buttEnreg.x+buttEnreg.w))&&(y>=buttEnreg.y)&&(y<=(buttEnreg.y+buttEnreg.h))){
	 		return 2;
	    }
	    else if((x>=buttInv.x)&&(x<=(buttInv.x+buttInv.w))&&(y>=buttInv.y)&&(y<=(buttInv.y+buttInv.h))){
	 		return 3;
	    }
	    else{

	    }
	}
}

int peserPhoto(SDL_Surface* screenSurface){
	SDL_Surface* texteRetour;
	SDL_Rect pos;
	SDL_Surface* texteGo;

	// Fond d'écran
	SDL_Surface *fond_ecran = SDL_LoadBMP("data/images/fond_ecran.bmp");
	SDL_Rect pos_fond_ecran;
	pos_fond_ecran.x = 0; pos_fond_ecran.y = 0;
	SDL_BlitSurface(fond_ecran,NULL,screenSurface,&pos_fond_ecran);

	// Bouton Retour
	SDL_Rect buttRetour; SDL_Color couleurBlanc = {255, 255, 255};
	buttRetour.x=0; buttRetour.y=0; buttRetour.w=45; buttRetour.h=30;
	SDL_FillRect(screenSurface,&buttRetour,SDL_MapRGB(screenSurface->format,211, 84, 0));
	texteRetour = TTF_RenderText_Blended(getpolice(), "<", couleurBlanc);
	int larg = texteRetour->w;
	int haut = texteRetour->h;
	pos.x=buttRetour.x + ((buttRetour.w-larg)/2); pos.y=buttRetour.y + ((buttRetour.h-haut)/2);
	SDL_BlitSurface(texteRetour,NULL,screenSurface,&pos);

	// Boutons menu
	SDL_Rect buttGo;
	buttGo.x=225; buttGo.y=40; buttGo.w=350; buttGo.h=400;

	SDL_FillRect(screenSurface,&buttGo,SDL_MapRGB(screenSurface->format,192, 57, 43));

	// Texte boutons
	texteGo = TTF_RenderText_Blended(getpolice(), "Prendre Photo", couleurBlanc);

	larg = texteGo->w;
	haut = texteGo->h;
	pos.x = buttGo.x + ((buttGo.w-larg)/2); pos.y=buttGo.y + ((buttGo.h-haut)/2);

	SDL_BlitSurface(texteGo,NULL,screenSurface,&pos);

	SDL_UpdateWindowSurface(getwindow());
	SDL_Event event;
	int loop = 1;
	while(loop==1){
		int x = -1; int y = -1;
	    SDL_WaitEvent(&event);
	    switch(event.type)
		{
	        case SDL_MOUSEBUTTONUP:
	        	x = event.button.x;
	            y = event.button.y;
	            break;
	        case SDL_FINGERDOWN:
	        	x = event.tfinger.x;
	            y = event.tfinger.y;
	            break;
	        case SDL_KEYDOWN:

	            switch(event.key.keysym.sym) {
	            	case SDLK_ESCAPE:
	                    loop= 0;
	                    return 0;
	                    break;
	            }
	                break;
	    }

		// Clic Boutons
	    if((x>=buttRetour.x)&&(x<=(buttRetour.x+buttRetour.w))&&(y>=buttRetour.y)&&(y<=(buttRetour.y+buttRetour.h))){
	 		return 0; // Fermeture de la pesée
	    }
		else if((x>=buttGo.x)&&(x<=(buttGo.x+buttGo.w))&&(y>=buttGo.y)&&(y<=(buttGo.y+buttGo.h))){
	 		return 4; // peserLoading2()
	    }
	    else {

	    }
	}
}

int peserLoading(SDL_Surface* screenSurface) {
	SDL_Rect pos;
	SDL_Surface* texteTitre;
	SDL_Surface* texteAttention;
	SDL_Color couleurBlanc = {255, 255, 255};
	SDL_Color couleurRouge = {255, 0, 0};

	// Fond d'écran
	SDL_Surface *fond_ecran = SDL_LoadBMP("data/images/fond_ecran.bmp");
	SDL_Rect pos_fond_ecran;
	pos_fond_ecran.x = 0; pos_fond_ecran.y = 0;
	SDL_BlitSurface(fond_ecran,NULL,screenSurface,&pos_fond_ecran);

	// Afficher patientez
	texteTitre = TTF_RenderText_Blended(getpolice(), "Veuillez patienter", couleurBlanc);
	pos.x = (800-(texteTitre->w))/2;
	pos.y = 240;
	SDL_BlitSurface(texteTitre,NULL,screenSurface,&pos);

	SDL_UpdateWindowSurface(getwindow());

	// On lance la premiere photo (fond) et on la contrôle
	FILE* fic;
	ImageBMP* img;
	int photoPrise;

	do {
		photoPrise = prendrePhoto("fond");

		fic = fopen(CHEMIN_PHOTO_FOND, "rb");
		if (!fic) {
			printf("Erreur ouverture fichier");
		}
		img = initImageBMP(fic);
		fclose(fic);

		if(estUni(img) != 1) {
			//On affiche un message attention
			texteAttention = TTF_RenderText_Blended(getpolice(), "Attention fond non unie", couleurRouge);
			pos.x = (800-(texteAttention->w))/2;
			pos.y = 280;
			SDL_BlitSurface(texteAttention,NULL,screenSurface,&pos);
			SDL_UpdateWindowSurface(getwindow());
		}
	} while(estUni(img) != 1 || photoPrise != 1);

	return 3; // On passe a la prise de photo de l'aliment
}

int peserLoading2(SDL_Surface* screenSurface) {
	SDL_Rect pos;
	SDL_Surface* texteTitre;
	SDL_Surface* texteAttention;
	SDL_Color couleurBlanc = {255, 255, 255};
	SDL_Color couleurRouge = {255, 0, 0};

	// Fond d'écran
	SDL_Surface *fond_ecran = SDL_LoadBMP("data/images/fond_ecran.bmp");
	SDL_Rect pos_fond_ecran;
	pos_fond_ecran.x = 0; pos_fond_ecran.y = 0;
	SDL_BlitSurface(fond_ecran,NULL,screenSurface,&pos_fond_ecran);

	// Afficher patientez
	texteTitre = TTF_RenderText_Blended(getpolice(), "Veuillez patienter", couleurBlanc);
	pos.x = (800-(texteTitre->w))/2;
	pos.y = 240;
	SDL_BlitSurface(texteTitre,NULL,screenSurface,&pos);

	SDL_UpdateWindowSurface(getwindow());

	// On prend une nouvelle photo (aliment + fond) et on controle qu'il y ait bien un aliment
	FILE* fic;
	ImageBMP* img;
	int photoPrise;

	do {
		photoPrise = prendrePhoto("aliment");

		fic = fopen(CHEMIN_PHOTO_ALIMENT, "rb");
		if (!fic) {
			printf("Erreur ouverture fichier");
		}
		img = initImageBMP(fic);
		fclose(fic);

		// Si la photo est unie, soit l'aliment prend toute la photo, soit il n'y a pas d'aliment en plus du fond
		if(estUni(img) == 1) {
			// Message d'avertissement
			texteAttention = TTF_RenderText_Blended(getpolice(), "Attention aliment non detecté", couleurRouge);
			pos.x = (800-(texteAttention->w))/2;
			pos.y = 280;
			SDL_BlitSurface(texteAttention,NULL,screenSurface,&pos);
			SDL_UpdateWindowSurface(getwindow());
		}
	} while(estUni(img) == 1 || photoPrise != 1);

	return 5; // On passe au choix de l'aliment reconnu
}

int peserBase(SDL_Surface* screenSurface){
	SDL_Surface* texteRetour;
	SDL_Rect pos;
	SDL_Surface* texteGo;

	// Fond d'écran
	SDL_Surface *fond_ecran = SDL_LoadBMP("data/images/fond_ecran.bmp");
	SDL_Rect pos_fond_ecran;
	pos_fond_ecran.x = 0; pos_fond_ecran.y = 0;
	SDL_BlitSurface(fond_ecran,NULL,screenSurface,&pos_fond_ecran);

	// Bouton Retour
	SDL_Rect buttRetour; SDL_Color couleurBlanc = {255, 255, 255};
	buttRetour.x=0; buttRetour.y=0; buttRetour.w=45; buttRetour.h=30;
	SDL_FillRect(screenSurface,&buttRetour,SDL_MapRGB(screenSurface->format,211, 84, 0));
	texteRetour = TTF_RenderText_Blended(getpolice(), "<", couleurBlanc);
	int larg= texteRetour->w;
	int haut= texteRetour->h;
	pos.x=buttRetour.x + ((buttRetour.w-larg)/2); pos.y=buttRetour.y + ((buttRetour.h-haut)/2);
	SDL_BlitSurface(texteRetour,NULL,screenSurface,&pos);

	// Boutons menu
	SDL_Rect buttGo;
	buttGo.x=225; buttGo.y=40; buttGo.w=350; buttGo.h=400;

	SDL_FillRect(screenSurface,&buttGo,SDL_MapRGB(screenSurface->format,192, 57, 43));

	// Texte boutons
	texteGo = TTF_RenderText_Blended(getpolice(), "Initialiser", couleurBlanc);

	larg= texteGo->w;
	haut= texteGo->h;
	pos.x=buttGo.x + ((buttGo.w-larg)/2); pos.y=buttGo.y + ((buttGo.h-haut)/2);

	SDL_BlitSurface(texteGo,NULL,screenSurface,&pos);

	SDL_UpdateWindowSurface(getwindow());
	SDL_Event event;
	int loop = 1;
	while(loop==1){
		int x = -1; int y = -1;
	    SDL_WaitEvent(&event);
	    switch(event.type)
	    {
	        case SDL_MOUSEBUTTONUP:
	        	x = event.button.x;
	            y = event.button.y;
	            break;
	        case SDL_FINGERDOWN:
	        	x = event.tfinger.x;
	            y = event.tfinger.y;
	            break;
	        case SDL_KEYDOWN:
	            switch(event.key.keysym.sym)
	            {
	            	case SDLK_ESCAPE:
	                    loop= 0;
	                    return 0;
	                    break;
	                }
	                break;
	    }
	    if((x>=buttRetour.x)&&(x<=(buttRetour.x+buttRetour.w))&&(y>=buttRetour.y)&&(y<=(buttRetour.y+buttRetour.h))){
	 		return 0; // Sortie du programme
	    }
		else if((x>=buttGo.x)&&(x<=(buttGo.x+buttGo.w))&&(y>=buttGo.y)&&(y<=(buttGo.y+buttGo.h))){
	 		return 2; // On passe au menu peser()
	    }
	    else{

	    }
	}
}

int peserChoix() {

	SDL_Surface* screenSurface;
	SDL_Surface* texteTitre;
	SDL_Surface* texteMenu;
	SDL_Surface* texteAutres;
	SDL_Rect pos;
	SDL_Color couleurBlanc = {255, 255, 255};
	SDL_Color couleurNoir = {0, 0, 0};

	// Fond d'écran
	screenSurface = SDL_GetWindowSurface(getwindow());
	SDL_Surface *fond_ecran = SDL_LoadBMP("data/images/fond_ecran.bmp");
	SDL_Rect pos_fond_ecran;
	pos_fond_ecran.x = 0; pos_fond_ecran.y = 0;
	SDL_BlitSurface(fond_ecran,NULL,screenSurface,&pos_fond_ecran);

	SDL_Rect objet1;SDL_Rect objet2; SDL_Rect objet3; SDL_Rect objet4; SDL_Rect objet5; SDL_Rect objet6;
	objet1.x=130; objet1.y=60; objet1.w=180; objet1.h=180;
	objet2.x=310; objet2.y=60; objet2.w=180; objet2.h=180;
	objet3.x=490; objet3.y=60; objet3.w=180; objet3.h=180;
	objet4.x=130; objet4.y=240; objet4.w=180; objet4.h=180;
	objet5.x=310; objet5.y=240; objet5.w=180; objet5.h=180;
	objet6.x=490; objet6.y=240; objet6.w=180; objet6.h=180;

	SDL_FillRect(screenSurface,&objet1,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&objet2,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&objet3,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&objet4,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&objet5,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&objet6,SDL_MapRGB(screenSurface->format,192, 57, 43));

	// Texte haut
	texteTitre = TTF_RenderText_Blended(getpolice(), "Choisissez votre aliment", couleurNoir);
	pos.x = (800-(texteTitre->w))/2;
	pos.y = 10;
	SDL_BlitSurface(texteTitre,NULL,screenSurface,&pos);

	// Bouton Menu
	SDL_Rect buttMenu;
	buttMenu.x=0; buttMenu.y=0; buttMenu.w=45; buttMenu.h=30;
	SDL_FillRect(screenSurface,&buttMenu,SDL_MapRGB(screenSurface->format,211, 84, 0));
	texteMenu = TTF_RenderText_Blended(getpolice(), "<", couleurBlanc);
	int larg = texteMenu->w;
	int haut = texteMenu->h;
	pos.x = buttMenu.x + ((buttMenu.w-larg)/2);
	pos.y = buttMenu.y + ((buttMenu.h-haut)/2);
	SDL_BlitSurface(texteMenu,NULL,screenSurface,&pos);

	// Couleur du fond
	FILE* ficFond;
	ImageBMP* imgFond;

	ficFond = fopen(CHEMIN_PHOTO_FOND,"rb");
	imgFond = initImageBMP(ficFond);
	Couleur* coulFond = initCouleur();
	coulFond = couleurDominante(imgFond);
	printf("\nCouleur Fond = %s",toCharCouleur(coulFond));

	fclose(ficFond);
	remove(CHEMIN_PHOTO_FOND);

	// Récupération de la couleur de l'aliment pris en photo
	FILE* photo = fopen(CHEMIN_PHOTO_ALIMENT,"rb");
	ImageBMP* img = initImageBMP(photo);
	Couleur* coulAlim = initCouleur();
	coulAlim = couleurDominanteHorsFond(img,coulFond);
	printf("\nCouleur Aliment = %s",toCharCouleur(coulAlim));

	fclose(photo);
	remove(CHEMIN_PHOTO_ALIMENT);

	// Chargement des 5 aliments probables
	// TODO : getIdAlimentParCouleur doit pouvoir prendre un offset en paramètre (pour l'instant il renvoie 5 alims)
	int seuil = 60;
	int* listeAlim = getIdAlimentParCouleur(coulAlim,seuil);
	printf("\nSeuil = %d",seuil);

	// Construction du chemin vers l'image
	char* chemin1 = malloc(100*sizeof(char*));
	strcpy(chemin1,CHEMIN_IMAGES_ALIMENTS);
	char* idchar1 = malloc(4*sizeof(char));
	sprintf(idchar1,"%d",listeAlim[0]);
	strcat(chemin1,idchar1);
	strcat(chemin1,".bmp");

	char* chemin2 = malloc(100*sizeof(char*));
	strcpy(chemin2,CHEMIN_IMAGES_ALIMENTS);
	char* idchar2 = malloc(4*sizeof(char));
	sprintf(idchar2,"%d",listeAlim[1]);
	strcat(chemin2,idchar2);
	strcat(chemin2,".bmp");

	char* chemin3 = malloc(100*sizeof(char*));
	strcpy(chemin3,CHEMIN_IMAGES_ALIMENTS);
	char* idchar3 = malloc(4*sizeof(char));
	sprintf(idchar3,"%d",listeAlim[2]);
	strcat(chemin3,idchar3);
	strcat(chemin3,".bmp");

	char* chemin4 = malloc(100*sizeof(char*));
	strcpy(chemin4,CHEMIN_IMAGES_ALIMENTS);
	char* idchar4 = malloc(4*sizeof(char));
	sprintf(idchar4,"%d",listeAlim[3]);
	strcat(chemin4,idchar4);
	strcat(chemin4,".bmp");

	char* chemin5 = malloc(100*sizeof(char*));
	strcpy(chemin5,CHEMIN_IMAGES_ALIMENTS);
	char* idchar5 = malloc(4*sizeof(char));
	sprintf(idchar5,"%d",listeAlim[4]);
	strcat(chemin5,idchar5);
	strcat(chemin5,".bmp");

	// Images
	SDL_Surface *image1 = SDL_LoadBMP(chemin1);
	SDL_Surface *image2 = SDL_LoadBMP(chemin2);
	SDL_Surface *image3 = SDL_LoadBMP(chemin3);
	SDL_Surface *image4 = SDL_LoadBMP(chemin4);
	SDL_Surface *image5 = SDL_LoadBMP(chemin5);

	// Redimensionnement des images (170x170 pixels)
	// Librairie SDL_gfx, fonction zoomSurface() sur les images
	// Les images étant carrées, on ne récupère que la hauteur
	int h1 = image1->h;
	double zoom1 = 160 / (double)h1;
	image1 = zoomSurface(image1,zoom1,zoom1,0);

	int h2 = image2->h;
	double zoom2 = 160 / (double)h2;
	image2 = zoomSurface(image2,zoom2,zoom2,0);

	int h3 = image3->h;
	double zoom3 = 160 / (double)h3;
	image3 = zoomSurface(image3,zoom3,zoom3,0);

	int h4 = image4->h;
	double zoom4 = 160 / (double)h4;
	image4 = zoomSurface(image4,zoom4,zoom4,0);

	int h5 = image5->h;
	double zoom5 = 160 / (double)h5;
	image5 = zoomSurface(image5,zoom5,zoom5,0);

	// Positionnement des images
	SDL_Rect pos1;
	pos1.x = objet1.x+10; pos1.y = objet1.y+10;
	SDL_Rect pos2;
	pos2.x = objet2.x+10; pos2.y = objet2.y+10;
	SDL_Rect pos3;
	pos3.x = objet3.x+10; pos3.y = objet3.y+10;
	SDL_Rect pos4;
	pos4.x = objet4.x+10; pos4.y = objet4.y+10;
	SDL_Rect pos5;
	pos5.x = objet5.x+10; pos5.y = objet5.y+10;

	// Blittage des images
	SDL_BlitSurface(image1,NULL,screenSurface,&pos1);
	SDL_BlitSurface(image2,NULL,screenSurface,&pos2);
	SDL_BlitSurface(image3,NULL,screenSurface,&pos3);
	SDL_BlitSurface(image4,NULL,screenSurface,&pos4);
	SDL_BlitSurface(image5,NULL,screenSurface,&pos5);

	// Ajout boutton Autre aliment
	SDL_Rect bouttonAutre;
	bouttonAutre.x=objet6.x+10; bouttonAutre.y=objet6.y+10; bouttonAutre.w=160; bouttonAutre.h=160;
	SDL_FillRect(screenSurface,&bouttonAutre,SDL_MapRGB(screenSurface->format,211, 84, 0));

	// Texte Autre aliment
	texteAutres = TTF_RenderText_Blended(getpolice(), "Autres", couleurBlanc);
	larg = texteAutres->w;
	haut = texteAutres->h;
	pos.x = bouttonAutre.x + ((bouttonAutre.w-larg)/2); pos.y=bouttonAutre.y + ((bouttonAutre.h-haut)/2);
	SDL_BlitSurface(texteAutres,NULL,screenSurface,&pos);

	SDL_UpdateWindowSurface(getwindow());

	SDL_Event event;
	int loop = 1;
	while(loop==1){
		int x = -1; int y = -1;
	    SDL_WaitEvent(&event);
	    switch(event.type)
	    {
	        case SDL_MOUSEBUTTONUP:
	        	x = event.button.x;
	            y = event.button.y;
	            break;
	        case SDL_FINGERDOWN:
	        	x = event.tfinger.x;
	            y = event.tfinger.y;
	            break;
	        case SDL_KEYDOWN:
	            switch(event.key.keysym.sym)
	            {
	            	case SDLK_ESCAPE:
	                    loop= 0;
	                    return 0;
	                    break;
	                }
	                break;
	    }
	    if((x>=buttMenu.x)&&(x<=(buttMenu.x+buttMenu.w))&&(y>=buttMenu.y)&&(y<=(buttMenu.y+buttMenu.h))){
	 		return 0; // retour au menu Accueil
	    }
		else if((x>=bouttonAutre.x)&&(x<=(bouttonAutre.x+bouttonAutre.w))&&(y>=bouttonAutre.y)&&(y<=(bouttonAutre.y+bouttonAutre.h))){
	 		return 6; // On passe au choix dans la liste des aliments complete
	    }
	    else if((x>=objet1.x)&&(x<=(objet1.x+objet1.w))&&(y>=objet1.y)&&(y<=(objet1.y+objet1.h))){
	 		if(listeAlim[0]!=0){
	 		char * desc = "Une pesee";
	 		int marche2 = ecrireDonneePesee(1,desc,listeAlim[0]);
	 		}
	 		return 0;
	    }
	   	else if((x>=objet2.x)&&(x<=(objet2.x+objet2.w))&&(y>=objet2.y)&&(y<=(objet2.y+objet2.h))){
	 		if(listeAlim[1]!=0){
	 		char * desc = "Une pesee";
	 		int marche2 = ecrireDonneePesee(1,desc,listeAlim[1]);
	 		}
	 		return 0;
	    }
	    else if((x>=objet3.x)&&(x<=(objet3.x+objet3.w))&&(y>=objet3.y)&&(y<=(objet3.y+objet3.h))){
	 		if(listeAlim[2]!=0){
	 		char * desc = "Une pesee";
	 		int marche2 = ecrireDonneePesee(1,desc,listeAlim[2]);
	 		}
	 		return 0;
	    }
	    else if((x>=objet4.x)&&(x<=(objet4.x+objet4.w))&&(y>=objet4.y)&&(y<=(objet4.y+objet4.h))){
	 		if(listeAlim[3]!=0){
	 		char * desc = "Une pesee";
	 		int marche2 = ecrireDonneePesee(1,desc,listeAlim[3]);
	 		}
	 		return 0;
	    }
	    else if((x>=objet5.x)&&(x<=(objet5.x+objet5.w))&&(y>=objet5.y)&&(y<=(objet5.y+objet5.h))){
	 		if(listeAlim[4]!=0){
	 		char * desc = "Une pesee";
	 		int marche2 = ecrireDonneePesee(1,desc,listeAlim[4]);
	 		}
	 		return 0;
	    }
	    else {

	    }
	}
}

int peserChoixComplet() {

	SDL_Surface* screenSurface;
	SDL_Surface* texteTitre;
	SDL_Surface* texteMenu;
	SDL_Surface* texteAutres;
	SDL_Rect pos;
	SDL_Color couleurBlanc = {255, 255, 255};
	SDL_Color couleurNoir = {0, 0, 0};

	// Fond d'écran
	screenSurface = SDL_GetWindowSurface(getwindow());
	SDL_Surface *fond_ecran = SDL_LoadBMP("data/images/fond_ecran.bmp");
	SDL_Rect pos_fond_ecran;
	pos_fond_ecran.x = 0; pos_fond_ecran.y = 0;
	SDL_BlitSurface(fond_ecran,NULL,screenSurface,&pos_fond_ecran);


	// Texte haut
	texteTitre = TTF_RenderText_Blended(getpolice(), "Choisissez votre aliment", couleurNoir);
	pos.x = (800-(texteTitre->w))/2;
	pos.y = 10;
	SDL_BlitSurface(texteTitre,NULL,screenSurface,&pos);

	// Bouton Menu
	SDL_Rect buttMenu;
	buttMenu.x=0; buttMenu.y=0; buttMenu.w=45; buttMenu.h=30;
	SDL_FillRect(screenSurface,&buttMenu,SDL_MapRGB(screenSurface->format,211, 84, 0));
	texteMenu = TTF_RenderText_Blended(getpolice(), "<", couleurBlanc);
	int larg = texteMenu->w;
	int haut = texteMenu->h;
	pos.x = buttMenu.x + ((buttMenu.w-larg)/2);
	pos.y = buttMenu.y + ((buttMenu.h-haut)/2);
	SDL_BlitSurface(texteMenu,NULL,screenSurface,&pos);

	// Chargement des 24 aliments probables
	int* listeAlim = getIdsAliments(24);

	//Affichage de la grille
	int i,j;
	for(i=0; i<4; i++){
		for(j=0; j<6; j++){
			SDL_Rect objet;
			objet.x=100+(100*j); objet.y=60+(100*i); objet.w=100; objet.h=100;
			SDL_FillRect(screenSurface,&objet,SDL_MapRGB(screenSurface->format,192, 57, 43));
			// Construction du chemin vers l'image
			char* chemin = malloc(100*sizeof(char*));
			strcpy(chemin,CHEMIN_IMAGES_ALIMENTS);
			char* idchar = malloc(4*sizeof(char));
			sprintf(idchar,"%d",listeAlim[(i*6)+j]);
			strcat(chemin,idchar);
			strcat(chemin,".bmp");
			// Images
			SDL_Surface *image = SDL_LoadBMP(chemin);
			// Redimensionnement des images (170x170 pixels)
			// Librairie SDL_gfx, fonction zoomSurface() sur les images
			// Les images étant carrées, on ne récupère que la hauteur
			int h = image->h;
			double zoom = 80 / (double)h;
			image = zoomSurface(image,zoom,zoom,0);
			// Positionnement des images
			SDL_Rect pos;
			pos.x = objet.x+10; pos.y = objet.y+10;
			SDL_BlitSurface(image,NULL,screenSurface,&pos);

		}
	}
	SDL_UpdateWindowSurface(getwindow());

	SDL_Event event;
	int loop = 1;
	while(loop==1){
		int x = -1; int y = -1;
	    SDL_WaitEvent(&event);
	    switch(event.type)
	    {
	        case SDL_MOUSEBUTTONUP:
	        	x = event.button.x;
	            y = event.button.y;
	            break;
	        case SDL_FINGERDOWN:
	        	x = event.tfinger.x;
	            y = event.tfinger.y;
	            break;
	        case SDL_KEYDOWN:
	            switch(event.key.keysym.sym)
	            {
	            	case SDLK_ESCAPE:
	                    loop= 0;
	                    return 0;
	                    break;
	                }
	                break;
	    }
	    if((x>=buttMenu.x)&&(x<=(buttMenu.x+buttMenu.w))&&(y>=buttMenu.y)&&(y<=(buttMenu.y+buttMenu.h))){
	 		return 0; // retour au menu Accueil
	    }
	   else if((y>40)&&(y<140)){
	 		if((x>=100)&&(x<200)){
	 			if(listeAlim[0]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[0]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=200)&&(x<300)){
	 			if(listeAlim[1]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[1]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=300)&&(x<400)){
	 			if(listeAlim[2]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[2]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=400)&&(x<500)){
	 			if(listeAlim[3]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[3]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=500)&&(x<600)){
	 			if(listeAlim[4]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[4]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=600)&&(x<700)){
	 			if(listeAlim[5]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[5]);
	 			}
	 			return 0;
	 		}

	    }
	   else if((y>140)&&(y<240)){
	 		if((x>=100)&&(x<200)){
	 			if(listeAlim[6]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[6]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=200)&&(x<300)){
	 			if(listeAlim[7]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[7]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=300)&&(x<400)){
	 			if(listeAlim[8]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[8]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=400)&&(x<500)){
	 			if(listeAlim[9]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[9]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=500)&&(x<600)){
	 			if(listeAlim[10]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[10]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=600)&&(x<700)){
	 			if(listeAlim[11]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[11]);
	 			}
	 			return 0;
	 		}

	    }
	    else if((y>=240)&&(y<340)){
	 		if((x>=100)&&(x<200)){
	 			if(listeAlim[12]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[12]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=200)&&(x<300)){
	 			if(listeAlim[13]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[13]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=300)&&(x<400)){
	 			if(listeAlim[14]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[14]);
	 			}
	 			return 1;
	 		}
	 		else if((x>=400)&&(x<500)){
	 			if(listeAlim[15]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[15]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=500)&&(x<600)){
	 			if(listeAlim[16]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[16]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=600)&&(x<700)){
	 			if(listeAlim[17]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[17]);
	 			}
	 			return 0;
	 		}

	    }
	    else if((y>=340)&&(y<440)){
	 		if((x>=100)&&(x<200)){
	 			if(listeAlim[18]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[18]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=200)&&(x<300)){
	 			if(listeAlim[19]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[19]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=300)&&(x<400)){
	 			if(listeAlim[20]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[20]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=400)&&(x<500)){
	 			if(listeAlim[21]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[21]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=500)&&(x<600)){
	 			if(listeAlim[22]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[22]);
	 			}
	 			return 0;
	 		}
	 		else if((x>=600)&&(x<700)){
	 			if(listeAlim[23]!=0){
	 			char * desc = "Une pesee";
	 			int marche2 = ecrireDonneePesee(1,desc,listeAlim[23]);
	 			}
	 			return 0;
	 		}

	    }
	    else {

	    }
	}
}


int peser() {
	SDL_Surface* screenSurface;
	screenSurface = SDL_GetWindowSurface(getwindow());

	int loop = 1;
	int page = 1;

	while(loop==1) {
		if(page==1) page = peserBase(screenSurface);
		else if(page==2) page = peserLoading(screenSurface);
		else if(page==3) page = peserPhoto(screenSurface);
		else if(page==4) page = peserLoading2(screenSurface);
		else if(page==5) page = peserChoix(screenSurface);
		else if(page==6) page = peserChoixComplet(screenSurface);
		else if(page==0) loop = 0;
	}

	return 1; // retour au menu Accueil
}

int rapport14J(int duree){
	if(duree<=0){
		return 0;
	}
	else if(duree >= 336){
		return 100;
	}
	else{
		return ((float)duree/336)*100;
	}
}

int stock() {
	SDL_Surface* screenSurface;
	SDL_Surface* texteTitre;
	SDL_Surface* texteMenu;
	SDL_Rect pos;
	SDL_Color couleurNoir = {138, 138, 138};
	SDL_Color couleurBlanc = {255, 255, 255};


	// Fond d'écran
	screenSurface = SDL_GetWindowSurface(getwindow());
	SDL_Surface *fond_ecran = SDL_LoadBMP("data/images/fond_ecran.bmp");
	SDL_Rect pos_fond_ecran;
	pos_fond_ecran.x = 0; pos_fond_ecran.y = 0;
	SDL_BlitSurface(fond_ecran,NULL,screenSurface,&pos_fond_ecran);





	SDL_Rect objet1;SDL_Rect objet2; SDL_Rect objet3; SDL_Rect objet4; SDL_Rect objet5;
	objet1.x=40; objet1.y=40; objet1.w=60; objet1.h=60;
	objet2.x=40; objet2.y=125; objet2.w=60; objet2.h=60;
	objet3.x=40; objet3.y=210; objet3.w=60; objet3.h=60;
	objet4.x=40; objet4.y=295; objet4.w=60; objet4.h=60;
	objet5.x=40; objet5.y=380; objet5.w=60; objet5.h=60;
	SDL_FillRect(screenSurface,&objet1,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&objet2,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&objet3,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&objet4,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&objet5,SDL_MapRGB(screenSurface->format,192, 57, 43));

	// Texte
	texteTitre = TTF_RenderText_Blended(getpolice(), "     Mon stock                                 7J                                      14J", couleurNoir);
	pos.x = (800-(texteTitre->w))/2;
	pos.y = 10;
	SDL_BlitSurface(texteTitre,NULL,screenSurface,&pos);

	// Bouton Menu
	SDL_Rect buttMenu;
	buttMenu.x=0; buttMenu.y=0; buttMenu.w=45; buttMenu.h=30;
	SDL_FillRect(screenSurface,&buttMenu,SDL_MapRGB(screenSurface->format,211, 84, 0));
	texteMenu = TTF_RenderText_Blended(getpolice(), "<", couleurBlanc);
	int larg = texteMenu->w;
	int haut = texteMenu->h;
	pos.x = buttMenu.x + ((buttMenu.w-larg)/2);
	pos.y = buttMenu.y + ((buttMenu.h-haut)/2);
	SDL_BlitSurface(texteMenu,NULL,screenSurface,&pos);

	// Chargement des 5 aliments qui vont bientôt périmer
	long int** listeIdDuree = getTabIdDureeAvantPer(5);

	// Construction du chemin vers l'image
	char* chemin1 = malloc(100*sizeof(char*));
	strcpy(chemin1,CHEMIN_IMAGES_ALIMENTS);
	char* idchar1 = malloc(4*sizeof(char));
	sprintf(idchar1,"%ld",listeIdDuree[0][0]);
	strcat(chemin1,idchar1);
	strcat(chemin1,".bmp");

	char* chemin2 = malloc(100*sizeof(char*));
	strcpy(chemin2,CHEMIN_IMAGES_ALIMENTS);
	char* idchar2 = malloc(4*sizeof(char));
	sprintf(idchar2,"%ld",listeIdDuree[1][0]);
	strcat(chemin2,idchar2);
	strcat(chemin2,".bmp");

	char* chemin3 = malloc(100*sizeof(char*));
	strcpy(chemin3,CHEMIN_IMAGES_ALIMENTS);
	char* idchar3 = malloc(4*sizeof(char));
	sprintf(idchar3,"%ld",listeIdDuree[2][0]);
	strcat(chemin3,idchar3);
	strcat(chemin3,".bmp");

	char* chemin4 = malloc(100*sizeof(char*));
	strcpy(chemin4,CHEMIN_IMAGES_ALIMENTS);
	char* idchar4 = malloc(4*sizeof(char));
	sprintf(idchar4,"%ld",listeIdDuree[3][0]);
	strcat(chemin4,idchar4);
	strcat(chemin4,".bmp");

	char* chemin5 = malloc(100*sizeof(char*));
	strcpy(chemin5,CHEMIN_IMAGES_ALIMENTS);
	char* idchar5 = malloc(4*sizeof(char));
	sprintf(idchar5,"%ld",listeIdDuree[4][0]);
	strcat(chemin5,idchar5);
	strcat(chemin5,".bmp");

	// Images
	SDL_Surface *image1 = SDL_LoadBMP(chemin1);
	SDL_Surface *image2 = SDL_LoadBMP(chemin2);
	SDL_Surface *image3 = SDL_LoadBMP(chemin3);
	SDL_Surface *image4 = SDL_LoadBMP(chemin4);
	SDL_Surface *image5 = SDL_LoadBMP(chemin5);

	// Redimensionnement des images (60x60 pixels)
	// Librairie SDL_gfx, fonction zoomSurface() sur les images
	// Les images étant carrées, on ne récupère que la hauteur
	int h1 = image1->h;
	double zoom1 = 60 / (double)h1;
	image1 = zoomSurface(image1,zoom1,zoom1,0);

	int h2 = image2->h;
	double zoom2 = 60 / (double)h2;
	image2 = zoomSurface(image2,zoom2,zoom2,0);

	int h3 = image3->h;
	double zoom3 = 60 / (double)h3;
	image3 = zoomSurface(image3,zoom3,zoom3,0);

	int h4 = image4->h;
	double zoom4 = 60 / (double)h4;
	image4 = zoomSurface(image4,zoom4,zoom4,0);

	int h5 = image5->h;
	double zoom5 = 60 / (double)h5;
	image5 = zoomSurface(image5,zoom5,zoom5,0);

	// Positionnement des images
	SDL_Rect pos1;
	pos1.x = objet1.x; pos1.y = objet1.y;
	SDL_Rect pos2;
	pos2.x = objet2.x; pos2.y = objet2.y;
	SDL_Rect pos3;
	pos3.x = objet3.x; pos3.y = objet3.y;
	SDL_Rect pos4;
	pos4.x = objet4.x; pos4.y = objet4.y;
	SDL_Rect pos5;
	pos5.x = objet5.x; pos5.y = objet5.y;

	// Blittage des images
	SDL_BlitSurface(image1,NULL,screenSurface,&pos1);
	SDL_BlitSurface(image2,NULL,screenSurface,&pos2);
	SDL_BlitSurface(image3,NULL,screenSurface,&pos3);
	SDL_BlitSurface(image4,NULL,screenSurface,&pos4);
	SDL_BlitSurface(image5,NULL,screenSurface,&pos5);

	//Ligne vertical
	SDL_Rect interface7J; SDL_Rect interface14J;
	interface7J.x=(objet1.x)+40+objet1.w+300; interface7J.y=objet1.y; interface7J.w=2; interface7J.h=400;
	interface14J.x=(objet1.x)+40+objet1.w+600; interface14J.y=objet1.y; interface14J.w=2; interface14J.h=400;
	SDL_FillRect(screenSurface,&interface7J,SDL_MapRGB(screenSurface->format,138, 138, 138));
	SDL_FillRect(screenSurface,&interface14J,SDL_MapRGB(screenSurface->format,138, 138, 138));

	// Durée de péremption
	long int duree1 = listeIdDuree[0][1];
	long int duree2 = listeIdDuree[1][1];
	long int duree3 = listeIdDuree[2][1];
	long int duree4 = listeIdDuree[3][1];
	long int duree5 = listeIdDuree[4][1];

	// Conversion en heures
	duree1 = duree1 / 3600;
	duree2 = duree2 / 3600;
	duree3 = duree3 / 3600;
	duree4 = duree4 / 3600;
	duree5 = duree5 / 3600;

	//Conversion en rapport à 2 semaines
	//336h dans deux semaines
	duree1 = rapport14J(duree1);
	duree2 = rapport14J(duree2);
	duree3 = rapport14J(duree3);
	duree4 = rapport14J(duree4);
	duree5 = rapport14J(duree5);

	//Affichage barre duree peremption
	SDL_Rect barre1;
	SDL_Rect barre2;
	SDL_Rect barre3;
	SDL_Rect barre4;
	SDL_Rect barre5;
	barre1.x=(pos1.x)+40+pos1.w; barre1.y=pos1.y+15; barre1.w=(float)((float)duree1/100)*600; barre1.h=30;
	barre2.x=(pos2.x)+40+pos2.w; barre2.y=pos2.y+15; barre2.w=(float)((float)duree2/100)*600; barre2.h=30;
	barre3.x=(pos3.x)+40+pos3.w; barre3.y=pos3.y+15; barre3.w=(float)((float)duree3/100)*600; barre3.h=30;
	barre4.x=(pos4.x)+40+pos4.w; barre4.y=pos4.y+15; barre4.w=(float)((float)duree4/100)*600; barre4.h=30;
	barre5.x=(pos5.x)+40+pos5.w; barre5.y=pos5.y+15; barre5.w=(float)((float)duree5/100)*600; barre5.h=30;


	if(duree1<=30){
		SDL_FillRect(screenSurface,&barre1,SDL_MapRGB(screenSurface->format,192, 57, 43));
	}
	else if (duree1<=60){
		SDL_FillRect(screenSurface,&barre1,SDL_MapRGB(screenSurface->format,230, 126, 34));
	}
	else{
		SDL_FillRect(screenSurface,&barre1,SDL_MapRGB(screenSurface->format,46, 204, 113));
	}

	if(duree2<=30){
		SDL_FillRect(screenSurface,&barre2,SDL_MapRGB(screenSurface->format,192, 57, 43));
	}
	else if (duree2<=60){
		SDL_FillRect(screenSurface,&barre2,SDL_MapRGB(screenSurface->format,230, 126, 34));
	}
	else{
		SDL_FillRect(screenSurface,&barre2,SDL_MapRGB(screenSurface->format,46, 204, 113));
	}

	if(duree3<=30){
		SDL_FillRect(screenSurface,&barre3,SDL_MapRGB(screenSurface->format,192, 57, 43));
	}
	else if (duree3<=60){
		SDL_FillRect(screenSurface,&barre3,SDL_MapRGB(screenSurface->format,230, 126, 34));
	}
	else{
		SDL_FillRect(screenSurface,&barre3,SDL_MapRGB(screenSurface->format,46, 204, 113));
	}

	if(duree4<=30){
		SDL_FillRect(screenSurface,&barre4,SDL_MapRGB(screenSurface->format,192, 57, 43));
	}
	else if (duree4<=60){
		SDL_FillRect(screenSurface,&barre4,SDL_MapRGB(screenSurface->format,230, 126, 34));
	}
	else{
		SDL_FillRect(screenSurface,&barre4,SDL_MapRGB(screenSurface->format,46, 204, 113));
	}

	if(duree5<=30){
		SDL_FillRect(screenSurface,&barre5,SDL_MapRGB(screenSurface->format,192, 57, 43));
	}
	else if (duree5<=60){
		SDL_FillRect(screenSurface,&barre5,SDL_MapRGB(screenSurface->format,230, 126, 34));
	}
	else{
		SDL_FillRect(screenSurface,&barre5,SDL_MapRGB(screenSurface->format,46, 204, 113));
	}



	SDL_UpdateWindowSurface(getwindow());

	SDL_Event event;
	int loop = 1;
	while(loop==1){
		int x = -1; int y = -1;
	    SDL_WaitEvent(&event);
	    switch(event.type)
	    {
	        case SDL_MOUSEBUTTONUP:
	        	x = event.button.x;
	            y = event.button.y;
	            break;
	        case SDL_FINGERDOWN:
	        	x = event.tfinger.x;
	            y = event.tfinger.y;
	            break;
	        case SDL_KEYDOWN:
	            switch(event.key.keysym.sym)
	            {
	            	case SDLK_ESCAPE:
	                    loop= 0;
	                    return 0;
	                    break;
	                }
	                break;
	    }
	    if((x>=buttMenu.x)&&(x<=(buttMenu.x+buttMenu.w))&&(y>=buttMenu.y)&&(y<=(buttMenu.y+buttMenu.h))){
	 		return 1; // retour au menu Accueil
	    }
	    else if((x>=objet1.x)&&(x<=(objet1.x+objet1.w))&&(y>=objet1.y)&&(y<=(objet1.y+objet1.h))){
	 		int marche=0;
	 		marche = supprimerDonneePesee(listeIdDuree[0][0]);
	 		return 3; // retour au menu Accueil
	    }
	    else if((x>=objet2.x)&&(x<=(objet2.x+objet2.w))&&(y>=objet2.y)&&(y<=(objet2.y+objet2.h))){
	 		int marche=0;
	 		marche = supprimerDonneePesee(listeIdDuree[1][0]);
	 		return 3; // retour au menu Accueil
	    }
	    else if((x>=objet3.x)&&(x<=(objet3.x+objet3.w))&&(y>=objet3.y)&&(y<=(objet3.y+objet3.h))){
	 		int marche=0;
	 		marche = supprimerDonneePesee(listeIdDuree[2][0]);
	 		return 3; // retour au menu Accueil
	    }
	    else if((x>=objet4.x)&&(x<=(objet4.x+objet4.w))&&(y>=objet4.y)&&(y<=(objet4.y+objet4.h))){
	 		int marche=0;
	 		marche = supprimerDonneePesee(listeIdDuree[3][0]);
	 		return 3; // retour au menu Accueil
		}
	    else if((x>=objet5.x)&&(x<=(objet5.x+objet5.w))&&(y>=objet5.y)&&(y<=(objet5.y+objet5.h))){
	 		int marche=0;
	 		marche = supprimerDonneePesee(listeIdDuree[4][0]);
	 		return 3; // retour au menu Accueil
	    }

	}
}
