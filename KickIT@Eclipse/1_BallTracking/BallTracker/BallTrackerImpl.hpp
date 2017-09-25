/**
 * file BallTrackerImpl.hpp
 * @brief
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
	 * @param TableControllerInterface* tci
	 * If the BallTracker has detected a new ball position, the TableController must be notified
	 */
	BallTrackerImpl(TableControllerInterface* tci);

	/**BallTrackerImpl destructor
	 *
	 */
	~BallTrackerImpl();

	/**getBallPosition function
	 *
	 */
	Vec2 getBallPosition();

	/**startTracking function
	 *
	 */
	void startTracking();

public slots:
	/**trackingSlot function
	 *
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
