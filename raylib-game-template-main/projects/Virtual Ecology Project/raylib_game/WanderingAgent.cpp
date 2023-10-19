#include "Agent.cpp"




class WanderingAgent : public Agent {

private:

	steady_clock::time_point timeOfLastEat = high_resolution_clock::now();


public:

	WanderingAgent(Vector2 location, float size, float maxSpeed, float maxForce, float foodRange, float detectRange, float rechargeTime) : 
		Agent(location, size, maxSpeed, maxForce, foodRange, detectRange, rechargeTime) {

	}

	void draw() override {
		//std::cout << detectRange << "\n";
		//std::cout << location.x << "\t" << location.y << "\n";


		DrawCircle(location.x, location.y, 5, GREEN);
		DrawCircleGradient(location.x, location.y, foodRange, Color{ 255, 255, 255, 0 }, Agent::gradientCalculator(EAT_COLOR_START, EAT_COLOR_END, (WANDERING_STARTING_POP + CHASER_STARTING_POP) * foodEaten / (2*FOOD_PER_ROUND)));
	}

	void update(std::vector<Food>* foods) override {
		//std::cout << "W:" << location.x << "\t" << location.y << "\n";


		if (Vector2Distance(location, targetPos) < foodRange || Vector2Length(velocity) < .01) // if slow or close to target
		{
			targetPos = { (float)(rand() % XDIM), (float)(rand() % YDIM) };
		}

		seekTarget();

		if (rechargeTime < duration_cast<seconds>(high_resolution_clock::now() - timeOfLastEat).count())
		{
			timeOfLastEat = high_resolution_clock::now();
			consumeFoodInRange(foods);
		}
		location = Vector2Add(location, velocity);
		velocity = Vector2Add(velocity, acceleration);

	}


	
};