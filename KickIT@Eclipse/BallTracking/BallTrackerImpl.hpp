#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

#include "../DataType/BallStatus.hpp"
#include "BallTrackerInterface.hpp"

class BallTrackerImpl: public BallTrackerInterface {

public:
	BallStatus* getBallStatus();
	void startTracking();

	void setTableController(TableControllerInterface* t);
	~BallTrackerImpl();

private:
	void camera_settings();
	void setCameraSettings();
	void getCameraSettings();


};

#endif /* BALLTRACKERIMPL_HPP */
