#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

#include "../../1_BallTracking/Camera/Camera.hpp"
#include "../../2_Control/TableControl/_TableControllerInterface.hpp"

#include "_BallTrackerInterface.hpp"
#include <QObject>

class BallTrackerImpl: public QObject, public BallTrackerInterface  {
	Q_OBJECT

public:
	BallTrackerImpl(TableControllerInterface* tci);
	~BallTrackerImpl();
	Vec2 getBallPosition();
	void startTracking();

public slots:
	void trackingSlot(){
		this->startTracking();
	}


protected:
	bool showImage = true;
	double lastx = 0;
	double lasty = 0;
};

#endif //BALLTRACKERIMPL_HPP
