#ifndef INTERFACEROWCONTROLLER_HPP
#define INTERFACEROWCONTROLLER_HPP

#include <cstdlib>

#include "../../5_DataType/TableConfig.hpp"
#include "../MotorCommunication/_MotorCommunicatorInterface.hpp"

class RowControllerInterface {

public:
	virtual void moveTo(float y) = 0;

	virtual void up() {}
	virtual void down() {}
	virtual void kick(int strength) {}

protected:
	MotorCommunicatorInterface* mcomm;

	bool isUp = false;
	bool isShooting = false;

	TableConfig tc;
};

#endif //INTERFACEROWCONTROLLER_HPP
