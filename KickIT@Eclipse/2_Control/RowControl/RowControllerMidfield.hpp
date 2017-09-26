/**
 * @file RowControllerMidfield.hpp
 * @brief
 */
#ifndef ROWCONTROL_ROWCONTROLLERMIDFIELD_HPP_
#define ROWCONTROL_ROWCONTROLLERMIDFIELD_HPP_

#include "_RowControllerInterface.hpp"

/**RowControllerMidfield class
 *
 */
class RowControllerMidfield: public RowControllerInterface {

public:
	/**RowControllerMidfield constructor
	 *
	 */
	RowControllerMidfield();

	/**moveTo function
	 * @param float y
	 *
	 */
	void moveTo(float y){}
};

#endif /* ROWCONTROL_ROWCONTROLLERMIDFIELD_HPP_ */
