/**
 * @file MotorComRS01Impl.hpp
 * @brief
 */
#ifndef MOTORCOM_IMPL_RS01_HPP
#define MOTORCOM_IMPL_RS01_HPP

#include <net/if.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 	//For sockets

#include "../../5_DataType/RowEnum.hpp"
#include "_MotorCommunicatorInterface.hpp"

/**MotorComRS01Impl class
 *
 */
class MotorComRS01Impl: public MotorCommunicatorInterface {

public:
	/**MotorComRS01Impl constructor
	 * @param Row r
	 */
	MotorComRS01Impl(Row r);

	/**linearMovement
	 * @param int position
	 */
	void linearMovement(int position);

	/**rotate function
	 * @param int amount
	 */
	void rotate(int amount);

protected:
	/**driverInit function
	 *
	 */
	void driverInit();
};

#endif //MOTORCOM_IMPL_PS01_HPP
