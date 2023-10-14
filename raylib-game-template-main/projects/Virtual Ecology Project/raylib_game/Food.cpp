#include "raylib.h"
#include "raymath.h"
#include <vector>

class Food {
	public:
		Vector2 location;
		
		const float radius = 1;
		Food(Vector2 location) {
			this->location = location;
		}
};