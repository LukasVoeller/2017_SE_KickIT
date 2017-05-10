/*
 * BallStatus.hpp
 *
 *  Created on: 23.03.2017
 *      Author: student
 */

#ifndef BALLSTATUS_HPP_
#define BALLSTATUS_HPP_
#include "Vec2.hpp"

class BallStatus {
public:
	Vec2 position;
	Vec2 movement;

	float getVelocity() {
		return 0.0f; //TODO
	}
};

#endif /* BALLSTATUS_HPP_ */
