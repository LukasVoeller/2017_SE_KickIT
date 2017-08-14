#ifndef INTERFACEROWCONTROLLER_HPP
#define INTERFACEROWCONTROLLER_HPP

#include "MotorCommunicatorInterface.hpp"
#include <cstdlib>

class RowControllerInterface {

public:
	void moveTo(float y){
		int castedY = (int)y;
		if(std::abs(castedY-lastY) >= 10){
			mcomm->linearMovement(castedY);
			lastY = castedY;
		}
	}

protected:
	MotorCommunicatorInterface* mcomm;
	int lastY = 0;
};

#endif //INTERFACEROWCONTROLLER_HPP
