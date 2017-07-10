/*
 * RowControllerDefense.cpp
 *
 *  Created on: 18.05.2017
 *      Author: student
 */

#include "RowControllerDefense.hpp"
#include "../DataType/RowEnum.hpp"
#include "MotorCommunicatorImpl.hpp"

RowControllerDefense::RowControllerDefense(){
	mcomm = new MotorCommunicatorImpl(KEEPER);
}
