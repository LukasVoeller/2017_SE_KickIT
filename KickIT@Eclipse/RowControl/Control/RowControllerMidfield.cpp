#include <RowControl/MotorCom_Impl_PS01.hpp>
#include "RowControllerMidfield.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerMidfield::RowControllerMidfield() {
	mcomm = new MotorCommunicatorImpl(MIDFIELD);
}

void RowControllerMidfield::run() {

}
