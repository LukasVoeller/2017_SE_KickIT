#include "../Communication/MotorComRS01Impl.hpp"
#include "RowControllerDefense.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerDefense::RowControllerDefense() {
	mcomm = new MotorComRS01Impl(DEFENSE);
}

void RowControllerDefense::run() {

}
