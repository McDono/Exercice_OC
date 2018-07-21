#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

int main(int argc, char *argv[])
{
	SDL_Surface *ecran = NULL, *texte = NULL;
	SDL_Rect position;
	SDL_Event event;
	SDL_Color Noir = { 0,0,0 };
	TTF_Font *police_angelina = NULL;

	int continuer = 1, pause = 0, space_enfonce = 0;

	int tempsActuel = 0, tempsPrecedent = 0, compteur = 0;
	char temps[20] = "";

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	//Init de l'écran
	ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("Deuxieme essaie au compteur", NULL);
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

	//Chargement de la police
	police_angelina = TTF_OpenFont("angelina.ttf", 65);

	//Init du texte et du temps
	tempsActuel = SDL_GetTicks();
	sprintf(temps, "Temps: %d ms", compteur);
	texte = TTF_RenderText_Solid(police_angelina, temps, Noir);

	while (continuer)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				space_enfonce = 0; //Space n'est plus appuyé
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				continuer = 0;
				break;
			case SDLK_SPACE:
				if (!space_enfonce) //Si space n'est pas déjà appuyé
				{
					space_enfonce = 1; //On signal que maintenant space est appuyé

					if (pause) //Si le jeu est en pause, on met fin à la pause
					{
						pause = 0;
					}
					else //Sinon, on met le jeu en pause
					{
						pause = 1;
					}
				}
				break;
			}
		}

		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); //On efface l'ecran

		if (!pause) //Si le jeu n'est pas en pause
		{
			tempsActuel = SDL_GetTicks(); //On recup le temps

			if (tempsActuel - tempsPrecedent >= 100) //Si au mmoins 100ms se sont écoulé depuis la derniere modif de temps
			{
				compteur += 100; //On rajoute 100ms au compteur
				sprintf(temps, "Temps: %d ms", compteur); //On ajoute le compteur dans la string
				SDL_FreeSurface(texte); //On efface le texte precedent
				texte = TTF_RenderText_Solid(police_angelina, temps, Noir); //On ecrit le nouveau texte
				tempsPrecedent = tempsActuel; //On stock le temps de la modif de texte
			}
		}

		position.x = 200;
		position.y = 200;
		SDL_BlitSurface(texte, NULL, ecran, &position); //On colle le texte sur l'ecran
		SDL_Flip(ecran); //On reactualise l'ecran
		
	}

	TTF_CloseFont(police_angelina);
	TTF_Quit();

	SDL_FreeSurface(texte);
	SDL_Quit();

	return EXIT_SUCCESS;
}
