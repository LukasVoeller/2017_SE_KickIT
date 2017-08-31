#include "../../2_Control/RowControl/RowControllerKeeper.hpp"

#include "../../2_Control/MotorCommunication/MotorComPS01Impl.hpp"
#include "../MotorCommunication/MotorComPS01Impl.hpp"
#include "../../5_DataType/RowEnum.hpp"

RowControllerKeeper::RowControllerKeeper() {
	mcomm = new MotorComPS01Impl(KEEPER);
}

void RowControllerKeeper::moveTo(float y){
	y-=tc.tableHeight/2;
	this->mcomm->linearMovement((int)y);
}
