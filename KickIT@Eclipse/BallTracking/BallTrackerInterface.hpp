#ifndef BALLTRACKERINTERFACE_HPP_
#define BALLTRACKERINTERFACE_HPP_

#include "../RowControl/Interface/TableControllerInterface.hpp"
#include "../DataType/BallStatus.hpp"
#include "Camera/Camera.hpp"

class BallTrackerInterface {
public:
	virtual void setTableController(TableControllerInterface* t) = 0;
	virtual ~BallTrackerInterface(){}



protected:
	Camera* camera;
	virtual void startTracking() = 0;
};

#endif /* BALLTRACKER_HPP_ */
