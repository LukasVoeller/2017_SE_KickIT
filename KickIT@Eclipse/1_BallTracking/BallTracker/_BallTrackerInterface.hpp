#ifndef BALLTRACKERINTERFACE_HPP
#define BALLTRACKERINTERFACE_HPP

#include "../../2_Control/TableControl/_TableControllerInterface.hpp"
#include "../../5_DataType/BallStatus.hpp"
#include "../Camera/_CameraInterface.hpp"
#include "../../5_DataType/Vec2.hpp"

class BallTrackerInterface {
public:
	void setTableController(TableControllerInterface* t) {
		this->tableController = t;
	}
	virtual ~BallTrackerInterface() {}
	virtual Vec2 getBallPosition() = 0;
	virtual void startTracking() = 0;

protected:
	CameraConfig* threshold;
	CameraInterface* camera;
	TableControllerInterface* tableController;
};

#endif //BALLTRACKER_HPP
