#pragma once

#include "Common.hpp"

struct Vec2D {

	int16_t x;
	int16_t y;

	void operator+=(Vec2D& vec) {
		this->x += vec.x;
		this->y += vec.y;
	}


};