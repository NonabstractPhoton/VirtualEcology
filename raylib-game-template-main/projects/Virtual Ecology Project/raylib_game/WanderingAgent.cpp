#include "Agent.cpp"




class WanderingAgent : public Agent {

private:
	int rechargeTimer = 0;

	const float SIZE = 1, MAX_SPEED = 1, MAX_FORCE = .1, FOOD_RANGE = 10, DETECT_RANGE = 0, RECHARGE_TIME = 5;

public:
	const int xDim = 1600, yDim = 900;

	WanderingAgent(Vector2 location) : Agent(location, SIZE, MAX_SPEED, MAX_FORCE, FOOD_RANGE, DETECT_RANGE, RECHARGE_TIME) {}

	void update(std::vector<Food>* foods) override
	{
		if (Vector2Distance(location, targetPos) < FOOD_RANGE || Vector2Length(velocity) < .01) // if slow or close to target
		{
			targetPos = {(float)(rand() % XDIM), (float)(rand() % YDIM)};
		}

		seekTarget();
		rechargeTimer -= GetFrameTime();

		if (rechargeTimer < .1)
		{
			rechargeTimer = RECHARGE_TIME;
			consumeFoodInRange(foods);
		}
	}

	void consumeFoodInRange(std::vector<Food>* foods)
	{
		for (int i = 0; i < (*foods).size(); i++)
		{
			if (Vector2Distance(location, (*foods)[i].location) < FOOD_RANGE)
			{
				foods->erase((*foods).begin() + i);
				foodEaten++;
				break;
			}
		}
	}
};