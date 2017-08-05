#ifndef BALLTRACKERINTERFACE_HPP_
#define BALLTRACKERINTERFACE_HPP_

#include "../RowControl/Interface/TableControllerInterface.hpp"
#include "../DataType/BallStatus.hpp"
#include "Camera/Camera.hpp"

class BallTrackerInterface {
public:
	virtual void setTableController(TableControllerInterface* t) = 0;
	virtual ~BallTrackerInterface(){}

private:
	virtual void analyseImage() = 0;
	virtual void startTracking() = 0;

protected:
	Camera* camera;
};

#endif /* BALLTRACKER_HPP_ */
