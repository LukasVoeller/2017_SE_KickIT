/*
 * BallTracker.hpp
 *
 *  Created on: 23.03.2017
 *      Author: student
 */

#ifndef BALLTRACKER_HPP_
#define BALLTRACKER_HPP_
#include "../DataType/BallStatus.hpp"
#include "../RowControl/TableControllerInterface.hpp"
//#include <pylon/PylonIncludes.h>
//#include <pylon/gige/BaslerGigEInstantCamera.h>

class BallTrackerInterface{
    public:
	virtual BallStatus* getBallStatus() = 0;
	virtual void startTracking() = 0;
	virtual void stopTracking() = 0;
    virtual void setTableController(TableControllerInterface* t) = 0;
};


#endif /* BALLTRACKER_HPP_ */
