/********************************************************************************
 * Software Engineering Projekt
 * Hochschule Osnabrueck, Sommersemester 2017
 *
 * Programmname      : KickIT
 * Version			 : 0.7.0-0001
 *
 * Authoren          : Lukas Voeller, Philip Baumgartner, Viktor Koschmann
 *
 * Erstellt am       : 15. April 2017
 *
 * Verwendugszweck   : Software framework fuer einen autonomen Kickertisch
 *
 * Bibliotheken      : QT (v5.8)      - Grafische Oberfläche, Virtual Kicker
 * 					   OpenCV (v2)    - Ballerkennung
 *                     Pylon (v5.0.1) - Kamerabilddarstellung
 *
 * TODO              :
 *
 ********************************************************************************/

//#include <BallTracking/BallTrackerInterface.hpp>
#include "2_Control/TableControl/TableControllerMock.hpp"
#include "3_VirtualKicker/VirtualKicker.hpp"
#include "4_Utilities/Calculator.hpp"
#include "4_Utilities/Modules.hpp"
#include "5_DataType/MotorConfig.hpp"
#include "5_DataType/TableConfig.hpp"
#include "2_Control/TableControl/TableControllerImpl.hpp"
#include <cstdlib>
#include <QApplication>
#include "1_BallTracking/BallTracker/_BallTrackerInterface.hpp"
#include "2_Control/TableControl/_TableControllerInterface.hpp"
#include "2_Control/MotorCommunication/_MotorCommunicatorInterface.hpp"

#define MODE 4
Modules* Modules::_instance = 0;
int main(int argc, char** argv) {

	Modules::instance()->registerFunction("calcIfKickSimple", &(Calculator::calcIfKickSimple));
	Modules::instance()->registerFunction("calcPositionsSimple", &(Calculator::calcPositionsSimple));
	//Modules::execute("calcIfKick", NULL);

	TableControllerInterface* tableController;

//Virtual mode - Ball tracking and table control is simulated by the virtual kicker
#if MODE == 1

	QApplication a(argc, argv);
	tableController = VirtualKicker::getVirtualKickerTable();
	return a.exec();

#endif

//Motor testing mode - The ball position is simulated with the GUI
#if MODE == 2
#endif

//Balltracking testing mode - The table is simulated with the GUI
#if MODE == 3
#endif

//Final mode - Ready to play!
#if MODE == 4

	QApplication a(argc, argv);
	TableControllerInterface* tci = new TableControllerImpl(VirtualKicker::getDisplay());
	BallTrackerInterface* bti = new BallTrackerImpl(tci);
	//tci->motorByHand();
	return a.exec();
#endif
}
