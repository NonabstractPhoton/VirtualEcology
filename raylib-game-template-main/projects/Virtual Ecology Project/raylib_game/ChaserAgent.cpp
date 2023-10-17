#include "Header.h"
#include "Agent.cpp"
#include "Food.cpp"





class ChaserAgent : public Agent {
public:

    ChaserAgent(Vector2 location) : Agent(location, SIZE, MAX_SPEED, MAX_FORCE, FOOD_RANGE, DETECT_RANGE, RECHARGE_TIME) {}


    void update(std::vector<Food>* foods) {
        for (int i = 0; i < (*foods).size(); i++) {
            if (Vector2Distance((*foods)[i].location, location) < detectRange) {
                targetPos = (*foods)[i].location;
            }
            if (Vector2Distance((*foods)[i].location, location) < foodRange) {
                (*foods).erase((*foods).begin() + i);
            }
        }
    }



private:

    const float SIZE = 1, MAX_SPEED = .5, MAX_FORCE = .1, FOOD_RANGE = 0, DETECT_RANGE = 100, RECHARGE_TIME = 0;

    void addForce(Vector2 f) {
        acceleration = f;
    }
};