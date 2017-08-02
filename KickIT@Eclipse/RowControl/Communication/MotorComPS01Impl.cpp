#include <iostream>
#include <stdio.h>
#include <cstring>
#include <unistd.h>		//For write in sendPort
#include "MotorComPS01Impl.hpp"

using namespace std;

MotorComPS01Impl::MotorComPS01Impl(Row r) {
	this->socketId = 0;
	this->nibble1 = 1;
	this->nibble2 = 1;

	switch (r) {
	case KEEPER:
		this->port = "can0";
		driverInit();
		break;
	default:
		cout << "Not implemented PS01" << endl;
		break;
	}
}

void MotorComPS01Impl::moveTo(float y) {
	//TODO
}

void MotorComPS01Impl::kick() {
	//TODO
}

int MotorComPS01Impl::openPort(const char* port) {
	struct ifreq ifr;
	struct sockaddr_can addr;

	this->socketId = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (this->socketId < 0) {
		return -1;
	}

	addr.can_family = AF_CAN;
	strcpy(ifr.ifr_name, port);
	if (ioctl(this->socketId, SIOCGIFINDEX, &ifr) < 0) {
		return (-1);
	}

	addr.can_ifindex = ifr.ifr_ifindex;
	fcntl(this->socketId, F_SETFL, O_NONBLOCK);
	if (bind(this->socketId, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		return -1;
	}

	return 0;
}

int MotorComPS01Impl::closePort() {
	close(this->socketId);
	return 0;
}

int MotorComPS01Impl::sendPort(struct can_frame *frame) {
	int retval = write(socketId, frame, sizeof(struct can_frame));
	if (retval != sizeof(struct can_frame))
		return -1;
	return 0;
}

void MotorComPS01Impl::readPort() {
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

void MotorComPS01Impl::frameInit(int ID, int DLC, int Data_0, int Data_1,
		int Data_2, int Data_3, int Data_4, int Data_5, int Data_6,
		int Data_7) {
	//Version frame_init() form TestProject_colson_backup for LinMot PS01
	cout << "frameInit() PS01" << endl;

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

void MotorComPS01Impl::driverInit() {
	//Version driver_init() form TestProject_colson_backup for LinMot PS01
	cout << "driverInit() PS01" << endl;

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

void MotorComPS01Impl::motorSwitchon() {
	//Version motor_switchon1() form TestProject_colson_backup for LinMot PS01
	cout << "motorSwitchon() PS01" << endl;

	int i = 0;
	cout << "What would you like to do?" << endl;
	cout << "1) Locking" << endl;
	cout << "2) Unlocking" << endl;
	cin >> i;

	switch (i) {
	case 1:
		frameInit(0x201, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		break;
	case 2:
		frameInit(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
		break;
	default:
		cout << "Try typing again!" << endl;
		break;
	}
	return;
}

void MotorComPS01Impl::homing() {
	//Version homing1() form TestProject_colson_backup for LinMot PS01
	cout << "homing() PS01" << endl;

	frameInit(0x201, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Homen Command an RXPD0 1
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	sleep(20);
}

void MotorComPS01Impl::sendPositionToDriver(int driverin) {
	//Version sent_position_to_driver1() form TestProject_colson_backup for LinMot PS01
	cout << "sendPositionToDriver() PS01" << endl;

	this->nibble1 = !(this->nibble1);
	int UpperPos = (driverin >> 8); //The lower 8 bits slide out
	int LowerPos = (driverin & 255); //Let the upper 8 bits disappear
	//Send to RXPD0 1 = 0x201(Address/ID), 0x8 = Databits, 0x3F 0x00 Controlword, 0x09 Nibble word that transmits the command,
	//LowerPos the lower 8 bits of the target position, UpperPos the upper 8 bits of the target position , 0xBB 0x08 max. speed
	frameInit(0x201, 0x8, 0x3F, 0x00, nibble1, 0x09, LowerPos, UpperPos, 0xBB,
			0x08);
	//Send to RXPDO 2 the rest of the command
	//0x301 the address of RXPDO 2, 0x8 = Number of data bits
	//0x2c 0x01 acceleration, 0x2c 0x01 braking
	frameInit(0x301, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	return;
}

void MotorComPS01Impl::motorByHand() {
	//Version motor_by_hand1() form TestProject_colson_backup for LinMot PS01
	cout << "motorByHand() PS01" << endl;

	int pos1;
	int pos2;
	int position;
	cout << "Enter the position and confirm with enter" << endl;
	cin >> position;

	position *= 10;

	pos1 = (position & 255);
	pos2 = (position >> 8);

	this->nibble1 = !(this->nibble1);
	cout << "Nibble: " << this->nibble1 << endl;
	//FRAME_INIT Can_ID, DLC , Data, Data, Data, Data, Data, Data, Data, Data,
	//Nibble has to change every new COmmand, therefore nibble =! nibble
	//Position is transferred with two hex data, therefore pos1 pos2. Pos 1 are the lower 8 bits
	//50 mm then corresponds to 500 in the data word as a hex number
	//The last two data words in the 0x201 frame are for the maximum speed
	frameInit(0x201, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos1, pos2, 0xBB,
			0x08); //RXPDO 1
	//This frame still belongs to the Got To Pos Command and is sent to RXPDO 2 therefore 0x301
	//The data words 0 and 1 are here for the acceleration 100 in Dec corresponds to an acceleration of 10 m / s²
	//The next two data words are for braking the scale is exactly like accelerating
	frameInit(0x301, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble1 = !(this->nibble1);
	cout << "Nibble: " << this->nibble1 << endl;
	frameInit(0x201, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos1, pos2, 0xBB,
			0x08); //RXPDO 1
	frameInit(0x301, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
}

void MotorComPS01Impl::linearMovement(int positionL) {
	//Version linear_movement() form TestProject_colson_backup for LinMot PS01
	cout << "linearMovement() PS01" << endl;

	int pos3;
	int pos4;

	positionL *= 10;
	pos3 = (positionL & 255);
	pos4 = (positionL >> 8);

	this->nibble2 = !(this->nibble2);
	cout << "Nibble2: " << this->nibble2 << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, this->nibble2, 0x09, pos3, pos4, 0x50,
			0x10); //Moving to 15.0 cm (linear)
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble2 = !(this->nibble2);
	cout << "Nibble2: " << this->nibble2 << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, this->nibble2, 0x09, pos3, pos4, 0x50,
			0x10); //Moving to 15.0 cm (linear)
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
}
