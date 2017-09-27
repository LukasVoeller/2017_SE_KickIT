/**
 * @file BallTrackerImpl.hpp
 *
 */
#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

#include "../../1_BallTracking/Camera/Camera.hpp"
#include "../../2_Control/TableControl/_TableControllerInterface.hpp"
#include "_BallTrackerInterface.hpp"
#include <QObject>

/**BallTrackerImpl class
 *
 */
class BallTrackerImpl: public QObject, public BallTrackerInterface  {
	Q_OBJECT
public:
	/**BallTrackerImpl constructor
	 *
	 * @param TableControllerInterface* tci
	 *
	 * If the BallTracker has detected a new ball position,
	 * he notifies the TableController which is paased to him through the constructor
	 */
	BallTrackerImpl(TableControllerInterface* tci);

	void startTracking();

public slots:
	/**trackingSlot function
	 *
	 * Necessary to run startTracking() in a QThread
	 */
	void trackingSlot(){
		this->startTracking();
	}

protected:
	bool showImage = true;
	double lastx = 0;
	double lasty = 0;
};

#endif //BALLTRACKERIMPL_HPP
