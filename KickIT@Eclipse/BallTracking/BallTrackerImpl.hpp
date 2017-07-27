#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

#include "../DataType/BallStatus.hpp"
#include "InterfaceBallTracker.hpp".hpp"

class BallTrackerImpl: public BallTrackerInterface {

public:
	BallStatus* getBallStatus();
	void startTracking();
	void stopTracking();
	~BallTrackerImpl();

private:
	void getCameraSettings();

};

#endif /* BALLTRACKERIMPL_HPP */

