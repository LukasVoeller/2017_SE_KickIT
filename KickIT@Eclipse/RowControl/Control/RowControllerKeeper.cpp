#include <RowControl/MotorCom_Impl_PS01.hpp>
#include "RowControllerKeeper.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerKeeper::RowControllerKeeper() {
	mcomm = new MotorComPS01(KEEPER);
}

void RowControllerKeeper::run() {

}
