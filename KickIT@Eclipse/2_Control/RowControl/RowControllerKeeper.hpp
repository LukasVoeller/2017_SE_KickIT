#ifndef ROWCONTROL_ROWCONTROLLERKEEPER_HPP_
#define ROWCONTROL_ROWCONTROLLERKEEPER_HPP_

#include "_RowControllerInterface.hpp"


class RowControllerKeeper: public RowControllerInterface {

public:
	RowControllerKeeper();
	void run();
	void moveTo(float y);

};

#endif /* ROWCONTROL_ROWCONTROLLERKEEPER_HPP_ */
