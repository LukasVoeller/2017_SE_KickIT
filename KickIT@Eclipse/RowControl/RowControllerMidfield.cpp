#include "RowControllerMidfield.hpp"
#include "MotorCommunicatorImpl.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerMidfield::RowControllerMidfield(){
	mcomm = new MotorCommunicatorImpl(MIDFIELD);
}
