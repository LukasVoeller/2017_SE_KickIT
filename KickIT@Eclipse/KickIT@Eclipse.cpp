
#include <cstdlib>
#include <QApplication>

#include <VirtualKicker/TableControllerMock.hpp>
#include <RowControl/InterfaceTableController.hpp>

#include "RowControl/InterfaceTableController.hpp"
#include "VirtualKicker/VirtualKicker.hpp"
#include "BallTracking/InterfaceBallTracker.hpp"
#include "RowControl/TableControllerImpl.hpp"

#define MODE 1


int main(int argc, char** argv) {

	InterfaceTableController* tableController;
	BallTrackerInterface* ballTracker;

//virtual mode - ball tracking and table control simulated by a virtual kicker
#if MODE == 1



    QApplication a(argc, argv);
    VirtualKicker::init();

    tableController = VirtualKicker::getMockTableController();


    return a.exec();

#endif

//motor testing mode - ball position is simulated by graphical interface
#if MODE == 2
    //initialize tablecontroller with only the keeper to be controlled
    tableController = new TableControllerImpl(true,true,false,false);

    QApplication a(argc, argv);
    VirtualKicker::init();

    ballTracker = VirtualKicker::getMockBallTracker();

#endif

//balltracking testing mode - table is simulated by graphical interface
#if MODE == 3
#endif

//final mode - ready to play
#if MODE == 4
#endif
}
