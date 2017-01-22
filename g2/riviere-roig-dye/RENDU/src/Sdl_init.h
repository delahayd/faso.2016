#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_rotozoom.h>
#include <stdio.h>

#define SCREEN_WIDTH 800;
#define SCREEN_HEIGHT 480;

/**
	@brief Recupère le renderer actuellement utilisé
	@return Pointeur vers le SDL_Renderer utilisé
*/
SDL_Renderer *getrenderer();
/**
	@brief Recupère la fenetre actuellement utilisé
	@return Pointeur vers le SDL_Window utilisé
*/
SDL_Window *getwindow();
/**
	@brief Recupère la police actuellement utilisé
	@return Pointeur vers le TTF_Font utilisé
*/
TTF_Font *getpolice();

/**
	@brief Initilialise une fenetre pour le programme
*/
void init();

/**
	@brief Detruit la fenetre, le rendu et ferme SDL
*/
void cleanup();
