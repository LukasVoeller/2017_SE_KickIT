#include <cstdlib>
#include <QApplication>

#include <VirtualKicker/TableControllerMock.hpp>
#include <RowControl/InterfaceTableController.hpp>

#include "RowControl/InterfaceTableController.hpp"
#include "BallTracking/InterfaceBallTracker.hpp"
#include "RowControl/TableControllerImpl.hpp"
#include "VirtualKicker/VirtualKicker.hpp"

#define MODE 1

int main(int argc, char** argv) {

	InterfaceTableController* tableController;
	BallTrackerInterface* ballTracker;

//Virtual mode - Ball tracking and table control is simulated by the virtual kicker
#if MODE == 1

	QApplication a(argc, argv);
	VirtualKicker::init();

	tableController = VirtualKicker::getMockTableController();

	return a.exec();

#endif

//Motor testing mode - Ball position is simulated by graphical interface
#if MODE == 2

	tableController = new TableControllerImpl(true,true,false,false);

	QApplication a(argc, argv);
	VirtualKicker::init();

	ballTracker = VirtualKicker::getMockBallTracker();

#endif

//Balltracking testing mode - Table is simulated by graphical interface
#if MODE == 3

#endif

//Final mode - Ready to play!
#if MODE == 4

#endif
}
