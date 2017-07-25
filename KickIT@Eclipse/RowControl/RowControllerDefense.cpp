#include "RowControllerDefense.hpp"
#include "MotorCommunicatorImpl.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerDefense::RowControllerDefense() {
	mcomm = new MotorCommunicatorImpl(DEFENSE);
}

void RowControllerDefense::run() {

}
