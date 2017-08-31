#include "../../2_Control/RowControl/RowControllerDefense.hpp"

#include <thread>
#include <unistd.h>

#include "../../2_Control/MotorCommunication/MotorComRS01Impl.hpp"
#include "../../5_DataType/RowEnum.hpp"

RowControllerDefense::RowControllerDefense() {
	mcomm = new MotorComRS01Impl(DEFENSE);
}

void RowControllerDefense::up(){
	if(!this->isUp){
		mcomm->rotate(10);
		this->isUp = true;
	}
}

void RowControllerDefense::down(){
	if(this->isUp){
		mcomm->rotate(0);
		this->isUp = false;
	}
}

void RowControllerDefense::kick(int amount){
	if(this->isShooting) return;
	this->isShooting = true;
	std::thread c(&RowControllerDefense::kickThread, this);
	c.detach();
}

void RowControllerDefense::kickThread(){
	mcomm->rotate(-2);
	usleep(100000);
	mcomm->rotate(2);
	usleep(100000);
	mcomm->rotate(-2);
	usleep(100000);
	mcomm->rotate(2);
	usleep(100000);
	mcomm->rotate(0);

	this->isShooting = false;
}

void RowControllerDefense::moveTo(float y){
	if(y<=this->tc.tableHeight/2){
		mcomm->linearMovement( (int)(y-tc.offsetTopSideDefense) );
	} else if(y>this->tc.tableHeight/2){
		mcomm->linearMovement( (int)(y-tc.offsetTopSideDefense - tc.playerGapDefense) );
	}
}
