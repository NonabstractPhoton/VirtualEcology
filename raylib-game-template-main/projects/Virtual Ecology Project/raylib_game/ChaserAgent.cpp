#include "Agent.cpp"
#include "Food.cpp"





class ChaserAgent : public Agent {
public:

	ChaserAgent(Vector2 location, float size, float maxSpeed, float maxForce, float foodRange, float detectRange, float rechargeTime) :
		Agent(location, size, maxSpeed, maxForce, foodRange, detectRange, rechargeTime) {

	}

	void draw() override {
		//std::cout << detectRange << "dr\n";
		//std::cout << foodRange << "fr\n";
		//std::cout << maxSpeed << "ms\n";
		//std::cout << maxForce << "mf\n";
		DrawCircle(location.x, location.y, 5, BLUE);
		DrawCircleGradient(location.x, location.y, detectRange, Color{ 255, 255, 255, 0 }, DETECT_COLOR);
		DrawCircleGradient(location.x, location.y, foodRange, Color{ 255, 255, 255, 0 }, EAT_COLOR);
	}

    void update(std::vector<Food>* foods) override {
		//std::cout << "C:" << location.x << "\t" << location.y << "\n";


		bool foodInDetectionRange = false;
		for (int i = 0; i < (*foods).size(); i++) { //seeks if in detection range
			if (Vector2Distance((*foods)[i].location, location) < detectRange) {
				targetPos = (*foods)[i].location;
				foodInDetectionRange = true;
			}
		}


		if (!foodInDetectionRange && (Vector2Distance(location, targetPos) < foodRange))
		{
			targetPos = { (float)(rand() % XDIM), (float)(rand() % YDIM) };
		}
		
        seekTarget();

		consumeFoodInRange(foods);

		location = Vector2Add(location, velocity);
		velocity = Vector2Add(velocity, acceleration);
    }



private:

    const float SIZE = 1, MAX_SPEED = 3, MAX_FORCE = .1, FOOD_RANGE = 5, DETECT_RANGE = 100, RECHARGE_TIME = 0;

    void addForce(Vector2 f) {
        acceleration = f;
    }
};