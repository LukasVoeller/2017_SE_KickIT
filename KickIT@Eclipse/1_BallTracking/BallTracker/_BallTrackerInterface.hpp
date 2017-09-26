/**
 * @file BallTrackerInterface.hpp
 * @brief
 */
#ifndef BALLTRACKERINTERFACE_HPP
#define BALLTRACKERINTERFACE_HPP

#include "../../2_Control/TableControl/_TableControllerInterface.hpp"
#include "../../5_DataType/BallStatus.hpp"
#include "../Camera/_CameraInterface.hpp"
#include "../../5_DataType/Vec2.hpp"

/**BallTrackerInterface class
 *
 */
class BallTrackerInterface {
public:
	/**setTableController function
	 *
	 * @param (TableControllerInterface* t)
	 */
	void setTableController(TableControllerInterface* t) {
		this->tableController = t;
	}
	/**BallTrackerInterface destructor
	 *
	 */
	virtual ~BallTrackerInterface() {}

	/**getBallPosition function
	 *
	 */
	virtual Vec2 getBallPosition() = 0;

	/**startTracking function
	 *
	 */
	virtual void startTracking() = 0;

protected:
	CameraConfig* threshold;
	CameraInterface* camera;
	TableControllerInterface* tableController;
};

#endif //BALLTRACKER_HPP
