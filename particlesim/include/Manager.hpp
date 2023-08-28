#pragma once

#include "Common.hpp"

#include <vector>

class Particle;


class Manager {


public:

	Manager();
	~Manager();

	void update();
	void draw(SDL_Renderer*& renderer);

	bool spawningParticles;

private:

	std::vector< std::vector<Particle*> > particles;

	int pWidth = SCREEN_WIDTH / P_SIZE;
	int pHeight = SCREEN_HEIGHT / P_SIZE;

	void handleParticles();
	inline bool inScreenBounds(int x, int y);




};