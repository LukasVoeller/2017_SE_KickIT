#ifndef VIRTUALKICKER_HPP
#define VIRTUALKICKER_HPP

#include "VirtualKickerWindow.hpp"
#include "../1_BallTracking/BallTracker/_BallTrackerInterface.hpp"
#include "../1_BallTracking/BallTracker/BallTrackerImpl.hpp"
#include "../2_Control/TableControl/_TableControllerInterface.hpp"

using namespace std;

class VirtualKicker {

public:
	static const int WINDOW_SIZE_X = 1024;
	static const int WINDOW_SIZE_Y = 768;

	static TableControllerInterface* getVirtualKickerTable() {

		VirtualKickerWindow* vkw = new VirtualKickerWindow();
		TableControllerMock* tcm = new TableControllerMock();

		tcm->setKickerWindow(vkw);
		vkw->setTableController(tcm);

		vkw->setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
		vkw->show();

		return tcm;
	}

	static VirtualKickerWindow* getDisplay(){
		VirtualKickerWindow* vkw = new VirtualKickerWindow();
		//vkw->setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
		vkw->setFixedSize(1200, 800);
		vkw->show();
		return vkw;
	}


};

#endif //VIRTUALKICKER_HPP
