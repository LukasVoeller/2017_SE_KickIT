#ifndef MOTORCOMMUNICATORIMPL_HPP
#define MOTORCOMMUNICATORIMPL_HPP

#include <net/if.h>
#include <linux/can.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h> //for sockets
#include <sys/socket.h> // for sockets

class MotorCommunicatorImpl {
private:
	int socketId;
	bool openPort(const char* port);
};

#endif /* MOTORCOMMUNICATOR_HPP */

