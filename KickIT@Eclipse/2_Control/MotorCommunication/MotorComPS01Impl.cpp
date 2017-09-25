/**
 * @file MotorComPS01Impl.cpp
 * @brief
 */
#include "../../2_Control/MotorCommunication/MotorComPS01Impl.hpp"

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <thread>

using namespace std;

MotorComPS01Impl::MotorComPS01Impl(Row r) {
	this->socketId = 0;
	this->port = "can0";
	this->row = r;
	if(mc.homingRequired){
		thread c(&MotorComPS01Impl::driverInit, this);
		c.detach();
	}
}

void MotorComPS01Impl::driverInit() {
	sleep(1);
	cout << "(1/6) Reset PS01:" << endl;
	frameInit(0x601, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00);
	sleep(this->mc.keeperSleepAfterReset);

	cout << "(2/6) Operational PS01:" << endl;
	frameInit(0x00, 0x2, 0x01, 0x00, this->switchedNibbleT(), 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(2);

	cout << "(3/6) Ready to switch on PS01:" << endl;
	frameInit(0x201, 0x8, 0x3E, 0x00, this->switchedNibbleT(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(2);

	cout << "(4/6) Switching on PS01:" << endl;
	frameInit(0x201, 0x8, 0x3F, 0x00, this->switchedNibbleT(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(2);

	cout << "(5/6) Homing PS01:" << endl;
	frameInit(0x201, 0x8, 0x3F, 0x08, this->switchedNibbleT(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(this->mc.keeperSleepAfterHoming);

	cout << "(6/6) Homed PS01:" << endl;
	frameInit(0x201, 0x8, 0x3F, 0x00, this->switchedNibbleT(), 0x00, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}

void MotorComPS01Impl::linearMovement(int position){
	if(position > mc.keeperBoundaryInwards) position = mc.keeperBoundaryInwards;			//Check if position is within range
	if(position < mc.keeperBoundaryOutwards) position = mc.keeperBoundaryOutwards;			//Check if position is within range

	int pos1, pos2;
	position *= 10;
	pos1 = (position & 255);
	pos2 = (position >> 8);

	int acceleration = this->mc.keeperAccelerationTranslational;
	int aLow = acceleration & 255;
	int aHigh = acceleration >> 8;

	int deceleration = this->mc.keeperDecelerationTranslational;
	int dLow = deceleration & 255;
	int dHigh = deceleration >> 8;

	int maxSpeed = this->mc.keeperSpeedTranslational;
	int sLow = maxSpeed & 255;
	int sHigh = maxSpeed >> 8;

	frameInit(0x201, 0x8, 0x3F, 0x00, this->switchedNibbleT(), 0x09, pos1, pos2, sLow, sHigh);
	frameInit(0x301, 0x8, aLow, aHigh, dLow, dHigh, 0x00, 0x00, 0x00, 0x00);
	frameInit(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
}
