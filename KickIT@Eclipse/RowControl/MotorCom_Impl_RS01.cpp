#include <RowControl/MotorCom_Impl_PS01.hpp>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <unistd.h>		//For write in sendPort

using namespace std;

MotorComRS01::MotorComRS01(Row r) :
		m_SocketId(0) {
	switch (r) {
	case KEEPER:
		port = "can0";
		driverInit();
		//homing();
		break;
	default:
		cout << "Not implemented" << endl;
		break;
	}
}

void MotorComRS01::moveTo(float y) {
	//TODO
}

void MotorComRS01::kick() {
	//TODO
}

int MotorComRS01::openPort(const char* port) {
	struct ifreq ifr;
	struct sockaddr_can addr;

	this->m_SocketId = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (this->m_SocketId < 0) {
		return -1;
	}

	addr.can_family = AF_CAN;
	strcpy(ifr.ifr_name, port);
	if (ioctl(this->m_SocketId, SIOCGIFINDEX, &ifr) < 0) {
		return (-1);
	}

	addr.can_ifindex = ifr.ifr_ifindex;
	fcntl(this->m_SocketId, F_SETFL, O_NONBLOCK);
	if (bind(this->m_SocketId, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		return -1;
	}

	return 0;
}

int MotorComRS01::closePort() {
	close(this->m_SocketId);
	return 0;
}

int MotorComRS01::sendPort(struct can_frame *frame) {
	int retval = write(m_SocketId, frame, sizeof(struct can_frame));
	if (retval != sizeof(struct can_frame))
		return -1;
	return 0;
}

void MotorComRS01::readPort() {
	/*
	 struct can_frame frame_rd;
	 int recvbytes = 0;

	 read_can_port = 1;
	 while (read_can_port) {
	 struct timeval timeout = { 1, 0 };
	 fd_set readSet;
	 FD_ZERO(&readSet);
	 FD_SET(soc, &readSet);

	 if (select((soc + 1), &readSet, NULL, NULL, &timeout) >= 0) {
	 if (!read_can_port)
	 break;
	 if (FD_ISSET(soc, &readSet)) {
	 recvbytes = read(soc, &frame_rd, sizeof(struct can_frame));
	 if (recvbytes) {
	 printf("dlc = %d, data = %s\n", frame_rd.can_dlc,
	 frame_rd.data);
	 read_can_port = 0;
	 }
	 }
	 }
	 }
	 */
	cout << "readPort() is not supported" << endl;
}

void MotorComRS01::frameInit(int ID, int DLC, int Data_0, int Data_1,
		int Data_2, int Data_3, int Data_4, int Data_5, int Data_6,
		int Data_7) {
	//Version frame_init() form TestProject_colson_backup hopefully for LinMot RS01

	openPort("can0");
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

void MotorComRS01::driverInit() {
	//Version driver_init() form TestProject_colson_backup hopefully for LinMot RS01

	cout << "Reseten" << endl;
	frameInit(0x601, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); //Reset Command
	frameInit(0x602, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); //Reset Command
	frameInit(0x603, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); //Reset Command
	sleep(20);
	cout << "Operational" << endl;
	frameInit(0x00, 0x2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(2);
	cout << "Ready to switch on" << endl;
	frameInit(0x201, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x202, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x203, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	sleep(2);
	cout << "Switch on" << endl;
	frameInit(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x202, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x203, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	sleep(2);
	cout << "Homing" << endl;
	frameInit(0x201, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x202, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Homen Command an RXPD0 1
	frameInit(0x203, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Homen Command an RXPD0 1
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	sleep(25);
	cout << "Homed" << endl;
	frameInit(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x202, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x203, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
}

void MotorComRS01::motorSwitchon() {
	//Version motor_switchon2() form TestProject_colson_backup hopefully for LinMot RS01

	int i = 0;
	cout << "What would you like to do?" << endl;
	cout << "1) Locking" << endl;
	cout << "2) Unlocking" << endl;
	cin >> i;

	switch (i) {
	case 1:
		frameInit(0x202, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		break;
	case 2:
		frameInit(0x202, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
		break;
	default:
		cout << "Try typing again!" << endl;
		break;
	}
	return;
}

void MotorComRS01::homing() {
	//Version homing2() form TestProject_colson_backup hopefully for LinMot RS01

	cout << "Homing" << endl;
	frameInit(0x202, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Homen Command an RXPD0 1
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
	sleep(20);
	cout << "Homed" << endl;
}
