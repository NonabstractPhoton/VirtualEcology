#pragma once
#include "Header.h"
#include "Food.cpp"

class Agent {

public:

	Vector2 location;
	Vector2 velocity = { 0, 0 };
	Vector2 acceleration = { 0, 0 };
	Vector2 targetPos = { 0, 0 };
	float size, maxSpeed, maxForce, foodRange, detectRange, rechargeTime, foodEaten;


	Agent(Vector2 location, float size, float maxSpeed, float maxForce, float foodRange, float detectRange, float rechargeTime) {
		this->location = location;
		this->size = size;
		this->maxSpeed = maxSpeed;
		this->maxForce = maxForce;
		this->foodRange = foodRange;
		this->detectRange = detectRange;
		this->rechargeTime = rechargeTime;
		foodEaten = 0;
	}

	virtual void draw() {

	}

	virtual void update(std::vector<Food>* foods) {

	}


	void seekTarget() { seek(); }

	void toString() {
		std::cout << foodRange << "\t";
		std::cout << detectRange << "\n";
		
	}

	void consumeFoodInRange(std::vector<Food>* foods)
	{
		for (int i = 0; i < (*foods).size(); i++)
		{
			if (Vector2Distance(location, (*foods)[i].location) < foodRange)
			{
				foods->erase((*foods).begin() + i);
				foodEaten++;
				break;
			}
		}
	}

	bool operator< (const Agent& other) {
		return foodEaten < other.foodEaten;
	}

	Color gradientCalculator(Color s, Color f, float fraction) {
		return Color{
			static_cast<uint8_t>(s.r + (fraction * (f.r - s.r))),
			static_cast<uint8_t>(s.g + (fraction * (f.g - s.g))),
			static_cast<uint8_t>(s.b + (fraction * (f.b - s.b))),
			static_cast<uint8_t>(s.a + (fraction * (f.a - s.a)))
		};
	}

private:


	const float mass =  1,
		rotationFrames = 90, slowdownDistance = 75, maxSpeedForStationaryTurns = .025f;
	int progress = 0;
	float angle = 360;



	void seek() {


		Vector2 desired = Vector2Subtract(targetPos, location);
		float distance = Vector2Length(desired);
		desired = Vector2Normalize(desired);

		if (distance <= slowdownDistance)
		{
			float newSpeed = (.66f + (distance / (3 * slowdownDistance))) * maxSpeed;
			desired = Vector2Multiply(desired, { newSpeed, newSpeed });
		}
		else
		{
			desired = Vector2Multiply(desired, { maxSpeed, maxSpeed });
		}

		Vector2 steer = Vector2Subtract(desired, velocity);
		steer = Vector2ClampValue(steer, 0, maxForce);
		applyForce(steer);


		
	}


	void calculateAngle()
	{
		if (progress <= rotationFrames)
		{
			Vector2 interpolatedAngleDirection = Vector2Lerp(
				Vector2Normalize({ cosf(angle * DEG2RAD), sinf(angle * DEG2RAD) }),
				Vector2Normalize(velocity),
				progress / rotationFrames);

			angle = RAD2DEG * Vector2Angle(interpolatedAngleDirection, { 1, 0 });

			if (angle <= 0)
				angle += 360;

			progress++;
			// DrawCircle(200, 200, progress, SKYBLUE);
		}
		else
		{
			progress = 0;
		}
	}



	void applyForce(Vector2 force)
	{
		acceleration = (Vector2Multiply(force, { 1 / mass, 1 / mass }));
	}
};