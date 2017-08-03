#ifndef MOTORCOM_IMPL_PS01_HPP
#define MOTORCOM_IMPL_PS01_HPP

#include <net/if.h>
#include <linux/can.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "../DataType/RowEnum.hpp"

#include <sys/types.h> 	//For sockets
#include <sys/socket.h> //For sockets
#include "../Interface/MotorCommunicatorInterface.hpp"

class MotorComPS01Impl: public MotorCommunicatorInterface {
public:
	MotorComPS01Impl(Row r);
	void moveTo(float y);
	void kick();

	virtual void linearMovement(int positionL);

private:
	int openPort();
	int closePort();
	int sendPort(struct can_frame *frame);
	void readPort();

	void frameInit(int ID, int DLC, int Data_0, int Data_1, int Data_2,
			int Data_3, int Data_4, int Data_5, int Data_6, int Data_7);
	void driverInit();
	void motorSwitchon();
	void homing();

	//New Functions
	virtual void sendPositionToDriver(int driverin);
	virtual void motorByHand();

};

#endif /* MOTORCOM_IMPL_PS01_HPP */
