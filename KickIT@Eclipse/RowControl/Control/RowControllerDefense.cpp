#include "../Control/RowControllerDefense.hpp"

#include "../Communication/MotorComRS01Impl.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerDefense::RowControllerDefense() {
	mcomm = new MotorComRS01Impl(DEFENSE);
}

void RowControllerDefense::run() {

}
