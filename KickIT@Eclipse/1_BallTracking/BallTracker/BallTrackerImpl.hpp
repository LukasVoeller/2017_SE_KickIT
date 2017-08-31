#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

#include "../../1_BallTracking/Camera/Camera.hpp"
#include "../../2_Control/TableControl/_TableControllerInterface.hpp"
#include "../../5_DataType/BallStatus.hpp"
#include "_BallTrackerInterface.hpp"

class BallTrackerImpl: public BallTrackerInterface {
public:
	BallTrackerImpl();
	BallTrackerImpl(TableControllerInterface* tci);
	~BallTrackerImpl();	//Virtual?
	BallStatus* getBallStatus();

	//void setTableController(TableControllerInterface* t);

protected:
	void startTracking();
	bool showImage = true;
};

#endif //BALLTRACKERIMPL_HPP
