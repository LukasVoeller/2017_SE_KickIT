#ifndef VIRTUALKICKER_HPP
#define VIRTUALKICKER_HPP

#include "../BallTracking/BallTrackerInterface.hpp"
#include "../BallTracking/BallTrackerImpl.hpp"
#include "VirtualKickerWindow.hpp"
#include "../RowControl/Interface/TableControllerInterface.hpp"

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
	}


};

#endif //VIRTUALKICKER_HPP
