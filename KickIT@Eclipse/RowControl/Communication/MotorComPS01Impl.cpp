#include <iostream>
#include <stdio.h>

#include <unistd.h>		//For write in sendPort
#include "MotorComPS01Impl.hpp"

using namespace std;

MotorComPS01Impl::MotorComPS01Impl(Row r) {
	this->socketId = 0;
	this->nibble = 1;

	this->port = "can0";
	this->row = r;
	this->motorAddress1 = 0x201;
	this->motorAddress2 = 0x301;

	if(!driversInitialized) driverInit();

}


void MotorComPS01Impl::kick() {
	//TODO
}



void MotorComPS01Impl::homing() {

	cout << "homing() is not supported" << endl;
}
