#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

#include "../DataType/BallStatus.hpp"
#include "BallTrackerInterface.hpp"
#include "Camera/Camera.hpp"

class BallTrackerImpl: public BallTrackerInterface {

public:

	BallTrackerImpl();

	BallStatus* getBallStatus();
	void startTracking();
	void threshold();
	void camera_settings();
	void setCameraSettings();
	void getCameraSettings();

	void setTableController(TableControllerInterface* t);
	~BallTrackerImpl();

	void stopTracking() {}

private:

	Camera* camera;



};

#endif /* BALLTRACKERIMPL_HPP */
