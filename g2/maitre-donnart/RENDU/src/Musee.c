#include "grovepi.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fmod.h>


#define us_cmd 7

/* Variables globales */
FMOD_SYSTEM *systeme; /* Système audio */
FMOD_CHANNEL *canal1, *canal2; /* Différents channel audio */
int etape; /* Etape actuelle */
int currentQuestion; /* Question actuelle */
time_t updateSon; /* Permet d'aller dans le fonction changer son toutes les 5 secondes */
int playingCurrent = 0; /* Booleen qui permet de savoir si un fichier audio est en train d'être joué */
int questionTime = 0; /* Permet de savoir si on est à l'étape des questions */
int reponseTime = 0; /* Permet de savoir si on est à l'étape des réponses */
int playingCurQuestion = 0; /* Permet de savoir si l'audio d'une question est en train d'être joué */
int total = 0; /* Total des réponses juste à un quizz */
FMOD_SOUND *rep0, *rep1, *rep2, *rep3, *rep4, *rep5; /* Les différents sons des réponses */
FMOD_SOUND *pres, *choix, *description, *dgauche, *ddroite, *quizz, *quizzg, *quizzd, *arret, *bruit, *musique; /* Les différentes sons des titres*/
enum capteurs {GAUCHE, CENTRE, DROITE}; /*Enumération pour faciliter l'utilisation des capteurs */


/* Configuration */
int valeurMaxSon = 200;
int DistMin = 30;
int DistMax = 50;

/* Structure permettant de représenter une question */
struct sQuestion { 
    FMOD_SOUND *son; /* Le son lié à la question */
    char reponse; /* Sa réponse */
};
typedef struct sQuestion question;

question Quest[10]; /* Il y a en tout 10 questions */

/* Initialise les fichiers audio des questions */
int initQuestions()
{
    FMOD_System_CreateStream(systeme, "questions/q1q1.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &Quest[0].son);
    Quest[0].reponse = 'A';
    FMOD_System_CreateStream(systeme, "questions/q1q2.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &Quest[1].son);
    Quest[1].reponse = 'C';
    FMOD_System_CreateStream(systeme, "questions/q1q3.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &Quest[2].son);
    Quest[2].reponse = 'C';
    FMOD_System_CreateStream(systeme, "questions/q1q4.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &Quest[3].son);
    Quest[3].reponse = 'B';
    FMOD_System_CreateStream(systeme, "questions/q1q5.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &Quest[4].son);
    Quest[4].reponse = 'C';
    FMOD_System_CreateStream(systeme, "questions/q2q1.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &Quest[5].son);
    Quest[5].reponse = 'B';
    FMOD_System_CreateStream(systeme, "questions/q2q2.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &Quest[6].son);
    Quest[6].reponse = 'A';
    FMOD_System_CreateStream(systeme, "questions/q2q3.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &Quest[7].son);
    Quest[7].reponse = 'C';
    FMOD_System_CreateStream(systeme, "questions/q2q4.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &Quest[8].son);
    Quest[8].reponse = 'B';
    FMOD_System_CreateStream(systeme, "questions/q2q5.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &Quest[9].son);
    Quest[9].reponse = 'A';
    return 1;
}

//Variables capteurs
int SND = 2;
int PIN1 = 3;
int PIN2 = 4;
int PIN3 = 4;

int lancerSons(FMOD_SOUND *sound)
{
    FMOD_System_PlaySound(systeme, sound, NULL, 0, &canal1);
}

/* Initialise FMOD avec les fichiers audio titres et réponses */
int initFMOD()
{
    FMOD_System_Create(&systeme);
    FMOD_System_Init(systeme, 2, FMOD_INIT_NORMAL,NULL);
    FMOD_System_SetOutput(systeme, FMOD_OUTPUTTYPE_AUTODETECT);
    FMOD_System_CreateStream(systeme, "titres/pres.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &pres);
    FMOD_System_CreateStream(systeme, "titres/pchoix.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &choix);
    FMOD_System_CreateStream(systeme, "titres/pdescription.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &description);
    FMOD_System_CreateStream(systeme, "titres/pdescGauche.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &dgauche);
    FMOD_System_CreateStream(systeme, "titres/pdescDroite.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &ddroite);
    FMOD_System_CreateStream(systeme, "titres/pquizz.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &quizz);
    FMOD_System_CreateStream(systeme, "titres/pquizzGauche.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &quizzg);
    FMOD_System_CreateStream(systeme, "titres/pquizzDroit.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &quizzd);
    FMOD_System_CreateStream(systeme, "titres/parret.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &arret);
    FMOD_System_CreateStream(systeme, "titres/musique.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &musique);
    FMOD_System_CreateStream(systeme, "alerte/tropBruit.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &bruit);
    FMOD_System_CreateStream(systeme, "alerte/tropBruit.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &bruit);
    FMOD_System_CreateStream(systeme, "reponse/rep0.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &rep0);
    FMOD_System_CreateStream(systeme, "reponse/rep1.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &rep1);
    FMOD_System_CreateStream(systeme, "reponse/rep2.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &rep2);
    FMOD_System_CreateStream(systeme, "reponse/rep3.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &rep3);
    FMOD_System_CreateStream(systeme, "reponse/rep4.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &rep4);
    FMOD_System_CreateStream(systeme, "reponse/rep5.mp3", FMOD_2D | FMOD_CREATESTREAM, NULL, &rep5);
    FMOD_System_Update(systeme);
}

/* Libère la mémoire pris par la librairie FMOD */
int freeFMOD()
{
    FMOD_Sound_Release(pres);
    FMOD_Sound_Release(choix);
    FMOD_Sound_Release(description);
    FMOD_Sound_Release(dgauche);
    FMOD_Sound_Release(ddroite);
    FMOD_Sound_Release(quizz);
    FMOD_Sound_Release(quizzg);
    FMOD_Sound_Release(quizzd);
    FMOD_Sound_Release(arret);
    FMOD_Sound_Release(musique);
    FMOD_Sound_Release(rep0);
    FMOD_Sound_Release(rep1);
    FMOD_Sound_Release(rep2);
    FMOD_Sound_Release(rep3);
    FMOD_Sound_Release(rep4);
    FMOD_Sound_Release(rep5);
    int i;
    for(i = 0; i < 10; i++)
    {
        FMOD_Sound_Release(Quest[i].son);
    }
    FMOD_System_Close(systeme);
    FMOD_System_Release(systeme);
}

/* Regarde si un capteur capte une personne */
int bonneDistance(enum capteurs capteur)
{
    int indice = -1;
    switch(capteur)
    {
        case GAUCHE:
            indice = PIN1;
            break;
        case CENTRE:
            indice = PIN2;
           break;
        case DROITE:
            indice = PIN3;
            break;
    }
    int distance;
    write_block(us_cmd, indice, 0, 0);
    pi_sleep(200);
    read_byte();
    read_block();
    distance =r_buf[1]* 256 + r_buf[2];
    if(indice == PIN1)
        printf("Distance1 : %d cm\n", distance);
    else
        printf("Distance2 : %d cm\n", distance);
    if(distance > DistMin && distance < DistMax)
        return 1;
    return 0;
}

/* Vérifie si la personne reste dans le rond plus de 1 secondes */
int estDansRond(enum capteurs capteur)
{
    int ok = 0;
    time_t debut = time(NULL);
    while(bonneDistance(capteur) == 1 && ok == 0)
    {
        printf("Capteur: %d\n", capteur);
        printf("Temps: %f\n", difftime(time(NULL), debut));
        if(difftime(time(NULL), debut) >= (float)1)
        {
            ok = 1;
        }
    }
    return ok;
}

/* Revient à l'étape initiale du programme si le capteur du milieux renvoi une valeur de moins de 5 cm pendant plus de 2 secondes */
int reinitialiser()
{
    int ok = 0;
    int proche = 0;
    time_t debut = time(NULL);
    do
    {
        int distance;
        write_block(us_cmd, PIN2, 0, 0);
        pi_sleep(100);
        read_byte();
        read_block();
        distance =r_buf[1]* 256 + r_buf[2];
        if(distance < 5)
        {
            proche = 1;
            if(difftime(time(NULL), debut) > 2)
            {
            	playingCurrent = 0;
                ok = 1;
            }
        }
        else
            proche = 0;
    }
    while(proche == 1 && ok == 0);
    return ok;
}

/* Arrete le programme si les trois capteurs renvoient une distance inférieur à 15 tous additionnés */
int arreter()
{
    int ok = 0;
    int proche = 0;
    time_t debut = time(NULL);
    do
    {
        int d1, d2, d3;
        write_block(us_cmd, PIN1, 0, 0);
        pi_sleep(100);
        read_byte();
        read_block();
        d1 =r_buf[1]* 256 + r_buf[2];
        write_block(us_cmd, PIN2, 0, 0);
        pi_sleep(100);
        read_byte();
        read_block();
        d2 =r_buf[1]* 256 + r_buf[2];
        write_block(us_cmd, PIN3, 0, 0);
        pi_sleep(100);
        read_byte();
        read_block();
        d3 =r_buf[1]* 256 + r_buf[2];
        if((d1+d2+d3) < 15)
        {
            proche = 1;
            if(difftime(time(NULL), debut) > 2)
                ok = 1;
        }
        else
            proche = 0;
    }
    while(proche == 1 && ok == 0);
    return ok;
}

/* Renvoi une lettre en fonction du rond dans laquelle une personne est */
char reponse()
{
    if(estDansRond(GAUCHE))
        return 'A';
    else if(estDansRond(CENTRE))
        return 'B';
    else if(estDansRond(DROITE))
        return 'C';
    return 'D';
}

/* Change le volume ou dis au personne de faire moins de bruit si il y a trop de bruit dans la salle*/
void changerSon()
{
	int valeur = analogRead(SND);
	printf("Valeur son: %d\n", valeur);
	if(valeur > valeurMaxSon)
	{
		FMOD_Channel_SetPaused(canal1, 1);
    	FMOD_System_PlaySound(systeme, bruit, NULL, 0, &canal2);
		FMOD_BOOL play = 1;
		while(play == 1)
		{
			FMOD_Channel_IsPlaying(canal2, &play);
		}
		FMOD_Channel_SetPaused(canal1, 0);
	}
	else
	{
		float volume = (float)valeur / (float)valeurMaxSon;
		if(volume < 0.5f)
			volume = 0.5f; 
		else if(volume > 1.0f)
			volume = 1.0f;
		FMOD_Channel_SetVolume(canal1, volume);
	}
    updateSon = time(NULL);
}

/* Foncton principale contenant la boucle principale avec les différentes étapes */
int main()
{
    int continuer = 1;
    etape = 0;
    currentQuestion = 0;
    if(init()==-1)
		exit(1);
    initFMOD();
    initQuestions();
    pinMode(SND,0);
    updateSon = time(NULL);
    while(continuer == 1)
    {
    	if((difftime(time(NULL), updateSon) > 5) && (etape != 0))
    	{
    		changerSon();
    	}
        if(arreter() == 1)
        {
            continuer = 0;
        }
        if(reinitialiser() == 1 || etape == -1)
        {
        	if(playingCurrent == 0)
        	{
                lancerSons(arret);
                playingCurrent = 1;
        	}
            etape = -1;
            FMOD_BOOL playing;
            FMOD_Channel_IsPlaying(canal1, &playing);
            if(playing == 0)
            {
                etape = 0;
                playingCurrent = 0;
            }
        }
        if(etape == 0)
        {
        	if(playingCurrent == 0) /*Permet de ne pas relancer un même fichier audio */
        	{
        		lancerSons(musique);
        		playingCurrent = 1;
        	}
            if(estDansRond(CENTRE))
            {
            	FMOD_Channel_Stop(canal1);
        		playingCurrent = 0;
                etape = 1;
            }
        }
        else if(etape == 1)
        {
            if(playingCurrent == 0)
            {
                printf("Etape: %d\n", etape);
                lancerSons(pres);
                playingCurrent = 1;
                pi_sleep(500);
            }
            FMOD_BOOL playing;
            FMOD_Channel_IsPlaying(canal1, &playing);
            if(playing == 0)
            {
                    etape = 2;
                    playingCurrent = 0;
            }
        }
        else if(etape == 2)
        {
            if(playingCurrent == 0)
            {
                printf("Etape: %d\n", etape);
                lancerSons(choix);
                playingCurrent = 1;
                pi_sleep(500);
            }
            FMOD_BOOL playing;
            FMOD_Channel_IsPlaying(canal1, &playing);
            if(playing == 0)
            {
                if(estDansRond(DROITE))
                {
                    etape = 7;
                    playingCurrent = 0;
                }
                else if(estDansRond(GAUCHE))
                {
                    etape = 3;
                    playingCurrent = 0;
                }
            }
        }
        else if(etape == 3)
        {
            if(playingCurrent == 0)
            {
                printf("Etape: %d\n", etape);
                lancerSons(description);
                pi_sleep(500);
                playingCurrent = 1;
            }
            FMOD_BOOL playing;
            FMOD_Channel_IsPlaying(canal1, &playing);
            if(playing == 0)
            {
                if(estDansRond(CENTRE))
                {
                    etape = 4;
                    playingCurrent = 0;
                }
                else if(estDansRond(DROITE))
                {
                    etape = 5;
                    playingCurrent = 0;
                }
            }
        }
        else if(etape == 4)
        {
            if(playingCurrent == 0)
            {
                printf("Etape: %d\n", etape);
                lancerSons(dgauche);
                pi_sleep(500);
                playingCurrent = 1;
            }
            FMOD_BOOL playing;
            FMOD_Channel_IsPlaying(canal1, &playing);
            if(playing == 0)
            {
                total = 0;
                etape = 9;
                playingCurrent = 0;
            }
        }
        else if(etape == 5)
        {
            if(playingCurrent == 0)
            {
                printf("Etape: %d\n", etape);
                lancerSons(ddroite);
                pi_sleep(500);
                playingCurrent = 1;
            }
            FMOD_BOOL playing;
            FMOD_Channel_IsPlaying(canal1, &playing);
            if(playing == 0)
            {
                total = 0;
                etape = 8;
                playingCurrent = 0;
            }
        }
        else if(etape == 7)
        {
            if(playingCurrent == 0)
            {
                printf("Etape: %d\n", etape);
                lancerSons(quizz);
                playingCurrent = 1;
                pi_sleep(500);
            }
            FMOD_BOOL playing;
            FMOD_Channel_IsPlaying(canal1, &playing);
            if(playing == 0)
            {
                if(estDansRond(GAUCHE))
                {
                    total = 0;
                    etape = 8;
                    playingCurrent = 0;
                }
                else if(estDansRond(CENTRE))
                {
                    total = 0;
                    etape = 9;
                    playingCurrent = 0;
                }
            }
        }
        else if(etape == 8 || etape == 9)
        {
            int q;
            if(etape == 9)
                q = 5;
            else
                q = 0;
            FMOD_BOOL playing;
            if(playingCurrent == 0)
            {
                printf("Etape: %d\n", etape);
                if(etape == 8)
                    lancerSons(quizzg);
                else
                    lancerSons(quizzd);
                playingCurrent = 1;
                pi_sleep(500);
            }
            FMOD_Channel_IsPlaying(canal1, &playing);
            if(playing == 0 && currentQuestion > -1)
            {
                questionTime = 1;
                if(playingCurQuestion == 0)
                {
                    lancerSons(Quest[q + currentQuestion].son);
                    playingCurQuestion = 1;
                    pi_sleep(500);
                }
                else if(reponseTime == 1)
                {
                    char rep = reponse();
                    if(rep != 'D')
                    {
                        if(rep == Quest[q + currentQuestion].reponse)
                            total += 1;
                        if(currentQuestion == 4)
                        {
                            currentQuestion = -1;
                        }
                        else
                        {
                            currentQuestion += 1;
                            playingCurQuestion = 0;
                        }
                        playingCurQuestion = 0;
                        reponseTime = 0;
                    }
                }
            }
            else if(currentQuestion == -1)
            {
                playingCurrent = 0;
                currentQuestion = 0;
                etape = 10;
            }
            else if(questionTime == 1)
            {
                reponseTime = 1;
            }
        }
        else if(etape == 10)
        {
            if(playingCurrent == 0)
            {
                switch(total)
                {
                    case 0:
                        lancerSons(rep0);
                        break;
                    case 1:
                        lancerSons(rep1);
                        break;
                    case 2:
                        lancerSons(rep2);
                        break;
                    case 3:
                        lancerSons(rep3);
                        break;
                    case 4:
                        lancerSons(rep4);
                        break;
                    case 5:
                        lancerSons(rep5);
                        break;
                }
                pi_sleep(500);
                playingCurrent = 1;
            }
            FMOD_BOOL playing;
            FMOD_Channel_IsPlaying(canal1, &playing);
            if(playing == 0)
            {
                pi_sleep(2000);
                etape = 2; /* Retour au choix de l'activité */
                playingCurrent = 0;
            }
        }
    }
	freeFMOD();
	return 0;
}
