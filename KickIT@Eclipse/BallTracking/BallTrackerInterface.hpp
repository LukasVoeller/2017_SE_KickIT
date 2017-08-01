#ifndef BALLTRACKERINTERFACE_HPP_
#define BALLTRACKERINTERFACE_HPP_
#include "../DataType/BallStatus.hpp"
#include "../RowControl/Interface/TableControllerInterface.hpp"


class BallTrackerInterface {
public:

	virtual void setTableController(TableControllerInterface* t) = 0;
	virtual ~BallTrackerInterface(){}

};

#endif /* BALLTRACKER_HPP_ */
