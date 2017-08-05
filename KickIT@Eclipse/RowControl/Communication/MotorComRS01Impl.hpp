#ifndef MOTORCOM_IMPL_RS01_HPP
#define MOTORCOM_IMPL_RS01_HPP

#include <net/if.h>
//#include <linux/can.h>
//#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "../DataType/RowEnum.hpp"

#include <sys/types.h> 	//For sockets
//#include <sys/socket.h> //For sockets
#include "../Interface/MotorCommunicatorInterface.hpp"

class MotorComRS01Impl: public MotorCommunicatorInterface {
public:
	MotorComRS01Impl(Row r);
	void moveTo(float y);
	void kick();

	virtual void linearMovement(int positionL);

private:

	int closePort();
	void readPort();

	void driverInit();
	void motorSwitchon();
	void homing();

	//New Functions
	virtual void sendPositionToDriver(int driverin);
	virtual void motorByHand();

	virtual void shootingMove(int positionS);
	virtual void rotation(int positionR);
	virtual void shoot1();
	virtual void shoot2();
	virtual void trickshot();
};

#endif /* MOTORCOM_IMPL_PS01_HPP */
