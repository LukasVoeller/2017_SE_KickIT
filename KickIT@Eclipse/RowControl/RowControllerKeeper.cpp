#include "RowControllerKeeper.hpp"
#include "MotorCommunicatorImpl.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerKeeper::RowControllerKeeper(){
	mcomm = new MotorCommunicatorImpl(KEEPER);
}
