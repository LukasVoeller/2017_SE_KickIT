/* 
 * File:   BallTrackerImpl.hpp
 * Author: student
 *
 * Created on 28. April 2017, 17:15
 */

#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

class BallTrackerImpl: public BallTrackerInterface {

public:
	virtual BallStatus* getBallStatus() {
		return new BallStatus();
	}

	virtual void startTracking() {
		//CGrabResultPtr ptrGrabResult;
	}

	virtual void stopTracking() {

	}

	virtual ~BallTrackerImpl() {

	}
};

#endif /* BALLTRACKERIMPL_HPP */
