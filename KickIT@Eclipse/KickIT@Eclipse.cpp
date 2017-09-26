/**
 * @file KickIT@Eclipse.cpp
 * @brief
 */
/*******************************************************************************************************
 *
 * KKKKKKKKK    KKKKKKK  iiii                      kkkkkkkk           IIIIIIIIIITTTTTTTTTTTTTTTTTTTTTTT
 * K:::::::K    K:::::K i::::i                     k::::::k           I::::::::IT:::::::::::::::::::::T
 * K:::::::K    K:::::K  iiii                      k::::::k           I::::::::IT:::::::::::::::::::::T
 * K:::::::K   K::::::K                            k::::::k           II::::::IIT:::::TT:::::::TT:::::T
 * KK::::::K  K:::::KKKiiiiiii     cccccccccccccccc k:::::k    kkkkkkk  I::::I  TTTTTT  T:::::T  TTTTTT
 *   K:::::K K:::::K   i:::::i   cc:::::::::::::::c k:::::k   k:::::k   I::::I          T:::::T
 *   K::::::K:::::K     i::::i  c:::::::::::::::::c k:::::k  k:::::k    I::::I          T:::::T
 *   K:::::::::::K      i::::i c:::::::cccccc:::::c k:::::k k:::::k     I::::I          T:::::T
 *   K:::::::::::K      i::::i c::::::c     ccccccc k::::::k:::::k      I::::I          T:::::T
 *   K::::::K:::::K     i::::i c:::::c              k:::::::::::k       I::::I          T:::::T
 *   K:::::K K:::::K    i::::i c:::::c              k:::::::::::k       I::::I          T:::::T
 * KK::::::K  K:::::KKK i::::i c::::::c     ccccccc k::::::k:::::k      I::::I          T:::::T
 * K:::::::K   K::::::Ki::::::ic:::::::cccccc:::::ck::::::k k:::::k   II::::::II      TT:::::::TT
 * K:::::::K    K:::::Ki::::::i c:::::::::::::::::ck::::::k  k:::::k  I::::::::I      T:::::::::T
 * K:::::::K    K:::::Ki::::::i  cc:::::::::::::::ck::::::k   k:::::k I::::::::I      T:::::::::T
 * KKKKKKKKK    KKKKKKKiiiiiiii    cccccccccccccccckkkkkkkk    kkkkkkkIIIIIIIIII      TTTTTTTTTTT ©2017
 *
 * Software Engineering Projekt
 * Hochschule Osnabrueck, Sommersemester 2017
 *
 * Programmname      : KickIT
 * Version			 : 0.7.4-0001
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
 *******************************************************************************************************/

#include "1_BallTracking/BallTracker/_BallTrackerInterface.hpp"
#include "2_Control/MotorCommunication/_MotorCommunicatorInterface.hpp"
#include "2_Control/TableControl/_TableControllerInterface.hpp"
#include "2_Control/TableControl/TableControllerMock.hpp"
#include "2_Control/TableControl/TableControllerImpl.hpp"
#include "3_VirtualKicker/VirtualKicker.hpp"
#include "4_Utilities/Calculator.hpp"
#include "4_Utilities/Modules.hpp"
#include "5_DataType/MotorConfig.hpp"
#include "5_DataType/TableConfig.hpp"
#include <QApplication>
#include <cstdlib>

#define MODE 2
Modules* Modules::_instance = 0;

bool keeperHomed = false;
bool defenseHomed = false;


/**main function
 *
 * @param (int argc, char** argv)
 *
 */
int main(int argc, char** argv) {
	Modules::instance()->registerFunction("calcIfKickSimple", &(Calculator::calcIfKickSimple));
	Modules::instance()->registerFunction("calcPositionsSimple", &(Calculator::calcPositionsSimple));

	/**MODE == 1
	 *
	 * Virtual mode - Ball tracking and table control is simulated by the virtual kicker
	 *
	 * @return a.exec()
	 */
	#if MODE == 1

		QApplication a(argc, argv);
		tableController = VirtualKicker::getVirtualKickerTable();
		return a.exec();

	#endif

	/**MODE == 2
	 *
	 * Final mode - Ready to play!
	 *
	 * @return a.exec()
	 */
	#if MODE == 2
		QApplication a(argc, argv);
		VirtualKickerWindow* vkw = VirtualKicker::getDisplay();
		TableControllerImpl* tci = new TableControllerImpl(vkw);
		BallTrackerImpl* bti = new BallTrackerImpl(tci);

		MotorConfig mc;

		if(!defenseHomed || !keeperHomed) cout << "waiting for motors" << endl;
		while(!defenseHomed || !keeperHomed){
			sleep(1);
		}


		QThread* th = new QThread();
		bti->moveToThread(th);
		th->start();
		QObject::connect(th, SIGNAL (started()), bti, SLOT (trackingSlot()));
		//QObject::connect(tci, SIGNAL(newBallStatus(BallStatus bs)), vkw, SLOT(newBallStatus(BallStatus bs)));
		return a.exec();

	#endif
}
