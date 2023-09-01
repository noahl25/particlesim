#pragma once

#include "Common.hpp"

#include <vector>

class Particle;
class ParticleType;


class Manager {


public:

	Manager();
	~Manager();

	void update(int x, int y);
	void draw(SDL_Renderer*& renderer);

	bool spawningParticles;

	inline void addToCursorSize(uint8_t size) {this->cursorSize += ((cursorSize <= 20 && cursorSize >= 1 ) ? size : 0);}

	ParticleType* particleType;

	inline void setParticleType(ParticleType type) { *particleType = type;}

private:

	std::vector< std::vector<Particle*> > particles;

	int pWidth = SCREEN_WIDTH / P_SIZE;
	int pHeight = SCREEN_HEIGHT / P_SIZE;

	void handleParticles();
	inline bool inScreenBounds(int x, int y);
	uint8_t cursorSize;

	void handleSand(int x, int y);




};