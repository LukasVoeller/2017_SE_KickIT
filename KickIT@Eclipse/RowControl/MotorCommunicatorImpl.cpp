#include "MotorCommunicatorImpl.hpp"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <unistd.h>		//For write in sendPort

int soc;
int readCanPort;

using namespace std;

MotorCommunicatorImpl::MotorCommunicatorImpl(Row r):socketId(0) {
	switch (r) {
	case KEEPER:
		port = "can0";
		homing();
		break;
	default:
		cout << "not implemented" << endl;
		break;
	}
}

void MotorCommunicatorImpl::moveTo(float y) {

}

void MotorCommunicatorImpl::kick() {

}

int MotorCommunicatorImpl::openPort() {
	struct ifreq ifr;
	struct sockaddr_can addr;

	socketId = socket(PF_CAN, SOCK_RAW, CAN_RAW);

	if (socket < 0) {
		cout << "opening port failed" << endl;
		return -1;
	}

	addr.can_family = AF_CAN;
	strcpy(ifr.ifr_name, port); //C++ functions!

	if (ioctl(socketId, SIOCGIFINDEX, &ifr) < 0) {
		cout << "opening port failed" << endl;
		return -1;
	}

	addr.can_ifindex = ifr.ifr_ifindex;
	fcntl(socketId, F_SETFL, O_NONBLOCK);

	if (bind(socketId, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		cout << "opening port failed" << endl;
		return -1;
	}

	return 0;
}

int MotorCommunicatorImpl::closePort() {
	close(soc);
	return 0;
}

int MotorCommunicatorImpl::sendPort(struct can_frame *frame) {
	int retval = write(soc, frame, sizeof(struct can_frame));
	if (retval != sizeof(struct can_frame))
		return -1;
	return 0;
}

void MotorCommunicatorImpl::readPort() {
	/*struct can_frame frame_rd;
	int recvbytes = 0;

	readCanPort = 1;
	while (readCanPort) {
		struct timeval timeout = { 1, 0 };
		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(soc, &readSet);

		if (select((soc + 1), &readSet, NULL, NULL, &timeout) >= 0) {
			if (!readCanPort)
				break;
			if (FD_ISSET(soc, &readSet)) {
				recvbytes = read(soc, &frame_rd, sizeof(struct can_frame));
				if (recvbytes) {
					printf("dlc = %d, data = %s\n", frame_rd.can_dlc,
							frame_rd.data);
					readCanPort = 0;
				}
			}
		}
	}*/
	cout << "not supported" << endl;
}

void MotorCommunicatorImpl::frameInit(int ID, int DLC, int Data_0, int Data_1,
		int Data_2, int Data_3, int Data_4, int Data_5, int Data_6,
		int Data_7) {

	struct can_frame frame;

	frame.can_id = ID; 		//COB ID 200 für RxPDO1 + Can ID 1
	frame.can_dlc = DLC; 	//Datacount
	frame.data[0] = Data_0; //Data
	frame.data[1] = Data_1;
	frame.data[2] = Data_2;
	frame.data[3] = Data_3;
	frame.data[4] = Data_4;
	frame.data[5] = Data_5;
	frame.data[6] = Data_6;
	frame.data[7] = Data_7;
	sendPort(&frame);

	closePort();

}

void MotorCommunicatorImpl::homing() {
	cout << "Homen... " << endl;

	frameInit(0x201, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);	//Homen Command an RXPD0 1
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);	//Sync
	sleep(25);

	cout << "Gehomed" << endl;
}
