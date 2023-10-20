#include "Agent.cpp"





class MutantAgent : public Agent {
public:

	MutantAgent(Vector2 location, float size, float maxSpeed, float maxForce, float foodRange, float detectRange, float rechargeTime) :
		Agent(location, size, maxSpeed, maxForce, foodRange, detectRange, rechargeTime) {
	}

	void draw() override {

		DrawCircle(location.x, location.y, 5, BLUE);

		DrawCircleGradient(location.x, location.y, foodRange, Color{ 255, 255, 255, 0 }, 
			Agent::gradientCalculator(EAT_COLOR_START, EAT_COLOR_END, 
				(WANDERING_STARTING_POP + CHASER_STARTING_POP) * foodEaten / (2 * FOOD_PER_ROUND)));


		DrawCircleGradient(location.x, location.y, detectRange, Color{ 255, 255, 255, 0 },
			Agent::gradientCalculator(DETECT_COLOR_START, DETECT_COLOR_END,
				(WANDERING_STARTING_POP + CHASER_STARTING_POP) * foodEaten / (2 * FOOD_PER_ROUND)));
	}

	void update(std::vector<Food>* foods) override {
		//std::cout<< "C:" << location.x << "\t" << location.y << "\n";


		bool foodInDetectionRange = false;
		for (int i = 0; i < (*foods).size(); i++) { //seeks if in detection range
			if (Vector2Distance((*foods)[i].location, location) < detectRange) {
				targetPos = (*foods)[i].location;
				foodInDetectionRange = true;
			}
		}

		if (!foodInDetectionRange && (Vector2Distance(location, targetPos) < foodRange || Vector2Length(velocity) < .01)) // if slow or close to target
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



private:

	steady_clock::time_point timeOfLastEat = high_resolution_clock::now();

	void addForce(Vector2 f) {
		acceleration = f;
	}
};