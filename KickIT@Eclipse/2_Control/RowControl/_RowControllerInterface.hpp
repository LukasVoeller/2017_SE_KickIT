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
	/**moveTo function
	 *
	 * @param float y as the position on the table at which you need a player.
	 */
	virtual void moveTo(float y) = 0;

	/**up function
	 *
	 * Function to set the row to horizontal position.
	 */
	virtual void up() {}

	/**down function
	 *
	 * Function to set the row back to vertical position.
	 */
	virtual void down() {}

	/**kick function
	 *
	 * @param int strength
	 */
	virtual void kick(int strength) {}

	/**RowControllerInterface destructor
	 *
	 */
	virtual ~RowControllerInterface() {}

protected:
	MotorCommunicatorInterface* mcomm;
	TableConfig tc;
	bool isUp = false;
	bool isShooting = false;
};

#endif //INTERFACEROWCONTROLLER_HPP
