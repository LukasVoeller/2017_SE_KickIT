#include <RowControl/MotorCom_Impl_PS01.hpp>
#include "RowControllerDefense.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerDefense::RowControllerDefense() {
	mcomm = new MotorCommunicatorImpl(DEFENSE);
}

void RowControllerDefense::run() {

}
