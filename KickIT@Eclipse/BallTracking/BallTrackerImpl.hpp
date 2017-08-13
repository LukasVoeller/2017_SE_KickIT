#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

#include "../DataType/BallStatus.hpp"
#include "BallTrackerInterface.hpp"
#include "Camera/Camera.hpp"
#include "../RowControl/Interface/TableControllerInterface.hpp"

class BallTrackerImpl: public BallTrackerInterface {
public:
	BallTrackerImpl();
	BallTrackerImpl(TableControllerInterface* tci);
	~BallTrackerImpl();	//Virtual?
	BallStatus* getBallStatus();

	//void setTableController(TableControllerInterface* t);

protected:
	void startTracking();
};

#endif //BALLTRACKERIMPL_HPP
