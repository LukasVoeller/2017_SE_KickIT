#ifndef ROWCONTROL_ROWCONTROLLERMIDFIELD_HPP_
#define ROWCONTROL_ROWCONTROLLERMIDFIELD_HPP_

#include "../Interface/RowControllerInterface.hpp"

class RowControllerMidfield: public RowControllerInterface {

public:
	RowControllerMidfield();
	void moveTo(float y){}
};

#endif /* ROWCONTROL_ROWCONTROLLERMIDFIELD_HPP_ */
