#ifndef BALLTRACKERINTERFACE_HPP_
#define BALLTRACKERINTERFACE_HPP_

#include "../RowControl/Interface/TableControllerInterface.hpp"
#include "../DataType/BallStatus.hpp"
#include "Camera/Camera.hpp"
#include "../RowControl/Interface/TableControllerInterface.hpp"

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

#endif /* BALLTRACKER_HPP_ */
