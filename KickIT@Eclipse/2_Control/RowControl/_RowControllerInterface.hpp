/**
 * @file RowControllerInterface
 * @brief
 */
#ifndef INTERFACEROWCONTROLLER_HPP
#define INTERFACEROWCONTROLLER_HPP

#include <cstdlib>

#include "../../5_DataType/TableConfig.hpp"
#include "../MotorCommunication/_MotorCommunicatorInterface.hpp"

/**RowControllerInterface class
 *
 */
class RowControllerInterface {

public:
	/**moveTo
	 * @param float y
	 */
	virtual void moveTo(float y) = 0;

	/**up function
	 *
	 */
	virtual void up() {}

	/**down function
	 *
	 */
	virtual void down() {}

	/**kick function
	 * @param int strength
	 */
	virtual void kick(int strength) {}

protected:
	MotorCommunicatorInterface* mcomm;

	bool isUp = false;
	bool isShooting = false;

	TableConfig tc;
};

#endif //INTERFACEROWCONTROLLER_HPP
