
#ifndef MOTORCOMMUNICATORIMPL_HPP
#define MOTORCOMMUNICATORIMPL_HPP

#include <net/if.h>
#include <linux/can.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "MotorCommunicatorInterface.hpp"
#include "../DataType/RowEnum.hpp"

#include <sys/types.h> //for sockets
#include <sys/socket.h> // for sockets

class MotorCommunicatorImpl : public MotorCommunicatorInterface{
public:
	void moveTo(float y);
	void kick();
	MotorCommunicatorImpl(Row r);

private:
    //int socketId;
    bool openPort(const char* port);
};


#endif /* MOTORCOMMUNICATOR_HPP */

