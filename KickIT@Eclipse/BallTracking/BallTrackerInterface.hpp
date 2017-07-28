#ifndef BALLTRACKERINTERFACE_HPP_
#define BALLTRACKERINTERFACE_HPP_
#include "../DataType/BallStatus.hpp"
#include "../RowControl/Interface/TableControllerInterface.hpp"
#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>

class BallTrackerInterface {
public:
	virtual BallStatus* getBallStatus() = 0;
	virtual void startTracking() = 0;
	virtual void stopTracking() = 0;
	virtual void setTableController(TableControllerInterface* t) = 0;
	virtual ~BallTrackerInterface();
};

#endif /* BALLTRACKER_HPP_ */
