#ifndef BALLTRACKERINTERFACE_HPP_
#define BALLTRACKERINTERFACE_HPP_

#include "../Camera/_CameraInterface.hpp"
#include "../../5_DataType/BallStatus.hpp"
#include "../../2_Control/TableControl/_TableControllerInterface.hpp"

class BallTrackerInterface {
public:
	void setTableController(TableControllerInterface* t){
		this->tableController = t;
	}
	virtual ~BallTrackerInterface(){}
	virtual void getBallPosition() = 0;
	virtual void startTracking() = 0;

protected:
	CameraConfig* threshold;
	CameraInterface* camera;
	TableControllerInterface* tableController;
};

#endif //BALLTRACKER_HPP_
