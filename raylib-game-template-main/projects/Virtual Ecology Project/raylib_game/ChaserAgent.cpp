#include "Header.h"
#include "Agent.cpp"

const float SIZE = 1, MAX_SPEED = 1, MAX_FORCE = .1, FOOD_RANGE = 1, DETECT_RANGE = 2, RECHARGE_TIME = 0;

class ChaserAgent : public Agent {
public:
    
    ChaserAgent(Vector2 location) : Agent(location, SIZE, MAX_SPEED, MAX_FORCE, FOOD_RANGE, DETECT_RANGE, RECHARGE_TIME) {}

    //it seeks
    void update() {
        lookForFood();
        if (&targetPos == NULL)
            velocity = Vector2Add(velocity, acceleration);
        velocity = Vector2ClampValue(velocity, -maxSpeed, maxSpeed);
        location = Vector2Add(location, velocity);

        Vector2 desiredVelocity = Vector2Normalize(Vector2Subtract(targetPos, location));
        addForce(Vector2ClampValue(
            Vector2Subtract(
                { desiredVelocity.x * maxSpeed, desiredVelocity.y * maxSpeed }
                , velocity)
            , -maxForce, maxForce));
    }

    void lookForFood() {

    }
private:
    void addForce(Vector2 f) {
        acceleration = f;
    }
};