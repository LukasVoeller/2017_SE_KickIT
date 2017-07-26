#ifndef MOTORCOMMUNICATORIMPL_HPP
#define MOTORCOMMUNICATORIMPL_HPP

#include <net/if.h>
#include <linux/can.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "InterfaceMotorCommunicator.hpp"
#include "../DataType/RowEnum.hpp"

#include <sys/types.h> 	//for sockets
#include <sys/socket.h> //for sockets

class MotorCommunicatorImpl: public InterfaceMotorCommunicator {
public:
	MotorCommunicatorImpl(Row r);
	void moveTo(float y);
	void kick();

private:
	int socketId;

	int openPort();
	int closePort();
	int sendPort(struct can_frame *frame);
	void readPort();
	void frameInit(int ID, int DLC, int Data_0, int Data_1, int Data_2,
			int Data_3, int Data_4, int Data_5, int Data_6, int Data_7);//Parameter?

	void homing();
	void driverInit();
};

#endif /* MOTORCOMMUNICATOR_HPP */
