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
extern bool keeperHomed;

MotorComPS01Impl::MotorComPS01Impl() {
	this->socketId = 0;
	this->port = "can0";
	if(mc.homingRequired){
		thread c(&MotorComPS01Impl::driverInit, this);
		c.detach();
	}
}

void MotorComPS01Impl::driverInit() {
	sleep(1);
	cout << "(1/6) Reset PS01:" << endl;
	frameInit(0x601, 0x8, 0x23, 0x0, 0x20, 0xB, 0x0, 0x0, 0x0, 0x0);
	sleep(this->mc.keeperSleepAfterReset);

	cout << "(2/6) Operational PS01:" << endl;
	frameInit(0x0, 0x2, 0x01, 0x0, this->switchedNibbleT(), 0x0, 0x0, 0x0, 0x0, 0x0);
	sleep(2);

	cout << "(3/6) Ready to switch on PS01:" << endl;
	frameInit(0x201, 0x8, 0x3E, 0x0, this->switchedNibbleT(), 0x0, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);
	sleep(2);

	cout << "(4/6) Switching on PS01:" << endl;
	frameInit(0x201, 0x8, 0x3F, 0x0, this->switchedNibbleT(), 0x0, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);
	sleep(2);

	cout << "(5/6) Homing PS01:" << endl;
	frameInit(0x201, 0x8, 0x3F, 0x08, this->switchedNibbleT(), 0x0, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);
	sleep(this->mc.keeperSleepAfterHoming);

	cout << "(6/6) Homed PS01:" << endl;
	frameInit(0x201, 0x8, 0x3F, 0x0, this->switchedNibbleT(), 0x0, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);

	keeperHomed = true;
}

void MotorComPS01Impl::linearMovement(int position){
	if(position > mc.keeperBoundaryInwards) position = mc.keeperBoundaryInwards;	//Check if position is within range
	if(position < mc.keeperBoundaryOutwards) position = mc.keeperBoundaryOutwards;	//Check if position is within range

	int pLow, pHigh;
	position *= 10;
	pLow = (position & 255);
	pHigh = (position >> 8);

	int acceleration = this->mc.keeperAccelerationTranslational;
	int aLow = acceleration & 255;
	int aHigh = acceleration >> 8;

	int deceleration = this->mc.keeperDecelerationTranslational;
	int dLow = deceleration & 255;
	int dHigh = deceleration >> 8;

	int maxSpeed = this->mc.keeperSpeedTranslational;
	int sLow = maxSpeed & 255;
	int sHigh = maxSpeed >> 8;

	frameInit(0x201, 0x8, 0x3F, 0x0, this->switchedNibbleT(), 0x09, pLow, pHigh, sLow, sHigh);
	frameInit(0x301, 0x8, aLow, aHigh, dLow, dHigh, 0x0, 0x0, 0x0, 0x0);
	frameInit(0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0);
}
