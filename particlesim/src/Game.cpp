#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.hpp"
#include "Debug.hpp"
#include "Particle.hpp"
#include "Common.hpp"
#include "Manager.hpp"

Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int x, int y, int width, int height, bool fullScreen) {

	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;

	int flags;
	if (fullScreen) {flags = SDL_WINDOW_FULLSCREEN;}
	else {flags = 0;}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		_ASSERT("SDL SUCCESSFULLY INITIALIZED");
		window = SDL_CreateWindow(title, x, y, width, height, flags);
		if (window) {
			_ASSERT("WINDOW INITIALIZED");
		}
 		
 		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			_ASSERT("RENDERER INITIALIZED");
		}

		isRunning = true;
	}

	else {
		isRunning = false;
		_ASSERT_FATAL("SDL FAILED TO INITIALIZE");
	}

	manager = new Manager();




}

void Game::handleEvents() {

	SDL_PollEvent(&event);

	switch (event.type) {

		case SDL_QUIT:
			isRunning = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			if (event.button.button == SDL_BUTTON_LEFT) {
		
				manager->spawningParticles = true;
			
			}
			break;

		case SDL_MOUSEBUTTONUP:

			if (event.button.button == SDL_BUTTON_LEFT) {
		
				manager->spawningParticles = false;


			}
			break;


		default:
			break;


	}



	
}

void Game::update() {

	manager->update();


}

void Game::render() {


	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	manager->draw(renderer);


	SDL_RenderPresent(renderer);

}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	_ASSERT("GAME DESTROYED");

}
