/* 
 * File:   BallTrackerMock.hpp
 * Author: student
 *
 * Created on 28. April 2017, 18:11
 */

#ifndef BALLTRACKERMOCK_HPP
#define BALLTRACKERMOCK_HPP

#include "BallTrackerInterface.hpp"
#include <QMouseEvent>

class BallTrackerMock: public BallTrackerInterface {
public:
	BallTrackerMock();
	virtual ~BallTrackerMock();

	void startTracking() {
	}
	void stopTracking() {
	}
	BallStatus* getBallStatus();
	void mouseMove(QMouseEvent* e);
private:

};

#endif /* BALLTRACKERMOCK_HPP */

