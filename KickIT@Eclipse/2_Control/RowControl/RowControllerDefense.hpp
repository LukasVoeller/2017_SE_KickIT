/**
 * @file RowControllerDefense.hpp
 * @brief
 */
#ifndef ROWCONTROL_ROWCONTROLLERDEFENSE_HPP_
#define ROWCONTROL_ROWCONTROLLERDEFENSE_HPP_

#include "_RowControllerInterface.hpp"

/**RowControllerDefense class
 *
 */
class RowControllerDefense: public RowControllerInterface {

public:
	/**RowControllerDefense constructor
	 *
	 */
	RowControllerDefense();

	void kick(int strength);
	virtual void up();
	virtual void down();
	void moveTo(float y);

protected:
	/**kickThread function
	 *
	 */
	void kickThread();
};

#endif /* ROWCONTROL_ROWCONTROLLERDEFENSE_HPP_ */
