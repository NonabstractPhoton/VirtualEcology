#include "Header.h"
#include "Agent.cpp"



class ChaserAgent : public Agent {
public:

    ChaserAgent(Vector2 location) : Agent(location, SIZE, MAX_SPEED, MAX_FORCE, FOOD_RANGE, DETECT_RANGE, RECHARGE_TIME) {}

    void lookForFood() {

    }



private:

    const float SIZE = 1, MAX_SPEED = .5, MAX_FORCE = .1, FOOD_RANGE = 10, DETECT_RANGE = 50, RECHARGE_TIME = 0;

    void addForce(Vector2 f) {
        acceleration = f;
    }
};