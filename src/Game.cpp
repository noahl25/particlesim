#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.hpp"
#include "Debug.hpp"
#include "Particle.hpp"
#include "Common.hpp"
#include "Manager.hpp"
#include "UI.hpp"
#include "UIElement.hpp"

Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int x, int y, int width, int height, bool fullScreen) {

	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;

	paused = false;

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
	ui = new UI();


	SDL_Rect rect{10, 10, 32, 32};
	SDL_Rect rect1{10, 42, 32, 32};
	ui->addUIElement<UIElementCursorSize>("cursor up", &rect, TextureManager::loadTexture("res/cursor_up.png", renderer), SDL_FLIP_NONE);
	ui->addUIElement<UIElementCursorSize>("cursor up", &rect1, TextureManager::loadTexture("res/cursor_up.png", renderer), SDL_FLIP_VERTICAL);





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
				SDL_ShowCursor(SDL_DISABLE);

				if (ui->getElements()[0]->hovering) {
					manager->addToCursorSize(1);
				}
				if (ui->getElements()[1]->hovering) {
					manager->addToCursorSize(-1);
				}
			
			}
			if (event.button.button == SDL_BUTTON_RIGHT) {
		
				paused = true;
				SDL_ShowCursor(SDL_ENABLE);
			
			}
			break;

		case SDL_MOUSEBUTTONUP:

			if (event.button.button == SDL_BUTTON_LEFT) {
		
				manager->spawningParticles = false;


			}
			if (event.button.button == SDL_BUTTON_RIGHT) {
				
				SDL_ShowCursor(SDL_DISABLE);
				paused = false;
			
			}
			break;



		default:
			break;


	}



	
}

void Game::update() {

	if (!paused) {

		for (UIElement* element : ui->getElements()) {

			if (element->hovering) {
				manager->spawningParticles = false;
			}
		}
		int x, y;
		SDL_GetMouseState(&x, &y);
		manager->update(x, y);
		ui->update(x, y);


	}

}

void Game::render() {

	if (!paused) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		manager->draw(renderer);
		ui->draw(renderer);


		SDL_RenderPresent(renderer);
	}
}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	_ASSERT("GAME DESTROYED");

}
