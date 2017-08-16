#ifndef INTERFACEROWCONTROLLER_HPP
#define INTERFACEROWCONTROLLER_HPP

#include "MotorCommunicatorInterface.hpp"
#include "../../DataType/TableConfig.hpp"
#include <cstdlib>

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
