#pragma once

#include "Common.hpp"
#include "Particle.hpp"

#include <vector>

class Particle;


class Manager {


public:

	Manager();
	~Manager();

	void update(int x, int y);
	void draw(SDL_Renderer*& renderer);

	bool spawningParticles;

	inline void addToCursorSize(int8_t size) {


		if (size == 1 && cursorSize < 20) {
			cursorSize++;
		}
		if (size == -1 && cursorSize > 1) {
			cursorSize--;
		}




	}

	ParticleType particleType;

	inline void setParticleType(ParticleType type) { particleType = type;}

	void resetScreen() {

		for (auto& row : particles) {
			for (auto& val : row) {
				if (val != nullptr) {
                	delete val; // Deallocate memory for Particle object
                	val = nullptr;
            	}
			}
		}

		

	

	}

private:

	std::vector< std::vector<Particle*> > particles;

	int pWidth = SCREEN_WIDTH / P_SIZE;
	int pHeight = SCREEN_HEIGHT / P_SIZE;

	void handleParticles();
	inline bool inScreenBounds(int x, int y);
	uint8_t cursorSize;

	void handleSand(int x, int y);




};