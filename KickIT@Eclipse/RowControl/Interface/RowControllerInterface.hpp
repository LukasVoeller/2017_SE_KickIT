#ifndef INTERFACEROWCONTROLLER_HPP
#define INTERFACEROWCONTROLLER_HPP

#include "MotorCommunicatorInterface.hpp"
#include <cstdlib>

class RowControllerInterface {

public:
	void moveTo(float y) {
		int castedY = (int) y;
		//if (std::abs(castedY - lastY) >= 6) {
			mcomm->linearMovement(castedY);
			//lastY = castedY;
		//}
	}

	virtual void up() {}
	virtual void down() {}
	virtual void kick(int strength) {}

protected:
	MotorCommunicatorInterface* mcomm;
	int lastY = 0;

	bool isUp = false;
	bool isShooting = false;
};

#endif //INTERFACEROWCONTROLLER_HPP
