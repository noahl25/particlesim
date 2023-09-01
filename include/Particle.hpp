#pragma once

#include "Vec2D.hpp"
#include "Common.hpp"
#include <vector>

enum class ParticleType {

	Sand,
	Rock,
	Water

};


struct Color {

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

};

class Color;


struct Particle {

	Particle(ParticleType type);
	~Particle();

	int32_t spawnTime;
	ParticleType type;
	Vec2D velocity;
	Color color;

	void update(std::vector<std::vector<Particle*>>& particles);
	void draw(SDL_Renderer*& renderer, uint32_t x, uint32_t y);

};

