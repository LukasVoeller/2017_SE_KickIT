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
	void kick();

protected:

	void driverInit();
	void homing();
};

#endif /* MOTORCOM_IMPL_PS01_HPP */
