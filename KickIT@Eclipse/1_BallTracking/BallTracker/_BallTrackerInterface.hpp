#ifndef BALLTRACKERINTERFACE_HPP_
#define BALLTRACKERINTERFACE_HPP_

#include "../Camera/Camera.hpp"
#include "../../5_DataType/BallStatus.hpp"
#include "../../2_Control/TableControl/_TableControllerInterface.hpp"

class BallTrackerInterface {
public:
	void setTableController(TableControllerInterface* t){
		this->tableController = t;
	}
	virtual ~BallTrackerInterface(){}

protected:
	Camera* camera;
	virtual void startTracking() = 0;

	TableControllerInterface* tableController;
};

#endif //BALLTRACKER_HPP_
