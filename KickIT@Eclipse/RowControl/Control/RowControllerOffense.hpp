#ifndef ROWCONTROL_ROWCONTROLLEROFFENSE_HPP_
#define ROWCONTROL_ROWCONTROLLEROFFENSE_HPP_

#include "../Interface/RowControllerInterface.hpp"

class RowControllerOffense: public RowControllerInterface {

public:
	RowControllerOffense();
	void moveTo(float y){}
};

#endif /* ROWCONTROL_ROWCONTROLLEROFFENSE_HPP_ */
