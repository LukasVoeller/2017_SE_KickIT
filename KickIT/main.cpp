
#include <cstdlib>
#include <QApplication>

#include <VirtualKicker/TableControllerMock.hpp>
#include <RowControl/TableControllerInterface.hpp>

#include "VirtualKicker/VirtualKicker.hpp"

TableControllerInterface* tableController;
BallTrackerInterface* ballTracker;



int main(int argc, char** argv) {

//virtual mode - ball tracking and table control emulated by a virtual kicker
#if 1
    QApplication a(argc, argv);
    
    VirtualKicker::init();
    
    
    tableController = VirtualKicker::getMockTableController();
    ballTracker = VirtualKicker::getMockBallTracker();
    
    
    
    

    return a.exec();
#endif
    
    
    
//final mode
#if 0
    
#endif
}
