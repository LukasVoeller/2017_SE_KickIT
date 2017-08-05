#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

#include "../DataType/BallStatus.hpp"
#include "BallTrackerInterface.hpp"
#include "Camera/Camera.hpp"

class BallTrackerImpl: public BallTrackerInterface {

public:

	BallTrackerImpl();

	BallStatus* getBallStatus();


	void setTableController(TableControllerInterface* t);
	~BallTrackerImpl();


private:
	void startTracking();
	void analyseImage();



};

#endif /* BALLTRACKERIMPL_HPP */
