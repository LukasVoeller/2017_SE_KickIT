
#include <cstdlib>
#include <QApplication>

#include <VirtualKicker/TableControllerMock.hpp>
#include <RowControl/TableControllerInterface.hpp>

#include "VirtualKicker/VirtualKicker.hpp"



int main(int argc, char** argv) {

//virtual mode - ball tracking and table control simulated by a virtual kicker
#if 1

	TableControllerMock* tableController;
	BallTrackerMock* ballTracker;

    QApplication a(argc, argv);
    VirtualKicker::init();

    tableController = VirtualKicker::getMockTableController();
    ballTracker = VirtualKicker::getMockBallTracker();

    //tableController->setBallTrackerMock(ballTracker);
    //ballTracker->setTableController(tableController);

    return a.exec();

#endif

//motor testing mode - ball position is simulated by graphical interface
#if 0

#endif

//balltracking testing mode - table is simulated by graphical interface
#if 0
#endif

//final mode - ready to play
#if 0
#endif
}
