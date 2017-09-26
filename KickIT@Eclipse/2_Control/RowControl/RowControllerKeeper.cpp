/**
 * @file RowControllerKeeper.cpp
 * @brief
 */
#include "../../2_Control/RowControl/RowControllerKeeper.hpp"

#include "../../2_Control/MotorCommunication/MotorComPS01Impl.hpp"
#include "../MotorCommunication/MotorComPS01Impl.hpp"

RowControllerKeeper::RowControllerKeeper() {
	mcomm = new MotorComPS01Impl();
}

void RowControllerKeeper::moveTo(float y){
	y-=tc.tableHeight/2;
	this->mcomm->linearMovement((int)y);
}
