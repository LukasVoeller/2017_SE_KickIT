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

	static TableControllerInterface* getMockTableController() {
		vkw = new VirtualKickerWindow();
		tcm = new TableControllerMock();

		tcm->setKickerWindow(vkw);
		vkw->setTableController(tcm);

		vkw->setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
		vkw->show();

		return tcm;
	}

	static TableControllerImpl* getTableController() {
		vkw = new VirtualKickerWindow();
		tci = new TableControllerImpl();

		vkw->setTableController(tci);

		vkw->setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
		vkw->show();

		return tci;
	}

	static TableControllerInterface* getMockTableControllerWithBalltracker() {

		TableControllerInterface* res = VirtualKicker::getMockTableController();
		BallTrackerImpl* bti = new BallTrackerImpl(res);
		bti->setTableController(res);

		return res;
	}

private:
	static VirtualKickerWindow* vkw;
	static TableControllerMock* tcm;
	static TableControllerImpl* tci;

};

VirtualKickerWindow* VirtualKicker::vkw;
TableControllerImpl* VirtualKicker::tci;
TableControllerMock* VirtualKicker::tcm;

#endif //VIRTUALKICKER_HPP
