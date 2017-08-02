#include <iostream>
#include <stdio.h>
#include <cstring>
#include <unistd.h>		//For write in sendPort
#include "MotorComRS01Impl.hpp"

using namespace std;

MotorComRS01Impl::MotorComRS01Impl(Row r) {
	this->socketId = 0;
	this->nibble1 = 1;
	this->nibble2 = 1;

	switch (r) {
	case DEFENSE:
		this->port = "can1";
		driverInit();
		break;
	default:
		cout << "Not implemented" << endl;
		break;
	}
}

void MotorComRS01Impl::moveTo(float y) {
	//TODO
}

void MotorComRS01Impl::kick() {
	//TODO
}

int MotorComRS01Impl::openPort(const char* port) {
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

int MotorComRS01Impl::closePort() {
	close(this->socketId);
	return 0;
}

int MotorComRS01Impl::sendPort(struct can_frame *frame) {
	int retval = write(socketId, frame, sizeof(struct can_frame));
	if (retval != sizeof(struct can_frame))
		return -1;
	return 0;
}

void MotorComRS01Impl::readPort() {
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

void MotorComRS01Impl::frameInit(int ID, int DLC, int Data_0, int Data_1,
		int Data_2, int Data_3, int Data_4, int Data_5, int Data_6,
		int Data_7) {
	//Version frame_init() form TestProject_colson_backup for LinMot RS01

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

void MotorComRS01Impl::driverInit() {
	//Version driver_init() form TestProject_colson_backup for LinMot RS01

	cout << "Reseten RS01" << endl;
	frameInit(0x601, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); //Reset Command
	frameInit(0x602, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); //Reset Command
	frameInit(0x603, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); //Reset Command
	sleep(20);
	cout << "Operational RS01" << endl;
	frameInit(0x00, 0x2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(2);
	cout << "Ready to switch on RS01" << endl;
	frameInit(0x201, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x202, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x203, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	sleep(2);
	cout << "Switch on RS01" << endl;
	frameInit(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x202, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x203, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	sleep(2);
	cout << "Homing RS01" << endl;
	frameInit(0x201, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x202, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Homen Command an RXPD0 1
	frameInit(0x203, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Homen Command an RXPD0 1
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	sleep(25);
	cout << "Homed RS01" << endl;
	frameInit(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x202, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x203, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
}

void MotorComRS01Impl::motorSwitchon() {
	//Version motor_switchon2() form TestProject_colson_backup for LinMot RS01

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

void MotorComRS01Impl::homing() {
	//Version homing2() form TestProject_colson_backup for LinMot RS01

	cout << "Homing" << endl;
	frameInit(0x202, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Homen Command an RXPD0 1
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
	sleep(20);
	cout << "Homed" << endl;
}

void MotorComRS01Impl::sendPositionToDriver(int driverin) {
	//Version sent_position_to_driver2() form TestProject_colson_backup for LinMot RS01
	cout << "sendPositionToDriver() RS01" << endl;

	this->nibble1 = !(this->nibble1);
	int UpperPos = (driverin >> 8); //The lower 8 bits slide out
	int LowerPos = (driverin & 255); //Let the upper 8 bits disappear
	//Send to RXPD0 1 = 0x201(Address/ID), 0x8 = Databits, 0x3F 0x00 Controlword, 0x09 Nibble word that transmits the command
	//LowerPos the lower 8 bits of the target position, UpperPos the upper 8 bits of the target position , 0xBB 0x08 max. speed
	frameInit(0x201, 0x8, 0x3F, 0x00, nibble1, 0x09, LowerPos, UpperPos, 0xFF,
			0x00);
	//Send to RXPDO 2 the rest of the command
	//0x301 the address of RXPDO 2, 0x8 = Number of data bits
	//0x2c 0x01 acceleration, 0x2c 0x01 braking
	frameInit(0x301, 0x8, 0xAC, 0x00, 0xAC, 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
	return;
}

void MotorComRS01Impl::motorByHand() {
	//Version motor_by_hand2() form TestProject_colson_backup for LinMot RS01
	cout << "motorByHand() RS01" << endl;

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
	frameInit(0x202, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos1, pos2, 0xFF,
			0xFF); // RXPDO 1
	//This frame still belongs to the Got To Pos Command and is sent to RXPDO 2 therefore 0x301
	//The data words 0 and 1 are here for the acceleration 100 in Dec corresponds to an acceleration of 10 m / s²
	//The next two data words are for braking the scale is exactly like accelerating
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

	this->nibble1 = !(this->nibble1);
	cout << "Nibble: " << this->nibble1 << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos1, pos2, 0xFF,
			0xFF); // RXPDO 1
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
}

void MotorComRS01Impl::linearMovement(int positionL) {
	//Version linear_movement() form TestProject_colson_backup for LinMot RS01
	cout << "linearMovement() RS01" << endl;

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

void MotorComRS01Impl::shootingMove(int positionS) {
	//Version shooting_move() form TestProject_colson_backup for LinMot RS01
	cout << "shooting_move() RS01" << endl;

	int pos5;
	int pos6;

	positionS *= 10;
	pos5 = (positionS & 255);
	pos6 = (positionS >> 8);

	this->nibble1 = !(this->nibble1);
	cout << "Nibble: " << this->nibble1 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos5, pos6, 0xFF,
			0xFF); //Moving to 1.0 cm (rotary)(Shot)
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble1 = !(this->nibble1);
	cout << "nibble: " << this->nibble1 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos5, pos6, 0xFF,
			0xFF); //Moving to 1.0 cm (rotary)(Shot)
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
}

void MotorComRS01Impl::rotation(int positionR) {
	//Version rotation() form TestProject_colson_backup for LinMot RS01
	cout << "rotation() RS01" << endl;

	int pos1;
	int pos2;

	positionR *= 10;
	pos1 = (positionR & 255);
	pos2 = (positionR >> 8);

	this->nibble1 = !(this->nibble1);
	cout << "nibble: " << this->nibble1 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos1, pos2, 0x50,
			0x10); //Rotary movement
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble1 = !(this->nibble1);
	cout << "nibble: " << this->nibble1 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos1, pos2, 0x50,
			0x10); //Rotary movement
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
}

void MotorComRS01Impl::shoot1() {
	//Version shot() form TestProject_colson_backup for LinMot RS01
	cout << "shoot1() RS01" << endl;

	int position1;
	int position2;
	int position3;
	int position4;
	int position5;
	int pos1;
	int pos2;
	int pos3;
	int pos4;
	int pos11;
	int pos22;
	int pos33;
	int pos44;
	int pos444;
	int pos333;

	//Linear part position
	position1 = 25; 	//Position to move the dummies 2.5 cm to the right side
	position3 = 150; //Position that we want at the end of the movement here it's the home position
	//Rotary part position
	position2 = 10;		//Position to ready up the shot (backing up)
	position4 = -10;	//Position to shot onward
	position5 = 0;		//Position of reset
	//The following lines are there to make the asking positions able to be read
	position1 *= 10;
	position3 *= 10;
	position2 *= 10;
	position4 *= 10;
	position5 *= 10;
	//Position1
	pos1 = (position1 & 255);
	pos2 = (position1 >> 8);
	//Position3 (position3 because it activates in the third)
	pos3 = (position3 & 255);
	pos4 = (position3 >> 8);
	//Position2
	pos11 = (position2 & 255);
	pos22 = (position2 >> 8);
	//Position4
	pos33 = (position4 & 255);
	pos44 = (position4 >> 8);
	//Position5
	pos333 = (position5 & 255);
	pos444 = (position5 >> 8);

	this->nibble2 = 1;
	this->nibble1 = !(this->nibble1);
	cout << "Nibble1: " << this->nibble1 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos11, pos22, 0x50,
			0x10); //moving to -1.0 cm (rotary)
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

	nibble2 = !(nibble2);
	cout << "Nibble2: " << nibble2 << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, nibble2, 0x09, pos1, pos2, 0x50, 0x10); //Moving to 2.5 cm (linear)
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble1 = !(this->nibble1);
	cout << "Nibble1: " << this->nibble1 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos11, pos22, 0xFF,
			0xFF);
	//Moving to -1.0 cm (rotary). We had to double it because of the nibble we had to make sure it respond every time
	frameInit(0x303, 0x8, 0xFF, 0xFF, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble2 = !(this->nibble2);
	cout << "Nibble2: " << nibble2 << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, nibble2, 0x09, pos1, pos2, 0x50, 0x10);
	//Moving to 2.5 cm (linear). We had to double it because of the nibble we had to make sure it respond every time
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	usleep(200000); //This command make the program wait a few milisecond

	this->nibble1 = !(this->nibble1);
	cout << "Nibble1: " << this->nibble1 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos33, pos44, 0xFF,
			0x10); //Moving to 1.0 cm (rotary)(Shot)
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	usleep(200000);

	this->nibble2 = !(this->nibble2);
	cout << "Nibble2: " << nibble2 << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, nibble2, 0x09, pos3, pos4, 0x50, 0x10); //Moving to 15.0 cm (linear)
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble1 = !(this->nibble1);
	cout << "Nibble1: " << this->nibble1 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos333, pos444, 0x50,
			0x10); //Moving to 0.0 cm, homing position (rotary)
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
}

void MotorComRS01Impl::shoot2() {
	//Version shot2() form TestProject_colson_backup for LinMot RS01
	cout << "shoot2() RS01" << endl;

	rotation(-10);
	linearMovement(25);
	usleep(200000); //This command make the program wait a few milisecond

	shootingMove(10);
	usleep(200000);

	linearMovement(150);
	rotation(0);

	this->nibble1 = !(this->nibble1);
}

void MotorComRS01Impl::trickshot() {
	//Version trickshot_around_theball() form TestProject_colson_backup for LinMot RS01
	cout << "trickshot() RS01" << endl;

	int position1;
	int position2;
	int position3;
	int position4;
	int position5;
	int position6;
	int position7;
	int position8;
	int position9;
	int position10;
	int pos1;
	int pos12;
	int pos2;
	int pos22;
	int pos3;
	int pos32;
	int pos4;
	int pos42;
	int pos5;
	int pos52;
	int pos6;
	int pos62;
	int pos7;
	int pos72;
	int pos8;
	int pos82;
	int pos9;
	int pos92;
	int pos10;
	int pos102;

	//Linear part's position
	position1 = 130; //Position to move the dummies 2.5 cm to the right side
	position3 = 150; //Position that we want at the end of the movement here it's the home position
	position6 = 100; //Position to slide pass the ball
	position7 = 150; //Position to slide pass the ball in the other way
	position8 = 130; //Position to go back to the right side and ready up the shot

	//Rotary part's position
	position2 = 10;	//Position to go behind the ball (backing up)
	position4 = -10;	//Turn forward
	position9 = 10;	//Turn back
	position10 = -10;	//Position to shot onward
	position5 = 0;	//Position of reset

	//The following lines are there to make the asking positions able to be read
	position1 *= 10;
	position3 *= 10;
	position2 *= 10;
	position4 *= 10;
	position5 *= 10;
	position6 *= 10;
	position7 *= 10;
	position8 *= 10;
	position9 *= 10;
	position10 *= 10;

	//Position1
	pos1 = (position1 & 255);
	pos12 = (position1 >> 8);
	//Position3 (position3 because it activates in the third)
	pos3 = (position3 & 255);
	pos32 = (position3 >> 8);
	//Position2
	pos2 = (position2 & 255);
	pos22 = (position2 >> 8);
	//Position4
	pos4 = (position4 & 255);
	pos42 = (position4 >> 8);
	//Position5
	pos5 = (position5 & 255);
	pos52 = (position5 >> 8);
	//Position6
	pos6 = (position6 & 255);
	pos62 = (position6 >> 8);
	//Position7
	pos7 = (position7 & 255);
	pos72 = (position7 >> 8);
	//Position8
	pos8 = (position8 & 255);
	pos82 = (position8 >> 8);
	//Position9
	pos9 = (position9 & 255);
	pos92 = (position9 >> 8);
	//Position10
	pos10 = (position10 & 255);
	pos102 = (position10 >> 8);

	this->nibble2 = 1;
	this->nibble1 = !(this->nibble1);
	cout << "Nibble1: " << this->nibble1 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos2, pos22, 0x50,
			0x00); //Moving to 1.0 cm (rotary)
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble2 = !(this->nibble2);
	cout << "Nibble2: " << this->nibble2 << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, this->nibble2, 0x09, pos1, pos12, 0x50,
			0x00); //Moving to 2.5 cm (linear)
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble1 = !(this->nibble1);
	cout << "Nibble1: " << this->nibble1 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos2, pos22, 0x50,
			0x00); //Moving to 1.0 cm (rotary). We had to double it because of the nibble we had to make sure it respond every time
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble2 = !(this->nibble2);
	cout << "Nibble2: " << this->nibble2 << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, this->nibble2, 0x09, pos1, pos12, 0x50,
			0x00); //Moving to 2.5 cm (linear). We had to double it because of the nibble we had to make sure it respond every time
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	sleep(2); //This command make the program wait a few milisecond

	this->nibble1 = !(this->nibble1);
	cout << "Nibble1: " << this->nibble1 << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos6, pos62, 0x50,
			0x00); //Moving to 1.0 cm (linear)
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble2 = !(this->nibble2);
	cout << "Nibble2: " << this->nibble2 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble2, 0x09, pos4, pos42, 0x50,
			0x00); //Moving to -1.0 cm (rotary)
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	sleep(2); //This command make the program wait a few milisecond

	this->nibble1 = !(this->nibble1);
	cout << "Nibble1: " << this->nibble1 << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos7, pos72, 0x50,
			0x00); //Moving to 4.0 cm (linear)
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble2 = !(this->nibble2);
	cout << "Nibble2: " << this->nibble2 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble2, 0x09, pos9, pos92, 0x50,
			0x00); //Moving to 1.0 cm (rotary)
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	sleep(2); //This command make the program wait a few milisecond

	this->nibble1 = !(this->nibble1);
	cout << "Nibble1: " << this->nibble1 << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos8, pos82, 0x50,
			0x00); //Moving to 2.5 cm (linear).
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	sleep(2);

	this->nibble2 = !(this->nibble2);
	cout << "Nibble2: " << this->nibble2 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble2, 0x09, pos10, pos102, 0x50,
			0x00); //moving to -1.0 cm (rotary)(Shot)
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync
	sleep(2);

	this->nibble1 = !(this->nibble1);
	cout << "Nibble1: " << this->nibble1 << endl;
	frameInit(0x202, 0x8, 0x3F, 0x00, this->nibble1, 0x09, pos3, pos32, 0x50,
			0x00); //Moving to 15.0 cm (linear)
	frameInit(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble2 = !(this->nibble2);
	cout << "Nibble2: " << this->nibble2 << endl;
	frameInit(0x203, 0x8, 0x3F, 0x00, this->nibble2, 0x09, pos5, pos52, 0x50,
			0x00); //Moving to 0.0 cm, homing position (rotary)
	frameInit(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); //Sync

	this->nibble1 = !(this->nibble1);
}
