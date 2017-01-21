#include "Sdl_fenetres.h"

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
	 		return 4; // peserLoading()
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
		char* nomPhoto = "fond";
		char* chemin = NULL;
		chemin = malloc(100*sizeof(char));
		strcpy(chemin,CHEMIN_IMAGES_ALIMENTS);
	    strcat(chemin,nomPhoto);
		strcat(chemin,".bmp");

		photoPrise = prendrePhoto(nomPhoto);

		fic = fopen(chemin, "rb");
		if (!fic) {
			printf("Erreur ouverture fichier");
		}
		img = initImageBMP(fic);
		fclose(fic);
		remove(chemin);

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

	// On lance la premiere photo (fond) et on la contrôle
	FILE* fic;
	ImageBMP* img;
	int photoPrise;

	do {
		char* nomPhoto = "euhJeSaisPas";
		char* chemin = NULL;
		chemin = malloc(100*sizeof(char));
		strcpy(chemin,CHEMIN_IMAGES_ALIMENTS);
	    strcat(chemin,nomPhoto);
		strcat(chemin,".bmp");

		photoPrise = prendrePhoto(nomPhoto);

		fic = fopen(chemin, "rb");
		if (!fic) {
			printf("Erreur ouverture fichier");
		}
		img = initImageBMP(fic);
		fclose(fic);
		remove(chemin);

		if(estUni(img) != 1) {
			//On affiche un message attention si pas reconnu
			texteAttention = TTF_RenderText_Blended(getpolice(), "Attention aliment non detecté", couleurRouge);
			pos.x = (800-(texteAttention->w))/2;
			pos.y = 280;
			SDL_BlitSurface(texteAttention,NULL,screenSurface,&pos);
			SDL_UpdateWindowSurface(getwindow());
		}
	} while(estUni(img) != 1 || photoPrise != 1);

	return 5; // On passe a la prise de photo de l'aliment
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

	// Chargement des 5 aliments probable
	long int** listeIdDuree = getTabIdDureeAvantPer(5);
	int i;

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

	//Ajout boutton Autre aliment
	SDL_Rect bouttonAutre;
	bouttonAutre.x=objet6.x+10; bouttonAutre.y=objet6.y+10; bouttonAutre.w=160; bouttonAutre.h=160;
	SDL_FillRect(screenSurface,&bouttonAutre,SDL_MapRGB(screenSurface->format,211, 84, 0));

	//Texte Autre aliment
	texteAutres = TTF_RenderText_Blended(getpolice(), "Autres", couleurBlanc);
	larg = texteAutres->w;
	haut = texteAutres->h;
	pos.x =bouttonAutre.x + ((bouttonAutre.w-larg)/2); pos.y=bouttonAutre.y + ((bouttonAutre.h-haut)/2);
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
	 		return 1; // retour au menu Accueil
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
		return (336/duree);
	}
}

int stock() {
	SDL_Surface* screenSurface;
	SDL_Surface* texteTitre;
	SDL_Surface* texteMenu;
	SDL_Rect pos;
	SDL_Color couleurNoir = {0, 0, 0};
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
	texteTitre = TTF_RenderText_Blended(getpolice(), "Mon stock", couleurNoir);
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
	int i;

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
	barre1.x=(pos1.x)+40+pos1.w; barre1.y=pos1.y+15; barre1.w=(float)((float)1/(float)duree1)*600; barre1.h=30;
	barre2.x=(pos2.x)+40+pos2.w; barre2.y=pos2.y+15; barre2.w=(float)((float)1/(float)duree2)*600; barre2.h=30;
	barre3.x=(pos3.x)+40+pos3.w; barre3.y=pos3.y+15; barre3.w=(float)((float)1/(float)duree3)*600; barre3.h=30;
	barre4.x=(pos4.x)+40+pos4.w; barre4.y=pos4.y+15; barre4.w=(float)((float)1/(float)duree4)*600; barre4.h=30;
	barre5.x=(pos5.x)+40+pos5.w; barre5.y=pos5.y+15; barre5.w=(float)((float)1/(float)duree5)*600; barre5.h=30;
	SDL_FillRect(screenSurface,&barre1,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&barre2,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&barre3,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&barre4,SDL_MapRGB(screenSurface->format,192, 57, 43));
	SDL_FillRect(screenSurface,&barre5,SDL_MapRGB(screenSurface->format,192, 57, 43));

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
	    else {

	    }
	}
}
