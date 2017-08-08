#include <iostream>
#include <stdio.h>

#include <unistd.h>		//For write in sendPort
#include "MotorComRS01Impl.hpp"

using namespace std;

MotorComRS01Impl::MotorComRS01Impl(Row r) {
	this->socketId = 0;
	this->nibble = 1;

	this->port = "can0";
	this->row = r;
	this->motorAddress1 = 0x202;
	this->motorAddress2 = 0x302;

	if(!driversInitialized) driverInit();
}


void MotorComRS01Impl::kick() {
	//TODO
}


void MotorComRS01Impl::homing() {

	cout << "homing() is not supported" << endl;
}
