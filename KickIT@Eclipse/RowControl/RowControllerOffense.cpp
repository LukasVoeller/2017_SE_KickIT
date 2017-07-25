#include "RowControllerOffense.hpp"
#include "MotorCommunicatorImpl.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerOffense::RowControllerOffense() {
	mcomm = new MotorCommunicatorImpl(OFFENSE);
}

void RowControllerOffense::run() {

}
