
#include <cstdlib>
#include <QApplication>

#include <VirtualKicker/TableControllerMock.h>
#include <RowControl/TableControllerInterface.hpp>


TableControllerInterface* tableController;



int main(int argc, char** argv) {

//virtual mode - ball tracking and table control emulated by a virtual kicker
#if 1
    QApplication a(argc, argv);
    
    tableController = new TableControllerMock();
    

    return a.exec();
#endif
    
    
    
//final mode
#if 0
    
#endif
}

