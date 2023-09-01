#include "Manager.hpp"
#include "Particle.hpp"
#include "Util.hpp"
#include "UIElement.hpp"


Manager::Manager() {

	for (int y(0u); y < pHeight; y++) {

		std::vector<Particle*> temp;

		for (int x(0u); x < pWidth; x++) {

			temp.push_back(nullptr);

		}

		particles.push_back(std::move(temp));

	}

	spawningParticles = false;
	cursorSize = 10;

	

}

void Manager::update(int x, int y) {

	for (std::vector<Particle*>& row : particles) {
		for (Particle*& p : row) {
			p->update(particles);
		}
	}

	handleParticles();

	if (spawningParticles && x >= 0 && y >= 0 && x <= SCREEN_WIDTH && y <= SCREEN_HEIGHT) {

		for (Vec2D*& coord : Util::getPointsWithinCircle(x, y, cursorSize)) {
			
			if (inScreenBounds((int)coord->x/5, (int)coord->y/5)) {

				if (particles[(int)(coord->y / 5)][(int)(coord->x / 5)] == nullptr) {
					particles[(int)(coord->y / 5)][(int)(coord->x / 5)] = new Particle(*particleType);
				}
			}
		}
	}

}

void Manager::draw(SDL_Renderer*& renderer) {

	for (uint32_t y(0u); y < particles.size(); y++) {
		for (uint32_t x(0u); x < particles[0].size(); x++) {
			if (particles[y][x] != nullptr) {
				particles[y][x]->draw(renderer, x * P_SIZE, y * P_SIZE);
			}
		}
	}

	int x, y;
	SDL_GetMouseState(&x, &y);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	Util::drawCircle(renderer, x, y, cursorSize);

}

void Manager::handleParticles() {

	//std::vector< std::vector<Particle*>> particles = particles;
	//double buffer?? 

	for (int y = particles.size() - 1; y >= 0; y--) {
		for (uint32_t x(0u); x < particles[0].size(); x++) {
				

			if (particles[y][x] != nullptr) {

				switch (particles[y][x]->type) {

				case ParticleType::Sand:

					handleSand(x, y); 
					break;

				}

			}
		}
	}


}
void Manager::handleSand(int x, int y) {
	
	if (inScreenBounds(x, y + 1) && particles[y+1][x] == nullptr) {

		particles[y][x] = nullptr;
		particles[y+1][x] = new Particle(ParticleType::Sand);
	}

	else if (inScreenBounds(x - 1, y + 1) && inScreenBounds(x + 1, y + 1) && particles[y+1][x - 1] == nullptr && particles[y+1][x + 1] == nullptr) {

		bool dir = rand() %2;

		if (dir) {
			particles[y][x] = nullptr;
			particles[y+1][x - 1] = new Particle(ParticleType::Sand);
		}
		else {
			particles[y][x] = nullptr;
			particles[y+1][x + 1] = new Particle(ParticleType::Sand);
		}



	}

	else if (inScreenBounds(x + 1, y + 1) && particles[y+1][x + 1] == nullptr) {

		particles[y][x] = nullptr;
		particles[y+1][x + 1] = new Particle(ParticleType::Sand);

	}

	else if (inScreenBounds(x - 1, y + 1) && particles[y+1][x - 1] == nullptr) {

		particles[y][x] = nullptr;
		particles[y+1][x - 1] = new Particle(ParticleType::Sand);

	}

		
}
inline bool Manager::inScreenBounds(int x, int y) {

	return y >= 0 && x >= 0 && x < pWidth && y < pHeight;


}


Manager::~Manager() {

 
}