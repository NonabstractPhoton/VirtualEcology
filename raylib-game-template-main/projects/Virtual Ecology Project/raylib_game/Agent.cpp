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

	void draw() {
		DrawCircle(location.x, location.y, 5, detectRange>0?BLUE:GREEN);
		DrawCircleGradient(location.x, location.y, detectRange, Color{255, 255, 255, 0}, DETECT_COLOR);
		DrawCircleGradient(location.x, location.y, foodRange, Color{255, 255, 255, 0 }, EAT_COLOR);
	}

	void update(std::vector<Food>* foods) {}


	void seekTarget() { seek(); }

private:


	const float mass = 50,
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