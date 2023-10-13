#include "Header.h"


class Agent {

public:

    Agent(Vector2 location, float size, float maxSpeed, float maxForce, float foodRange, float detectRange, float rechargeTime) {
        this->location = location;
        this->size = size;
        this->maxSpeed= maxSpeed;
        this->maxForce = maxForce;
        this->foodRange = foodRange;
        this->detectRange = detectRange;
        this->rechargeTime = rechargeTime;
    }

    Vector2 location;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 targetPos;
    float size, maxSpeed, maxForce, foodRange, detectRange, rechargeTime;
};