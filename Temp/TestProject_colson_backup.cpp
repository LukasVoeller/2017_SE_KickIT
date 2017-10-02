//============================================================================
// Name        : rotary_and_linear part.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <cstdio>




// new
#include <sys/socket.h>
#include <sys/types.h>

//using namespace cv;
using namespace std;
//using namespace Pylon;

int BlueLow = 159;
int GreenLow = 170;
int RedLow = 0;
int BlueHigh = 255;
int GreenHigh = 255;
int RedHigh = 255;
int soc;
int read_can_port;
int nibble = 1;  //Wozu ist der gut???
int nibble2 = 1;

//Datei für Mittelpunkt-Koordinate des Balles

double lastx = 0;
double lasty = 0;
double x, y;

//Datei für Torwart-Abweichung
fstream TW("Torwart.txt", ios::out);


int TorwartAbweichung;

int exitCode = 0;


int open_port(const char *port) {
	struct ifreq ifr;
	struct sockaddr_can addr;

	/* open socket */
	soc = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (soc < 0)
		return -1;

	addr.can_family = AF_CAN;
	strcpy(ifr.ifr_name, port);
	if (ioctl(soc, SIOCGIFINDEX, &ifr) < 0)
		return (-1);
	addr.can_ifindex = ifr.ifr_ifindex;
	fcntl(soc, F_SETFL, O_NONBLOCK);
	if (bind(soc, (struct sockaddr *) &addr, sizeof(addr)) < 0)
		return -1;

	return 0;
}

int send_port(struct can_frame *frame) {
	int retval = write(soc, frame, sizeof(struct can_frame));
	if (retval != sizeof(struct can_frame))
		return -1;
	return 0;
}

void read_port() {
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
}

int close_port() {
	close(soc);
	return 0;
}

void frame_init(int ID, int DLC, int Data_0, int Data_1, int Data_2, int Data_3, int Data_4, int Data_5, int Data_6, int Data_7) {
	open_port("can0");
	//printf("open: %d\n", ret);
	struct can_frame frame;
	frame.can_id = ID; //  COB ID 200 für RxPDO1 + Can ID 1
	frame.can_dlc = DLC; // Datenanzahl
	frame.data[0] = Data_0; // Daten
	frame.data[1] = Data_1; //Daten
	frame.data[2] = Data_2; //..
	frame.data[3] = Data_3;
	frame.data[4] = Data_4;
	frame.data[5] = Data_5;
	frame.data[6] = Data_6;
	frame.data[7] = Data_7;
	send_port(&frame);
	//printf("sent: %d\n", ret);
	close_port();
}

void driver_init() {

	cout << "Reseten" << endl;
	frame_init(0x601, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); // Reset Command
	frame_init(0x602, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); // Reset Command
	frame_init(0x603, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); // Reset Command
	sleep(20);
	cout << "Operational" << endl;
	frame_init(0x00, 0x2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(2);
	cout << "ready to switch on" << endl;
	frame_init(0x201, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x202, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x203, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(2);
	cout << "switch on" << endl;
	frame_init(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x202, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x203, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
	sleep(2);
	cout << "homen: " << endl;
	frame_init(0x201, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x202, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);// Homen Command an RXPD0 1
	frame_init(0x203, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);// Homen Command an RXPD0 1
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
	sleep(25);
	cout << "homed" << endl;
	frame_init(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x202, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x203, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

}

int pixel_to_driverin(int Pixel) {
	if (Pixel <= 160) {
		return 10 * 5;
	} else if (Pixel >= 252) {
		return 10 * 160;
	} else {
		return 10 * (((Pixel - 160) * 1.75) + 5); // 1 Pixel entspricht 1,807 Millimeter 5mm Offset bei 169 haben wir 5mm
	}
}

void sent_position_to_driver1(int driverin) {
	cout << "sent_position_to_driver1"<< endl;
	//  An den Nibble denken!
	nibble = !nibble;
	int UpperPos = (driverin >> 8); //The lower 8 bits slide out
	//printf("Upper Pos :%i\n", UpperPos);
	int LowerPos = (driverin & 255); // Let the upper 8 bits disappear
	//printf("Lower Pos : %i\n", LowerPos);
	// Sende an RXPD0 1 = 0x201( Addresse/ ID), 0x8 = Datenbits, 0x3F 0x00 Controlword, 0x09 Nibble word that transmits the command,
	//LowerPos the lower 8 bits of the target position, UpperPos the upper 8 bits of the target position , 0xBB 0x08 Max. speed
	frame_init(0x201, 0x8, 0x3F, 0x00, nibble, 0x09, LowerPos, UpperPos, 0xBB,
			0x08);
	// Send to RXPDO 2 the rest of the command
	// 0x301 the address of RXPDO 2 ,0x8 = Number of data bits
	// 0x2c 0x01 acceleration, 0x2c 0x01 braking
	frame_init(0x301, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	// Now the sync message to run the command
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
	return;
}

void sent_position_to_driver2(int driverin) {
	cout << "sent_position_to_driver2"<< endl;
	//  An den Nibble denken!
	nibble = !nibble;
	int UpperPos = (driverin >> 8); // Die unteren 8 Bit rausschieben
	//printf("Upper Pos :%i\n", UpperPos);
	int LowerPos = (driverin & 255); // Die Oberen 8 Bit verschwinden lassen
	//printf("Lower Pos : %i\n", LowerPos);
	// Sende an RXPD0 1 = 0x201( Addresse/ ID), 0x8 = Datenbits, 0x3F 0x00 Controlword, 0x09 nibble Wort das den Befehl überträgt,/ Ball Tracking testen
	//LowerPos die unteren 8 Bit der Zielposition, UpperPos die oberen 8 Bit der Zielposition , 0xBB 0x08 Max Geschwindigkeit
	frame_init(0x201, 0x8, 0x3F, 0x00, nibble, 0x09, LowerPos, UpperPos, 0xFF,
			0x00);
	// Sende an RXPDO 2 den Rest des Befehls
	// 0x301 die Adresse von RXPDO 2 ,0x8 = Anzahl Datenbits
	// 0x2c 0x01 Beschleunigung, 0x2c 0x01 Abbremsen
	frame_init(0x301, 0x8, 0xAC, 0x00, 0xAC, 0x00, 0x00, 0x00, 0x00, 0x00);
	// Jetzt noch die Sync Message damit der Befehl ausgeführt wird.
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
	return;
}



void motor_by_hand1() {
	int position, pos1, pos2;
	cout << "Enter the position and confirm with enter" << endl;

	cin >> position;
	position *= 10;

	pos1 = (position & 255);
	pos2 = (position >> 8);

	nibble = !(nibble);
	cout << "nibble: " << nibble << endl;
	// FRAME_INIT Can_ID, DLC , Data, Data, Data, Data, Data, Data, Data, Data,
	// Nibble has to change every new COmmand, therefore nibble =! nibble
	// Position wird mit zwei HexDaten Übertragen deswegen Pos1 pos2. pos 1 sind die unteren 8 Bit
	// 50 mm entspricht dann 500 im Datenwort als Hex-Zahl
	// Die letzten beiden Datenworte im 0x201 Frame sind für die maximale Geschwindigkeit
	frame_init(0x201, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0xBB, 0x08); // RXPDO 1
	// Dieser Frame gehört noch zum Got To Pos Command und wird an RXPDO 2 geschickt deswegen 0x301
	// The data words 0 and 1 are here for the acceleration 100 in Dec corresponds to an acceleration of 10 m / s²
	//The next two data words are for braking the scale is exactly like accelerating
	frame_init(0x301, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

	nibble = !(nibble);
	cout << "nibble: " << nibble << endl;
	frame_init(0x201, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0xBB, 0x08); // RXPDO 1
	frame_init(0x301, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync


}

void motor_by_hand2() {
	int position, pos1, pos2;
	cout << "Enter the position and confirm with enter" << endl;

	cin >> position;
	position *= 10;

	pos1 = (position & 255);
	pos2 = (position >> 8);

	nibble = !(nibble);
	cout << "nibble: " << nibble << endl;
	// FRAME_INIT Can_ID, DLC , Data, Data, Data, Data, Data, Data, Data, Data,
	// Nibble has to change every new COmmand, therefore nibble =! nibble
	// Position is transferred with two hex data, therefore pos1 pos2. Pos 1 are the lower 8 bits
	// 50 mm then corresponds to 500 in the data word as a hex number
	// The last two data words in the 0x201 frame are for the maximum speed
	frame_init(0x202, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0xFF, 0xFF); // RXPDO 1
	// This frame still belongs to the Got To Pos Command and is sent to RXPDO 2 therefore 0x301
	// The data words 0 and 1 are here for the acceleration 100 in Dec corresponds to an acceleration of 10 m / s²
		//The next two data words are for braking the scale is exactly like accelerating
	frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

	nibble = !(nibble);
	cout << "nibble: " << nibble << endl;
	frame_init(0x202, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0xFF, 0xFF); // RXPDO 1
	frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
}

void motor_by_hand3() {
	int position, pos1, pos2;
	cout << "Enter the position and confirm with enter" << endl;

	cin >> position;
	position *= 10;

	pos1 = (position & 255);
	pos2 = (position >> 8);

	nibble = !(nibble);
	cout << "nibble: " << nibble << endl;
	// FRAME_INIT Can_ID, DLC , Data, Data, Data, Data, Data, Data, Data, Data,
	// Nibble has to change every new COmmand, therefore nibble =! nibble
	// Position is transferred with two hex data, therefore pos1 pos2. Pos 1 are the lower 8 bits
	// 50 mm then corresponds to 500 in the data word as a hex number
	// The last two data words in the 0x201 frame are for the maximum speed
	frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0xE8, 0x00); // RXPDO 1
	// This frame still belongs to the Got To Pos Command and is sent to RXPDO 2 therefore 0x301
	// The data words 0 and 1 are here for the acceleration 100 in Dec corresponds to an acceleration of 10 m / s²
		//The next two data words are for braking the scale is exactly like accelerating
	frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

	nibble = !(nibble);
	cout << "nibble: " << nibble << endl;
	frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0xE8, 0x00); // RXPDO 1
	frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

	nibble = !(nibble);
}

void homing1(){
	cout << "Homing" << endl;
	frame_init(0x201, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00); // Homen Command an RXPD0 1
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00); // Sync
	sleep(20);
	cout << "Homed" << endl;
}

void homing2(){
	cout << "Homing" << endl;
	frame_init(0x202, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00); // Homen Command an RXPD0 1
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00); // Sync
	sleep(20);
	cout << "Homed" << endl;
}

void homing3(){
	cout << "Homing" << endl;
	frame_init(0x203, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00); // Homen Command an RXPD0 1
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00); // Sync
	sleep(2);
	cout << "Homed" << endl;
}


void motor_switchon1() {
	int i = 0;

	cout << "What would you like to do?" << endl;
	cout << "1) Locking" << endl;
	cout << "2) Unlocking" << endl;
	cin >> i;

	switch (i) {
	case 1:
		frame_init(0x201, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		break;
	case 2:
		frame_init(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
		break;
	default:
		cout << "Try typing again!" << endl;
		break;
	}
	return;
}

void motor_switchon2() {
	int i = 0;

	cout << "What would you like to do?" << endl;
	cout << "1) Locking" << endl;
	cout << "2) Unlocking" << endl;
	cin >> i;

	switch (i) {
	case 1:
		frame_init(0x202, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		break;
	case 2:
		frame_init(0x202, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
		break;
	default:
		cout << "Try typing again!" << endl;
		break;
	}
	return;
}

void motor_switchon3() {
	int i = 0;

	cout << "What would you like to do?" << endl;
	cout << "1) Locking" << endl;
	cout << "2) Unlocking" << endl;
	cin >> i;

	switch (i) {
	case 1:
		frame_init(0x203, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		break;
	case 2:
		frame_init(0x203, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
		break;
	default:
		cout << "Try typing again!" << endl;
		break;
	}
	return;
}

void linear_movement(int positionL){
	int pos3,pos4;

	positionL *= 10;
	pos3 = (positionL & 255);
	pos4 = (positionL >> 8);

	nibble2 = !(nibble2);
	cout << "nibble2: " << nibble2 << endl;
	frame_init(0x202, 0x8, 0x3F, 0x00, nibble2, 0x09, pos3, pos4, 0x50, 0x10); //moving to 15.0 cm (linear)
	frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);//Sync

	nibble2 = !(nibble2);
	cout << "nibble2: " << nibble2 << endl;
	frame_init(0x202, 0x8, 0x3F, 0x00, nibble2, 0x09, pos3, pos4, 0x50, 0x10); //moving to 15.0 cm (linear)
	frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);//Sync

}

void shooting_move(int positionS){

	int pos5,pos6;

	positionS *= 10;
	pos5 = (positionS & 255);
	pos6 = (positionS >> 8);

	nibble = !(nibble);
	cout << "nibble: " << nibble << endl;
	frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos5, pos6, 0xFF, 0xFF); //moving to 1.0 cm (rotary)(Shot)
	frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

	nibble = !(nibble);
	cout << "nibble: " << nibble << endl;
	frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos5, pos6, 0xFF, 0xFF); //moving to 1.0 cm (rotary)(Shot)
	frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

}

void rotation(int positionR){
	int pos1,pos2;

	positionR *= 10;
	pos1 = (positionR & 255);
	pos2 = (positionR >> 8);

	nibble = !(nibble);
	cout << "nibble: " << nibble << endl;
	frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0x50, 0x10); //rotary movement
	frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

	nibble = !(nibble);
	cout << "nibble: " << nibble << endl;
	frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0x50, 0x10); //rotary movement
	frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync


}


void shot2(){

	rotation(-10);
	linear_movement(25);
	usleep(200000);//This command make the program wait a few milisecond

	shooting_move(10);
	usleep(200000);

	linear_movement(150);
	rotation(0);

	nibble = !(nibble);
}



void routine_motor_2_3(){
	int position2, position1, pos1, pos2, pos11, pos22;
	/*This function is the first routine for the linear and rotary motor.
	 *this subprogram is a function to move the linear part and the rotary part
	 work together */
		cout << "Enter the linear position and confirm with enter" << endl;
		cin >> position1;
		cout << "Enter the rotary position and confirm with enter" << endl;
		cin >> position2;
//linear part
		position1 *= 10;

		pos1 = (position1 & 255);
		pos2 = (position1 >> 8);

//rotary part
		position2 *= 10;

		pos11 = (position2 & 255);
		pos22 = (position2 >> 8);

		nibble = !(nibble);
		cout << "nibble: " << nibble << endl;
		frame_init(0x202, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0x50, 0x00); // moving to the linear position
		frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

		frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos11, pos22, 0x50, 0x00); // moving to the rotary position
		frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

		nibble = !(nibble);
		cout << "nibble: " << nibble << endl;
		frame_init(0x202, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0x50, 0x00); /*moving to the linear position
		(we have to double the command to make sure that the command is sent)*/
		frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

		frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos11, pos22, 0x50, 0x00); /*moving to the rotary position
		(we have to double the command to make sure that the command is sent)*/
		frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

		sleep(2);

}
void routine_second_motor_2_3(){//this function is a routine to make the rotary and the linear part of the motor move together
	int y, position2, position1,position3,position4, pos1, pos2, pos3, pos4, pos11, pos22, pos33, pos44;
		/*you can choose the position of each part.
		you choose the first position and second position of each part and according to this
		the motor will move from the first position to the second then from the second to the first*/
		cout << "Enter the linear position1 and confirm with enter" << endl;
		cin >> position1;
		cout << "Enter the rotary position1 and confirm with enter" << endl;
		cin >> position2;
		cout << "Enter the linear position2 and confirm with enter" << endl;
		cin >> position3;
		cout << "Enter the rotary position2 and confirm with enter" << endl;
		cin >> position4;
		//linear part
		position1 *= 10;
		position3 *= 10;
		//rotary part
		position2 *= 10;
		position4 *= 10;
		pos1 = (position1 & 255);
		pos2 = (position1 >> 8);
		pos3 = (position3 & 255);
		pos4 = (position3 >> 8);
		pos11 = (position2 & 255);
		pos22 = (position2 >> 8);
		pos33 = (position4 & 255);
		pos44 = (position4 >> 8);
		do{//this is a while loop
		y=1;//the loop will keep going if the value is superior to 0
		nibble = !(nibble);
		cout << "nibble: " << nibble << endl;
		frame_init(0x202, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0x50, 0x00); // moving to the first linear position
		frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

		frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos11, pos22, 0x50, 0x00); // moving to the first rotary position
		frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

		nibble = !(nibble);
		cout << "nibble: " << nibble << endl;
		frame_init(0x202, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0x50, 0x00); /*moving to the first linear position
		(we have to double the FIRST command to make sure that the FIRST command is sent)*/
		frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

		frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos11, pos22, 0x50, 0x00);  /*moving to the first rotary position
		(we have to double the FIRST command to make sure that the FIRST command is sent)*/
		frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

		sleep(2);//the system wait 2 seconds

		nibble = !(nibble);
		cout << "nibble: " << nibble << endl;
		frame_init(0x202, 0x8, 0x3F, 0x00, nibble, 0x09, pos3, pos4, 0x50, 0x00); // moving to the second linear position
		frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);// Sync

		frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos33, pos44, 0x50, 0x00); // moving to the second rotary position
		frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
		frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
		sleep(2);

		cout << "Do you want to stop ?"<< endl;
		cin >>y;//you choose the value of y and if it's inferior to 0 the loop ends
		}
		while(y>0);
}


void shot(){// this function is a routine to shoot
	int nibble2, position2, position1,position3,position4,position5, pos1, pos2, pos3, pos4, pos11, pos22, pos33, pos44,pos444,pos333;

	//linear part position
				position1 = 25;//position to move the dummies 2.5 cm to the right side
				position3 = 150;//position that we want at the end of the movement here it's the home position
	//rotary part position
				position2 = 10;// position to ready up the shot (backing up)
				position4 = -10;// position to shot onward
				position5 = 0;// position of reset
	// the following lines are there to make the asking positions able to be read
				position1 *= 10;
				position3 *= 10;
				position2 *= 10;
				position4 *= 10;
				position5 *= 10;
				//position1
				pos1 = (position1 & 255);
				pos2 = (position1 >> 8);
				//position3 (position3 because it activates in the third)
				pos3 = (position3 & 255);
				pos4 = (position3 >> 8);
				//position2
				pos11 = (position2 & 255);
				pos22 = (position2 >> 8);
				//position4
				pos33 = (position4 & 255);
				pos44 = (position4 >> 8);
				//position5
				pos333 = (position5 & 255);
				pos444 = (position5 >> 8);

				nibble2 = 1;
				nibble = !(nibble);
				cout << "nibble: " << nibble << endl;
				frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos11, pos22, 0x50, 0x10); //moving to -1.0 cm (rotary)
				frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

				nibble2 = !(nibble2);
				cout << "nibble2: "<< nibble2 << endl;
				frame_init(0x202, 0x8, 0x3F, 0x00, nibble2, 0x09, pos1, pos2, 0x50, 0x10); //moving to 2.5 cm (linear)
				frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

				nibble = !(nibble);
				cout << "nibble: " << nibble << endl;
				frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos11, pos22, 0xFF, 0xFF); /*moving to -1.0 cm (rotary).
				We had to double it because of the nibble we had to make sure it respond every time*/
				frame_init(0x303, 0x8, 0xFF, 0xFF, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

				nibble2 = !(nibble2);
				cout << "nibble2: "<< nibble2 << endl;
				frame_init(0x202, 0x8, 0x3F, 0x00, nibble2, 0x09, pos1, pos2, 0x50, 0x10); /*moving to 2.5 cm (linear).
				We had to double it because of the nibble we had to make sure it respond every time*/
				frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
				usleep(200000);//This command make the program wait a few milisecond

				nibble = !(nibble);
				cout << "nibble: " << nibble << endl;
				frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos33, pos44, 0xFF, 0x10); //moving to 1.0 cm (rotary)(Shot)
				frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
				usleep(200000);

				nibble2 = !(nibble2);
				cout << "nibble2: "<< nibble2 << endl;
				frame_init(0x202, 0x8, 0x3F, 0x00, nibble2, 0x09, pos3, pos4, 0x50, 0x10); //moving to 15.0 cm (linear)
				frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);//Sync

				nibble = !(nibble);
				cout << "nibble: " << nibble << endl;
				frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos333, pos444, 0x50, 0x10); //moving to 0.0 cm, homing position (rotary)
				frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync


}




void trickshot_around_theball(){
	int nibble2, position2, position1,position3,position4,position5,position6,position7,position8,position9,position10,
	pos1,pos12,pos2,pos22,pos3,pos32,pos4,pos42,pos5,pos52,pos6,pos62,pos7,pos72,pos8,pos82,pos9,pos92,pos10,pos102;

	//linear part's position
				position1 = 130;//position to move the dummies 2.5 cm to the right side
				position3 = 150;//position that we want at the end of the movement here it's the home position
				position6 = 100;//position to slide pass the ball
				position7 = 150;//position to slide pass the ball in the other way
				position8 = 130;//position to go back to the right side and ready up the shot
	//rotary part's position
				position2 = 10;// position to go behind the ball (backing up)
				position4 = -10;//turn forward
				position9 = 10;//turn back
				position10 = -10;// position to shot onward
				position5 = 0;// position of reset
	// the following lines are there to make the asking positions able to be read
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
				//position1
				pos1 = (position1 & 255);
				pos12 = (position1 >> 8);
				//position3 (position3 because it activates in the third)
				pos3 = (position3 & 255);
				pos32 = (position3 >> 8);
				//position2
				pos2 = (position2 & 255);
				pos22 = (position2 >> 8);
				//position4
				pos4 = (position4 & 255);
				pos42 = (position4 >> 8);
				//position5
				pos5 = (position5 & 255);
				pos52 = (position5 >> 8);
				//position6
				pos6 = (position6 & 255);
				pos62 = (position6 >> 8);
				//position7
				pos7 = (position7 & 255);
				pos72 = (position7 >> 8);
				//position8
				pos8 = (position8 & 255);
				pos82 = (position8 >> 8);
				//position9
				pos9 = (position9 & 255);
				pos92 = (position9 >> 8);
				//position10
				pos10 = (position10 & 255);
				pos102 = (position10 >> 8);

				nibble2 = 1;

				nibble = !(nibble);
				cout << "nibble: " << nibble << endl;
				frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos2, pos22, 0x50, 0x00); //moving to 1.0 cm (rotary)
				frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

				nibble2 = !(nibble2);
				cout << "nibble2: "<< nibble2 << endl;
				frame_init(0x202, 0x8, 0x3F, 0x00, nibble2, 0x09, pos1, pos12, 0x50, 0x00); //moving to 2.5 cm (linear)
				frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

				nibble = !(nibble);
				cout << "nibble: " << nibble << endl;
				frame_init(0x203, 0x8, 0x3F, 0x00, nibble, 0x09, pos2, pos22, 0x50, 0x00); //moving to 1.0 cm (rotary). We had to double it because of the nibble we had to make sure it respond every time
				frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

				nibble2 = !(nibble2);
				cout << "nibble2: "<< nibble2 << endl;
				frame_init(0x202, 0x8, 0x3F, 0x00, nibble2, 0x09, pos1, pos12, 0x50, 0x00); //moving to 2.5 cm (linear). We had to double it because of the nibble we had to make sure it respond every time
				frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
				sleep(2);//This command make the program wait a few milisecond

				nibble = !(nibble);
				cout << "nibble: " << nibble << endl;
				frame_init(0x202, 0x8, 0x3F, 0x00, nibble, 0x09, pos6, pos62, 0x50, 0x00); //moving to 1.0 cm (linear)
				frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

				nibble2 = !(nibble2);
				cout << "nibble2: " << nibble2 << endl;
				frame_init(0x203, 0x8, 0x3F, 0x00, nibble2, 0x09, pos4, pos42, 0x50, 0x00); //moving to -1.0 cm (rotary)
				frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
				sleep(2);//This command make the program wait a few milisecond

				nibble = !(nibble);
				cout << "nibble: " << nibble << endl;
				frame_init(0x202, 0x8, 0x3F, 0x00, nibble, 0x09, pos7, pos72, 0x50, 0x00); //moving to 4.0 cm (linear)
				frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

				nibble2 = !(nibble2);
				cout << "nibble2: " << nibble2 << endl;
				frame_init(0x203, 0x8, 0x3F, 0x00, nibble2, 0x09, pos9, pos92, 0x50, 0x00); //moving to 1.0 cm (rotary)
				frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
				sleep(2);//This command make the program wait a few milisecond

				nibble = !(nibble);
				cout << "nibble: "<< nibble << endl;
				frame_init(0x202, 0x8, 0x3F, 0x00, nibble, 0x09, pos8, pos82, 0x50, 0x00); //moving to 2.5 cm (linear).
				frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
				sleep(2);

				nibble2 = !(nibble2);
				cout << "nibble2: " << nibble2 << endl;
				frame_init(0x203, 0x8, 0x3F, 0x00, nibble2, 0x09, pos10, pos102, 0x50, 0x00); //moving to -1.0 cm (rotary)(Shot)
				frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
				sleep(2);

				nibble = !(nibble);
				cout << "nibble: "<< nibble << endl;
				frame_init(0x202, 0x8, 0x3F, 0x00, nibble, 0x09, pos3, pos32, 0x50, 0x00); //moving to 15.0 cm (linear)
				frame_init(0x302, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);//Sync

				nibble2 = !(nibble2);
				cout << "nibble2: " << nibble2 << endl;
				frame_init(0x203, 0x8, 0x3F, 0x00, nibble2, 0x09, pos5, pos52, 0x50, 0x00); //moving to 0.0 cm, homing position (rotary)
				frame_init(0x303, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync

				nibble = !(nibble);

}

void Menue() {
	int i = 0;
	while (1) {
		cout << "Herzlich Willkommen!" << endl;
		cout << "Was moechten Sie machen:" << endl;
		cout << "1) Motor Initialisieren" << endl;
		cout << "2) Spielen" << endl;
		cout << "3) Set position motor 1" << endl;
		cout << "4) Set position motor 2" << endl;
		cout << "5) Set position motor 3" << endl;
		cout << "6) Homimg motor 1" << endl;
		cout << "7) Homimg motor 2" << endl;
		cout << "8) Homimg motor 3" << endl;
		cout << "9) Motor 1 switch on" << endl;
		cout << "10) Motor 2 switch on" << endl;
		cout << "11) Motor 3 switch on" << endl;
		cout << "12) Routine motor 2 and 3" << endl;
		cout << "13) Routine2 motor 2 and 3" << endl;
		cout << "14) shot" << endl;
		cout << "15) shot2.0" << endl;
		cout << "16) shot around ball shot" << endl;
		cout << "17) End" << endl;
		cin >> i;
		switch (i) {
		case 1:
			driver_init();
			break;
		case 2:
			//traction_and_motor();
			break;
		case 3:
			motor_by_hand1();
			break;
		case 4:
			motor_by_hand2();
			break;
		case 5:
			motor_by_hand3();
			break;
		case 6:
			homing1();
			break;
		case 7:
			homing2();
			break;
		case 8:
			homing3();
			break;
		case 9:
			motor_switchon1();
			break;
		case 10:
			motor_switchon2();
			break;
		case 11:
			motor_switchon3();
			break;
		case 12:
			routine_motor_2_3();
			break;
		case 13:
			routine_second_motor_2_3();
			break;
		case 14:
			shot();
			break;
		case 15:
			shot2();
			break;
		case 16:
			trickshot_around_theball();
			break;
		case 17:
			cout << "Program finished" << endl << endl;
			return;
		default:
			cout << "Try typing again!" << endl;
			break;

		}

	}
}

int main(int argc, char** argv) {

	Menue();

}

