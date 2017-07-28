#ifndef ROWCONTROL_ROWCONTROLLERDEFENSE_HPP_
#define ROWCONTROL_ROWCONTROLLERDEFENSE_HPP_

#include "../Interface/RowControllerInterface.hpp"

class RowControllerDefense: public RowControllerInterface {

public:
	RowControllerDefense();
	void run();
};

#endif /* ROWCONTROL_ROWCONTROLLERDEFENSE_HPP_ */
