#include "../Control/RowControllerKeeper.hpp"
#include "../Communication/MotorComPS01Impl.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerKeeper::RowControllerKeeper() {
	mcomm = new MotorComPS01Impl(KEEPER);
}

void RowControllerKeeper::moveTo(float y){
	y-=tc.tableHeight/2;
	this->mcomm->linearMovement((int)y);
}
