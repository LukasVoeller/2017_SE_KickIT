/**
 * @file VirtualKicker.hpp
 * @brief
 */
#ifndef VIRTUALKICKER_HPP
#define VIRTUALKICKER_HPP

#include "VirtualKickerWindow.hpp"
#include "../1_BallTracking/BallTracker/_BallTrackerInterface.hpp"
#include "../1_BallTracking/BallTracker/BallTrackerImpl.hpp"
#include "../2_Control/TableControl/_TableControllerInterface.hpp"
#include <QThread>

using namespace std;

/**VirtualKicker class
 *
 */
class VirtualKicker {

public:
	static const int WINDOW_SIZE_X = 1200;
	static const int WINDOW_SIZE_Y = 800;

	/**getVirtualKickerTable function
	 *
	 *  @return tcm to a TableControllerMock object
	 */
	static TableControllerInterface* getVirtualKickerTable() {
		VirtualKickerWindow* vkw = new VirtualKickerWindow(true, true);
		TableControllerMock* tcm = new TableControllerMock();
		tcm->setKickerWindow(vkw);
		vkw->setTableController(tcm);
		vkw->setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
		vkw->show();

		return tcm;
	}

	/**getDisplay function
	 *
	 * @return vkw to a VirtualKickerWindow object
	 */
	static VirtualKickerWindow* getDisplay(){
		QLabel* sd = new QLabel();
		sd->setMargin(20);
		QFont f( "Arial", 30, QFont::Bold);
		sd->setFont(f);
		sd->setFixedSize(500, 100);
		VirtualKickerWindow* vkw = new VirtualKickerWindow(false, false);
		vkw->speedDisplay = sd;
		vkw->setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
		vkw->move(200, 200);
		vkw->show();
		return vkw;
	}


};

#endif //VIRTUALKICKER_HPP
