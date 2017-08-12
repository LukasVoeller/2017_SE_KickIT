#ifndef INTERFACEROWCONTROLLER_HPP
#define INTERFACEROWCONTROLLER_HPP

#include "MotorCommunicatorInterface.hpp"

class RowControllerInterface {

public:
	void moveTo(float y){
		mcomm->linearMovement(y);
	}

protected:
	MotorCommunicatorInterface* mcomm;
};

#endif //INTERFACEROWCONTROLLER_HPP
