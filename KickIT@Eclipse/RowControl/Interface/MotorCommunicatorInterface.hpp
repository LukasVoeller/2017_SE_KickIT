#ifndef INTERFACEMOTORCOMMUNICATOR_HPP
#define INTERFACEMOTORCOMMUNICATOR_HPP

#include <net/if.h>
#include <linux/can.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring>
#include <iostream>
#include "../../DataType/RowEnum.hpp"

class MotorCommunicatorInterface {
public:
	virtual void kick() = 0;
	virtual void linearMovement(int position) = 0;

protected:
	Row row;
	char* port;
	int socketId;
	int nibbleRotary = 1;
	int nibbleTranslational = 1;

	virtual void homing() = 0;
	virtual void driverInit() = 0;

	int switchedNibbleT() {
		nibbleTranslational++;
		return nibbleTranslational;
	}

	int switchedNibbleR() {
		nibbleRotary++;
		return nibbleRotary;
	}

	int openPort() {
		struct ifreq ifr;
		struct sockaddr_can addr;

		this->socketId = socket(PF_CAN, SOCK_RAW, CAN_RAW);
		if (this->socketId < 0) {
			return -1;
		}

		addr.can_family = AF_CAN;
		strcpy(ifr.ifr_name, port);
		if (ioctl(this->socketId, SIOCGIFINDEX, &ifr) < 0) {
			std::cout << "ioctl failed port: " << port << std::endl;
			return (-1);
		}

		addr.can_ifindex = ifr.ifr_ifindex;

		if (fcntl(this->socketId, F_SETFL, O_NONBLOCK) < 0) {
			std::cout << "fcntl failed port: " << port << std::endl;
		}
		if (bind(this->socketId, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
			std::cout << "bind failed port: " << port << std::endl;
			return -1;
		}

		return 0;
	}

	void frameInit(int ID, int DLC, int Data_0, int Data_1, int Data_2,
			int Data_3, int Data_4, int Data_5, int Data_6, int Data_7) {
		openPort();

		struct can_frame frame;
		frame.can_id = ID; 		//COB ID 200 für RxPDO1 + Can ID 1
		frame.can_dlc = DLC; 	//Datenanzahl
		frame.data[0] = Data_0; //Daten
		frame.data[1] = Data_1;
		frame.data[2] = Data_2; //Nibble
		frame.data[3] = Data_3;
		frame.data[4] = Data_4;
		frame.data[5] = Data_5;
		frame.data[6] = Data_6;
		frame.data[7] = Data_7;

		sendPort(&frame);
		closePort();
	}

	int sendPort(struct can_frame *frame) {
		int retval = write(socketId, frame, sizeof(struct can_frame));

		if (retval != sizeof(struct can_frame)) {
			std::cout << "write failed port!" << std::endl;
			return -1;
		}
		return 0;
	}



	void closePort() {
		close(this->socketId);
	}
};

#endif /* INTERFACEMOTORCOMMUNICATOR_HPP */
