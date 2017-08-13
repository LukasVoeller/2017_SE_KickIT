#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

#include "../DataType/BallStatus.hpp"
#include "BallTrackerInterface.hpp"
#include "Camera/Camera.hpp"

class BallTrackerImpl: public BallTrackerInterface {
public:
	BallTrackerImpl();
	~BallTrackerImpl();	//Virtual?
	BallStatus* getBallStatus();

	//void setTableController(TableControllerInterface* t);

protected:
	void startTracking();
};

#endif //BALLTRACKERIMPL_HPP
