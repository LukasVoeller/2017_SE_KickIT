#ifndef ROWCONTROL_ROWCONTROLLERKEEPER_HPP_
#define ROWCONTROL_ROWCONTROLLERKEEPER_HPP_
#include "InterfaceRowController.hpp"


class RowControllerKeeper : public InterfaceRowController{

public:
	RowControllerKeeper();
	void run(){};
};

#endif /* ROWCONTROL_ROWCONTROLLERKEEPER_HPP_ */
