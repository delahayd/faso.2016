#include "grovepi.c"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fmod.h>

#define us_cmd 7

//Variables globales
FMOD_SYSTEM *systeme;
FMOD_SOUND *sound, *sound2;
FMOD_CHANNEL *canal1, *canal2;
int data;
int value;
int once;
time_t timeO;

//Variables capteurs
int SND = 1;
int PIN = 3;

int initFMOD()
{
    FMOD_System_Create(&systeme);
    FMOD_System_Init(systeme, 20, FMOD_INIT_NORMAL, NULL);
    FMOD_System_CreateStream(systeme, "musique.ogg", FMOD_2D | FMOD_CREATESTREAM, NULL, &sound);
    FMOD_System_CreateStream(systeme, "musique2.ogg", FMOD_2D | FMOD_CREATESTREAM, NULL, &sound2);
    FMOD_System_Update(systeme);
    FMOD_Sound_SetLoopCount(sound, -1);
    FMOD_Sound_SetLoopCount(sound2, -1);
    FMOD_System_PlaySound(systeme, sound, NULL, 0, &canal1);
    FMOD_System_PlaySound(systeme, sound2, NULL, 0, &canal2);
    FMOD_Channel_SetPaused(canal1, 1);
    FMOD_Channel_SetPaused(canal2, 1);
}

int freeFMOD()
{
    FMOD_Sound_Release(sound);
    FMOD_Sound_Release(sound2);
    FMOD_System_Close(systeme);
    FMOD_System_Release(systeme);
}

int information()
{
    write_block(us_cmd, PIN, 0, 0);
    pi_sleep(200);
    read_byte();
    read_block();
    data=r_buf[1]* 256 + r_buf[2];
    printf("Distance : %d cm\n", data);
    value = analogRead(SND);
    printf("Décibel : %d\n", value);
}

int update()
{
    if(data > 10 && data < 30)
    {
        FMOD_Channel_SetPaused(canal1, 0);
        FMOD_Channel_SetPaused(canal2, 1);
    }
    else if(data > 30 && data < 50)
    {
        FMOD_Channel_SetPaused(canal2, 0);
        FMOD_Channel_SetPaused(canal1, 1);
    }
    if((int)difftime(time(NULL), timeO) % 2 == 0)
    {
        if(once == 0)
        {
            once =1;
            printf("Entré\n");
            if(value > 200)
            {
                FMOD_Channel_SetVolume(canal1, 1.0);
                FMOD_Channel_SetVolume(canal2, 1.0);
            }
            else
            {
                FMOD_Channel_SetVolume(canal1, value * 1.0 / 200);
                FMOD_Channel_SetVolume(canal2, value * 1.0 / 200);
            }
        }
    }
    else if(once == 1)
    {
        once = 0;
    }
}

int main()
{
    if(init()==-1)
		exit(1);
    data = 8;
    timeO = time(NULL);
    initFMOD();
    pinMode(SND,0);
	while(data > 7) // boucle infinie
	{
	    information();
	    update();
        pi_sleep(100); // attend 500ms
	}
	freeFMOD();
}
