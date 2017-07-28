#include <RowControl/MotorCom_Impl_PS01.hpp>
#include "RowControllerOffense.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerOffense::RowControllerOffense() {
	mcomm = new MotorCommunicatorImpl(OFFENSE);
}

void RowControllerOffense::run() {

}
