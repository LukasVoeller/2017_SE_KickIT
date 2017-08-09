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

static bool driversInitialized = false;

class MotorCommunicatorInterface {
public:
	virtual void kick() = 0;

	void linearMovement(int position){
		int pos1, pos2;

		if(position > 300 || position < 1){
			return;
		}

		position *= 10;

		pos1 = (position & 255);
		pos2 = (position >> 8);

		nibble = !(nibble);
		// FRAME_INIT Can_ID, DLC , Data, Data, Data, Data, Data, Data, Data, Data,
		// Nibble has to change every new COmmand, therefore nibble =! nibble
		// Position is transferred with two hex data, therefore pos1 pos2. Pos 1 are the lower 8 bits
		// 50 mm then corresponds to 500 in the data word as a hex number
		// The last two data words in the 0x201 frame are for the maximum speed
		frameInit(this->motorAddress2, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0xFF, 0xFF); // RXPDO 1
		// This frame still belongs to the Got To Pos Command and is sent to RXPDO 2 therefore 0x301
		// The data words 0 and 1 are here for the acceleration 100 in Dec corresponds to an acceleration of 10 m / s²
		//The next two data words are for braking the scale is exactly like accelerating
		frameInit(this->motorAddress3, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
		frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

	}

protected:

	Row row;
	char* port;
	int socketId;
	int nibble;

	int motorAddress2;
	int motorAddress3;
	int motorAddress6;


	virtual void homing() = 0;
	virtual void driverInit() = 0;


	virtual int openPort() {
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

	/*void driverInit() {
		driversInitialized = true;
		std::cout << "----- driver init -----" << std::endl;
		std::cout << std::endl;

		std::cout << "reset PS01..." << std::endl;
		frameInit(0x601, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); // Reset Command
		sleep(2);
		std::cout << "reset RS01..." << std::endl;
		frameInit(0x602, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); // Reset Command
		frameInit(0x603, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); // Reset Command
		sleep(20);
		std::cout << "operational..." << std::endl;
		frameInit(0x00, 0x2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		sleep(2);
		std::cout << "ready to switch on PS01..." << std::endl;
		frameInit(0x201, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		sleep(2);
		std::cout << "RS01..." << std::endl;
		frameInit(0x202, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frameInit(0x203, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

		frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

		sleep(2);

		std::cout << "switch on PS01..." << std::endl;
		frameInit(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		sleep(2);
		std::cout << "RS01..." << std::endl;
		frameInit(0x202, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frameInit(0x203, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

		frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

		sleep(2);
		std::cout << "homen  PS01..." << std::endl;
		frameInit(0x201, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		sleep(2);
		std::cout << "homen  RS01..." << std::endl;
		frameInit(0x202, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);// Homen Command an RXPD0 1
		frameInit(0x203, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);// Homen Command an RXPD0 1

		frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

		sleep(25);

		std::cout << "homed" << std::endl;
		frameInit(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		sleep(2);
		frameInit(0x202, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frameInit(0x203, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);

		frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

		std::cout << std::endl;



	}*/

	void closePort() {
		close(this->socketId);
	}


};

#endif /* INTERFACEMOTORCOMMUNICATOR_HPP */
