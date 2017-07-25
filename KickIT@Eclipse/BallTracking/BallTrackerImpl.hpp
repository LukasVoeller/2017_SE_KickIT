#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

class BallTrackerImpl: public BallTrackerInterface {

public:
	virtual BallStatus* getBallStatus() {
		return BallStatus;
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

