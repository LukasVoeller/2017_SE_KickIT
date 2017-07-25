#ifndef BALLTRACKER_HPP_
#define BALLTRACKER_HPP_
#include "../DataType/BallStatus.hpp"
#include "../RowControl/InterfaceTableController.hpp"
//#include <pylon/PylonIncludes.h>
//#include <pylon/gige/BaslerGigEInstantCamera.h>

class BallTrackerInterface {
public:
	virtual BallStatus* getBallStatus() = 0;
	virtual void startTracking() = 0;
	virtual void stopTracking() = 0;
	virtual void setTableController(InterfaceTableController* t) = 0;
	virtual ~BallTrackerInterface();
};

#endif /* BALLTRACKER_HPP_ */
