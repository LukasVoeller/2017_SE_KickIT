/* 
 * File:   VirtualKicker.hpp
 * Author: student
 *
 * Created on 28. April 2017, 18:21
 */

#ifndef VIRTUALKICKER_HPP
#define VIRTUALKICKER_HPP

#include "VirtualKickerWindow.hpp"
#include "TableControllerInterface.hpp"
#include "BallTrackerMock.hpp"

class VirtualKicker {

public:
	static const int WINDOW_SIZE_X = 1000;
	static const int WINDOW_SIZE_Y = 700;

	static VirtualKickerWindow* vkw;
	static TableControllerInterface* tc;
	static BallTrackerMock* bt;

	static void init() {
		bt = new BallTrackerMock();
		vkw = new VirtualKickerWindow(bt);
		tc = new TableControllerMock(vkw);

		vkw->setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
		vkw->show();
	}

	static TableControllerInterface* getMockTableController() {
		//return tc;
		return NULL;
	}

	static BallTrackerInterface* getMockBallTracker() {
		//return bt;
		return NULL;
	}

};

VirtualKickerWindow* VirtualKicker::vkw;
TableControllerInterface* VirtualKicker::tc;
BallTrackerMock* VirtualKicker::bt;

#endif /* VIRTUALKICKER_HPP */

