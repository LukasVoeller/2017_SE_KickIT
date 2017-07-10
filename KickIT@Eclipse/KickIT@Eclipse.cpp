
#include <cstdlib>
#include <QApplication>

#include <VirtualKicker/TableControllerMock.hpp>
#include <RowControl/TableControllerInterface.hpp>

#include "RowControl/TableControllerInterface.hpp"
#include "VirtualKicker/VirtualKicker.hpp"
#include "BallTracking/BallTrackerInterface.hpp"
#include "RowControl/TableControllerImpl.hpp"


int main(int argc, char** argv) {

	TableControllerInterface* tableController;
	BallTrackerInterface* ballTracker;

//virtual mode - ball tracking and table control simulated by a virtual kicker
#if 0



    QApplication a(argc, argv);
    VirtualKicker::init();

    tableController = VirtualKicker::getMockTableController();
    ballTracker = VirtualKicker::getMockBallTracker();

    //tableController->setBallTrackerMock(ballTracker);
    //ballTracker->setTableController(tableController);

    return a.exec();

#endif

//motor testing mode - ball position is simulated by graphical interface
#if 1
    tableController = new TableControllerImpl(1,0,0,0);

#endif

//balltracking testing mode - table is simulated by graphical interface
#if 0
#endif

//final mode - ready to play
#if 0
#endif
}
