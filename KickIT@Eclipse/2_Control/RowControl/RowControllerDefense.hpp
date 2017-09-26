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

	/**kick function
	 * @param int strength
	 *
	 */
	void kick(int strength); //Parameter Deklaration != Parameter Implementation

	/**up function
	 *
	 */
	virtual void up();

	/**down function
	 *
	 */
	virtual void down();

	/**moveTo function
	 * @param float y
	 *
	 */
	void moveTo(float y);

protected:
	/**kickThread function
	 *
	 */
	void kickThread();
};

#endif //ROWCONTROL_ROWCONTROLLERDEFENSE_HPP_
