#include "Header.h"
#include "Food.cpp"

class Agent {

    public:
        Vector2 location;
        Vector2 velocity;
        Vector2 acceleration;
        Vector2 targetPos;
        float size, maxspeed, maxforce, foodRange, detectRange, rechargeTime;

		void draw() {}

		void seekTarget() { seek(); }

	private:
		const float maxComponentSpeed = 1.8f, maxForce = 1, mass = 50,
			rotationFrames = 90, slowdownDistance = 75, maxSpeedForStationaryTurns = .025f;
		int progress = 0;
		float angle = 360;



		void seek() {
			Vector2 desired = Vector2Subtract(targetPos, location);
			float distance = Vector2Length(desired);
			desired = Vector2Normalize(desired);

			if (distance <= slowdownDistance)
			{
				float newSpeed = (.66f + (distance / (3 * slowdownDistance))) * maxComponentSpeed;
				desired = Vector2Multiply(desired, { newSpeed, newSpeed });
			}
			else
			{
				desired = Vector2Multiply(desired, { maxComponentSpeed, maxComponentSpeed });
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