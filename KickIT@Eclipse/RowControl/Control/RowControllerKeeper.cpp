#include "../Communication/MotorComPS01Impl.hpp"
#include "RowControllerKeeper.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerKeeper::RowControllerKeeper() {
	mcomm = new MotorComPS01Impl(KEEPER);
}

void RowControllerKeeper::run() {

}
