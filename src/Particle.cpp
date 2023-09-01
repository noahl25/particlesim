#include "Particle.hpp"

#include <SDL2/SDL.h>


Particle::Particle(ParticleType type) {
	this->type = type;

	if (type == ParticleType::Sand) {
		color = {194, 178, 128, 255};
	}
	if (type == ParticleType::Rock) {
		color = {211, 211, 211, 255};
	}
}

void Particle::draw(SDL_Renderer*& renderer, uint32_t x, uint32_t y) {

	SDL_Rect rect = {x, y, P_SIZE, P_SIZE};

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_RenderFillRect(renderer, &rect);


}
void Particle::update(std::vector<std::vector<Particle*>>& particles) {


}

Particle::~Particle() {

}