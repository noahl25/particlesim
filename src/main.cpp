#define DEBUG_USE_SIMPLIFIED_NAMES

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.hpp"
#include "Common.hpp"
#include "TextureManager.hpp"

#include <windows.h>


int main(int argc, char* args[]){

	Game *game = nullptr;
	game = new Game();
	game->init("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 840, 600, false);

	const int FPSTarget = 60;
	const int deltaTimeTarget = 1000/FPSTarget;

	Uint32 frameStart;
	int frameTime;

	int frames;
	int prevTime = SDL_GetTicks();
	const char* temp;

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		
		frames++;
 
		if (deltaTimeTarget > frameTime) {

			SDL_Delay(deltaTimeTarget - frameTime);

		}



	}

	game->clean();
	delete game;

	return 0;
}