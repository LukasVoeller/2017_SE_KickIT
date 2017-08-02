#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

#include "../DataType/BallStatus.hpp"
#include "BallTrackerInterface.hpp"


class BallTrackerImpl: public BallTrackerInterface {

public:
	BallStatus* getBallStatus();
	void startTracking();
	void threshold();
	void camera_settings();
	void setCameraSettings();
	void getCameraSettings();

	void setTableController(TableControllerInterface* t);
	~BallTrackerImpl();

private:
	//void threshold();
	//void camera_settings();
	//void setCameraSettings();
	//void getCameraSettings();



};

#endif /* BALLTRACKERIMPL_HPP */
