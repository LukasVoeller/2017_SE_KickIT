#ifndef ROWCONTROL_ROWCONTROLLERKEEPER_HPP_
#define ROWCONTROL_ROWCONTROLLERKEEPER_HPP_
#include "../Interface/RowControllerInterface.hpp"

class RowControllerKeeper: public RowControllerInterface {

public:
	RowControllerKeeper();
	void run();
};

#endif /* ROWCONTROL_ROWCONTROLLERKEEPER_HPP_ */
