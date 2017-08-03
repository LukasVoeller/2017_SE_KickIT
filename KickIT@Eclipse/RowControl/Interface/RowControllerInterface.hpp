#ifndef INTERFACEROWCONTROLLER_HPP
#define INTERFACEROWCONTROLLER_HPP

#include "MotorCommunicatorInterface.hpp"

class RowControllerInterface {
public:
	//for testing
	void moveTo(float y){
		mcomm->linearMovement(y);
	}
private:

protected:
	MotorCommunicatorInterface* mcomm;
};

#endif /* INTERFACEROWCONTROLLER_HPP */
