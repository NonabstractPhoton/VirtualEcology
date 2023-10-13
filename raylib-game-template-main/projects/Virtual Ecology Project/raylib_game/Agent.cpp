#include "raylib.h"
#include "raymath.h"
#include <vector>
#include "Header.h"


class Agent {

public:
    Vector2 location;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 targetPos;
    float size, maxspeed, maxforce, foodRange, detectRange, rechargeTime;
};