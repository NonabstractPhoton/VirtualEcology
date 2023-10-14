#include "Header.h"
#include "Agent.cpp"

const float SIZE = 1, MAX_SPEED = 1, MAX_FORCE = .1, FOOD_RANGE = 2, DETECT_RANGE = 0, RECHARGE_TIME = 5;

class WanderingAgent : public Agent{

	private:
		const int distanceTolerance = 5;
		int rechargeTimer = 0;

	public:
		const int xDim=1600, yDim=900;

		WanderingAgent(Vector2 location) : Agent(location, SIZE, MAX_SPEED, MAX_FORCE, FOOD_RANGE, DETECT_RANGE, RECHARGE_TIME) {}
		
		void update(std::vector<Food>* food)
		{
			if (Vector2Length(velocity) < .01 || Vector2Length(Vector2Subtract(location, targetPos)) < distanceTolerance)
			{
				/*
					targetPos = {rand() % xdim, rand() % ydim};
				*/
			}

			seekTarget();

			if (rechargeTimer < .1)
			{
				// consumeFoodinRadius()
			}
		}
};