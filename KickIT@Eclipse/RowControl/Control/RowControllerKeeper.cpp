#include "../Control/RowControllerKeeper.hpp"

#include "../Communication/MotorComPS01Impl.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerKeeper::RowControllerKeeper() {
	mcomm = new MotorComPS01Impl(KEEPER);
}
