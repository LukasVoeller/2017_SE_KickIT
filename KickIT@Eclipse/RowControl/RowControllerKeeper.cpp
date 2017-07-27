#include <RowControl/MotorCom_Impl_PS01.hpp>
#include "RowControllerKeeper.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerKeeper::RowControllerKeeper() {
	mcomm = new MotorCommunicatorImpl(KEEPER);
}

void RowControllerKeeper::run() {

}
