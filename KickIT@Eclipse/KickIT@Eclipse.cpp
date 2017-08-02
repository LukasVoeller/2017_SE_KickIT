/********************************************************************************
 * Software Engineering Projekt
 * Hochschule Osnabrueck, Sommersemester 2017
 *
 * Programmname      : KickIT
 * Version			 : 0.4.5-0001
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
 * TODO              : Warnings beheben
 *
 ********************************************************************************/

#include <BallTracking/BallTrackerInterface.hpp>
#include <cstdlib>
#include <QApplication>

#include <VirtualKicker/TableControllerMock.hpp>
#include <RowControl/Interface/TableControllerInterface.hpp>

#include "RowControl/Interface/TableControllerInterface.hpp"
#include "RowControl/Control/TableControllerImpl.hpp"
#include "VirtualKicker/VirtualKicker.hpp"

#define MODE 3

int main(int argc, char** argv) {

	TableControllerInterface* tableController;
	BallTrackerInterface* ballTracker;

//Virtual mode - Ball tracking and table control is simulated by the virtual kicker
#if MODE == 1

	QApplication a(argc, argv);

	tableController = VirtualKicker::getMockTableController();

	return a.exec();

#endif

//Motor testing mode - Ball position is simulated by graphical interface
#if MODE == 2

	QApplication a(argc, argv);

	tableController = VirtualKicker::getTableController();

	return a.exec();

#endif

//Balltracking testing mode - Table is simulated by graphical interface
#if MODE == 3

	QApplication a(argc, argv);
	VirtualKicker::getMockTableControllerWithBalltracker();
	return a.exec();

#endif

//Final mode - Ready to play!
#if MODE == 4

#endif
}
