#ifndef MOTORCOM_IMPL_PS01_HPP
#define MOTORCOM_IMPL_PS01_HPP

#include <net/if.h>
#include <linux/can.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 	//For sockets
#include <sys/socket.h> //For sockets

#include "../../DataType/RowEnum.hpp"
#include "../Interface/MotorCommunicatorInterface.hpp"

class MotorComPS01Impl: public MotorCommunicatorInterface {
public:
	MotorComPS01Impl(Row r);
	void kick();
	void linearMovement(int posotion);

protected:

	void driverInit();
	void homing();

};

#endif /* MOTORCOM_IMPL_PS01_HPP */
