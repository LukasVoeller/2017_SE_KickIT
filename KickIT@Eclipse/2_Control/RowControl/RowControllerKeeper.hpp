/**
 * @file RowControllerKeeper.hpp
 * @brief
 */
#ifndef ROWCONTROL_ROWCONTROLLERKEEPER_HPP_
#define ROWCONTROL_ROWCONTROLLERKEEPER_HPP_

#include "_RowControllerInterface.hpp"


/**RowControllerKeeper class
 *
 */
class RowControllerKeeper: public RowControllerInterface {

public:
	/**RowControllerKeeper constructor
	 *
	 */
	RowControllerKeeper();

	/**run function
	 *
	 */
	void run();

	/**moveTo function
	 *
	 */
	void moveTo(float y);

};

#endif /* ROWCONTROL_ROWCONTROLLERKEEPER_HPP_ */
