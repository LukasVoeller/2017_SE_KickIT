#ifndef MOTORCOMMUNICATORIMPL_HPP
#define MOTORCOMMUNICATORIMPL_HPP

#include <net/if.h>
#include <linux/can.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "InterfaceMotorCommunicator.hpp"
#include "../DataType/RowEnum.hpp"

#include <sys/types.h> //for sockets
#include <sys/socket.h> // for sockets

class MotorCommunicatorImpl : public InterfaceMotorCommunicator{
public:
	MotorCommunicatorImpl(Row r);
	void moveTo(float y);
	void kick();

private:
    int socketId;
    int openPort(const char* port);
    void homing();
};


#endif /* MOTORCOMMUNICATOR_HPP */

