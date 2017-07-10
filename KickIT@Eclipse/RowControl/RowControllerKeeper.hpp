/*
 * RowControllerKeeper.hpp
 *
 *  Created on: 18.05.2017
 *      Author: student
 */

#ifndef ROWCONTROL_ROWCONTROLLERKEEPER_HPP_
#define ROWCONTROL_ROWCONTROLLERKEEPER_HPP_
#include "RowControllerInterface.hpp"


class RowControllerKeeper : public RowControllerInterface{
private:
	MotorCommunicatorInterface* mcomm;
public:
	RowControllerKeeper();
	void run(){};
};




#endif /* ROWCONTROL_ROWCONTROLLERKEEPER_HPP_ */
