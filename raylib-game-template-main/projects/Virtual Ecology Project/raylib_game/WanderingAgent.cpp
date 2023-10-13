#include "Header.h"
#include "Agent.cpp"

class WanderingAgent : public Agent
{
	private:
		const int distanceTolerance = 5;
		int rechargeTimer = 0;

	public:
		const int xDim, yDim;
		
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