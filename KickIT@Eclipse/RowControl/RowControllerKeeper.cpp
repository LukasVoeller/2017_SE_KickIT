/*
 * RowControllerKeeper.cpp
 *
 *  Created on: 18.05.2017
 *      Author: student
 */

#include "RowControllerKeeper.hpp"
#include "MotorCommunicatorImpl.hpp"
#include "../DataType/RowEnum.hpp"

RowControllerKeeper::RowControllerKeeper(){
	mcomm = new MotorCommunicatorImpl(KEEPER);
}
