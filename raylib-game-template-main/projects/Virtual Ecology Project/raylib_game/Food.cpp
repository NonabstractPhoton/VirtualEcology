#include "raylib.h"
#include "raymath.h"
#include <vector>
#pragma once


class Food {
public:
	Vector2 location;

	Food(Vector2 location) {
		this->location = location;
	}
};