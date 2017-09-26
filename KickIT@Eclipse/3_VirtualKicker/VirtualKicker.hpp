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
	 *  @return tcm pointer to a TableControllerMock object
	 */
	static TableControllerInterface* getVirtualKickerTable() {

		/**vkw is a pointer to a VirtualKickerWindow object
		 *
		 */
		VirtualKickerWindow* vkw = new VirtualKickerWindow(true, true);
		/**
		 * tcm is a pointer to a TableControllerMock object
		 */
		TableControllerMock* tcm = new TableControllerMock();

		/**setKickerWindow function
		 * @param vkw
		 */
		tcm->setKickerWindow(vkw);

		/**setTableController function
		 * @param tcm
		 */
		vkw->setTableController(tcm);

		/**setFixedSize function
		 * @param WINDOW_SIZE_X, WINDOW_SIZE_Y
		 */
		vkw->setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);

		/**show function
		 *
		 */
		vkw->show();

		return tcm;
	}

	/**getDisplay function
	 * @return vkw pointer to a VirtualKickerWindow object
	 */
	static VirtualKickerWindow* getDisplay(){
		/**QLabel
		 * sd is a pointer to a QLabel object
		 */
		QLabel* sd = new QLabel();
		/**setMargin function
		 * @param 20
		 *
		 */
		sd->setMargin(20);
		/**QFont
		 * f is a QFont object
		 * @@param "Arial", 30, QFont::Bold
		 */
		QFont f( "Arial", 30, QFont::Bold);

		/**setFont function
		 * @param f
		 *
		 */
		sd->setFont(f);
		/**setFixedSize function
		 * @param 500, 100
		 */
		sd->setFixedSize(500, 100);
		/**VirtualKickerWindow
		 * vkw is a pointer to a VirtualKickerWindow object
		 */
		VirtualKickerWindow* vkw = new VirtualKickerWindow(false, false);
		vkw->speedDisplay = sd;
		/**setFixedSize function
		 * @param WINDOW_SIZE_X, WINDOW_SIZE_Y
		 */
		vkw->setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
		/**move function
		 * @param 200, 200
		 */
		vkw->move(200, 200);
		/**show function
		 *
		 */
		vkw->show();
		return vkw;
	}


};

#endif //VIRTUALKICKER_HPP
