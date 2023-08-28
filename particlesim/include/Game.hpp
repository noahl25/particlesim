#pragma once


class ColliderComponent;
class Manager;

class Game {

public:

	Game();
	~Game();

	void init(const char* title, int x, int y, int width, int height, bool fullScreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	inline bool running() {return isRunning;}


private:
	
	SDL_Window* window;
	SDL_Renderer* renderer;

	Manager* manager;

	SDL_Event event;

	bool isRunning;

};