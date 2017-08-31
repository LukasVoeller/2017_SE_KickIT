#ifndef BALLSTATUS_HPP_
#define BALLSTATUS_HPP_

#include "../5_DataType/Vec2.hpp"

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
		this->movement.x = bs.movement.x;
		this->movement.y = bs.movement.y;

		this->position.x = bs.position.x;
		this->position.y = bs.position.y;

		return *this;
	}

	void update(float x, float y){
		Vec2 newPos(x,y);
		//std::cout << "new pos x: " << x << " new y: " << y << std::endl;

		this->movement = this->position.toTarget(newPos);
		this->position.update(x,y);
	}
};

#endif //BALLSTATUS_HPP_
