#include "Manager.hpp"
#include "Particle.hpp"

Manager::Manager() {

	for (int y(0u); y < pHeight; y++) {

		std::vector<Particle*> temp;

		for (int x(0u); x < pWidth; x++) {

			temp.push_back(nullptr);

		}

		particles.push_back(std::move(temp));

	}

	spawningParticles = false;

	

}

void Manager::update() {

	for (std::vector<Particle*>& row : particles) {
		for (Particle*& p : row) {
			p->update(particles);
		}
	}

	handleParticles();

	int x, y;
	SDL_GetMouseState(&x, &y);

	if (spawningParticles && inScreenBounds((int)x/5, (int)y/5)) {
		
		if (particles[(int)(y / 5)][(int)(x / 5)] == nullptr) {
				particles[(int)(y / 5)][(int)(x / 5)] = new Particle(ParticleType::Sand);
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


}

void Manager::handleParticles() {

	std::vector< std::vector<Particle*>> tempParticles = particles;

	for (uint32_t y(0u); y < particles.size(); y++) {
		for (uint32_t x(0u); x < particles[0].size(); x++) {
				

			if (tempParticles[y][x] != nullptr) {

				switch (tempParticles[y][x]->type) {

				case ParticleType::Sand:


					if (inScreenBounds(x, y + 1) && tempParticles[y+1][x] == nullptr) {

						particles[y][x] = nullptr;
						particles[y+1][x] = new Particle(ParticleType::Sand);
					}

					else if (inScreenBounds(x - 1, y + 1) && inScreenBounds(x + 1, y + 1) && tempParticles[y+1][x - 1] == nullptr && tempParticles[y+1][x + 1] == nullptr) {

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

					else if (inScreenBounds(x + 1, y + 1) && tempParticles[y+1][x + 1] == nullptr) {

						particles[y][x] = nullptr;
						particles[y+1][x + 1] = new Particle(ParticleType::Sand);

					}

					else if (inScreenBounds(x - 1, y + 1) && tempParticles[y+1][x - 1] == nullptr) {

						particles[y][x] = nullptr;
						particles[y+1][x - 1] = new Particle(ParticleType::Sand);

					}



					break;
				default:
					break;

				}


			}


		}
	}




}

inline bool Manager::inScreenBounds(int x, int y) {

	return y >= 0 && x >= 0 && x < pWidth && y < pHeight;


}

Manager::~Manager() {

 
}