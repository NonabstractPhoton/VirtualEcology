#include "raylib.h"
#include "raymath.h"
#include <vector>
#include "Header.h"
#include "Agent.cpp"


class ChaserAgent : public Agent {
public:


    //it seeks
    void updatePlayerNums() {
        lookForFood();
        if (&targetPos == NULL)
            velocity = Vector2Add(velocity, acceleration);
        velocity = Vector2ClampValue(velocity, -maxspeed, maxspeed);
        location = Vector2Add(location, velocity);

        Vector2 desiredVelocity = Vector2Normalize(Vector2Subtract(targetPos, location));
        addForce(Vector2ClampValue(
            Vector2Subtract(
                { desiredVelocity.x * maxspeed, desiredVelocity.y * maxspeed }
                , velocity)
            , -maxforce, maxforce));
    }

    void lookForFood() {

    }
private:
    void addForce(Vector2 f) {
        acceleration = f;
    }
};