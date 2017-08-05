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

class MotorCommunicatorInterface {
public:
	virtual void moveTo(float y) = 0;	//Redundant?
	virtual void kick() = 0;			//Redundant?

	virtual void linearMovement(int positionL) = 0;

protected:

	//TODO Elternklassen für die folgenden vier Funktionen
	virtual int closePort() = 0;
	virtual void readPort() = 0;

	virtual void driverInit() = 0;
	virtual void motorSwitchon() = 0;
	virtual void homing() = 0;

	//New Functions
	virtual void sendPositionToDriver(int driverin) = 0;
	virtual void motorByHand() = 0;

	//Shooting Functions
	virtual void shootingMove(int positionS) {}
	virtual void rotation(int positionR) {}
	virtual void shoot1() {}
	virtual void shoot2() {}
	virtual void trickshot() {}

	char* port;
	int socketId;
	int nibble1;
	int nibble2;

	virtual int openPort() {
		struct ifreq ifr;
		struct sockaddr_can addr;

		this->socketId = socket(PF_CAN, SOCK_RAW, CAN_RAW);
		if (this->socketId < 0) {
			return -1;
		} else {
			std::cout << "socketid: " << this->socketId << std::endl;
		}

		addr.can_family = AF_CAN;
		strcpy(ifr.ifr_name, port);
		if (ioctl(this->socketId, SIOCGIFINDEX, &ifr) < 0) {
			std::cout << "ioctl failed port: " << port << std::endl;
			return (-1);
		}

		addr.can_ifindex = ifr.ifr_ifindex;
		std::cout << "addr.can_ifindex: " << addr.can_ifindex  << std::endl;

		if(fcntl(this->socketId, F_SETFL, O_NONBLOCK) < 0 ){
			std::cout << "fcntl failed port: " << port << std::endl;
		}
		if (bind(this->socketId, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
			std::cout << "bind failed port: " << port << std::endl;
			return -1;
		}

		return 0;
	}

	virtual void frameInit(int ID, int DLC, int Data_0, int Data_1, int Data_2, int Data_3, int Data_4, int Data_5, int Data_6, int Data_7) {
		//Version frame_init() form TestProject_colson_backup for LinMot RS01

		openPort();
		struct can_frame frame;
		frame.can_id = ID; 		//COB ID 200 für RxPDO1 + Can ID 1
		frame.can_dlc = DLC; 	//Datenanzahl
		frame.data[0] = Data_0; //Daten
		frame.data[1] = Data_1; //Daten
		frame.data[2] = Data_2; //...
		frame.data[3] = Data_3;
		frame.data[4] = Data_4;
		frame.data[5] = Data_5;
		frame.data[6] = Data_6;
		frame.data[7] = Data_7;
		sendPort(&frame);
		closePort();
	}

	virtual int sendPort(struct can_frame *frame) {
		int retval = write(socketId, frame, sizeof(struct can_frame));

		if (retval != sizeof(struct can_frame)){
			std::cout << "write failed port: " << port << " socketId: " << socketId << " retval: " << retval << " errno: " << strerror(errno) << std::endl;
			return -1;
		}
		return 0;
	}
};

#endif /* INTERFACEMOTORCOMMUNICATOR_HPP */
