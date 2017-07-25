#ifndef BALLSTATUS_HPP_
#define BALLSTATUS_HPP_
#include "Vec2.hpp"

class BallStatus {
public:
	Vec2 movement;
	Vec2 position;

	BallStatus(float posx, float posy, float movementx, float movementy) :
			movement(movementx, movementy), position(posx, posy) {
	}

	BallStatus() :
			movement(0.0f, 0.0f), position(0.0f, 0.0f) {

	}

	float getVelocity() {
		return 0.0f; //TODO
	}

	BallStatus & operator=(const BallStatus & bs) {
		movement.x = bs.movement.x;
		movement.y = bs.movement.y;

		position.x = bs.position.x;
		position.y = bs.position.y;

		return *this;
	}
};

#endif /* BALLSTATUS_HPP_ */
