#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

#include "../../1_BallTracking/Camera/Camera.hpp"
#include "../../2_Control/TableControl/_TableControllerInterface.hpp"
#include "../../5_DataType/BallStatus.hpp"
#include "_BallTrackerInterface.hpp"

class BallTrackerImpl: public BallTrackerInterface {
public:
	BallTrackerImpl(TableControllerInterface* tci);
	~BallTrackerImpl();
	BallStatus* getBallStatus();
	void startTracking();
	void getBallPosition();

protected:
	bool showImage = true;
	double lastx = 0;
	double lasty = 0;
};

#endif //BALLTRACKERIMPL_HPP
