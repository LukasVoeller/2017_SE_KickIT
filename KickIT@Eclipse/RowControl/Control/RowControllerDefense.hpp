#ifndef ROWCONTROL_ROWCONTROLLERDEFENSE_HPP_
#define ROWCONTROL_ROWCONTROLLERDEFENSE_HPP_

#include "../Interface/RowControllerInterface.hpp"

class RowControllerDefense: public RowControllerInterface {

public:
	RowControllerDefense();
	void kick(int strength); //Parameter Deklaration != Parameter Implementation
	virtual void up();
	virtual void down();
	void moveTo(float y);

protected:
	void kickThread();
};

#endif /* ROWCONTROL_ROWCONTROLLERDEFENSE_HPP_ */
