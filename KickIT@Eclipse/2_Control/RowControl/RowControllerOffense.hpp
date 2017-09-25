/**
 * @file RowControllerOffense.hpp
 * @brief
 */
#ifndef ROWCONTROL_ROWCONTROLLEROFFENSE_HPP_
#define ROWCONTROL_ROWCONTROLLEROFFENSE_HPP_

#include "_RowControllerInterface.hpp"

/**RowControllerOffense class
 *
 */
class RowControllerOffense: public RowControllerInterface {

public:
	/**RowControllerOffense constructor
	 *
	 */
	RowControllerOffense();

	/**moveTo function
	 * @param float y
	 *
	 */
	void moveTo(float y){}
};

#endif /* ROWCONTROL_ROWCONTROLLEROFFENSE_HPP_ */
