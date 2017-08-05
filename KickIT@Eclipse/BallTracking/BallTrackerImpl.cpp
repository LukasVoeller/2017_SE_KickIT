#include "BallTrackerInterface.hpp"
#include "BallTrackerImpl.hpp"
#include <iostream>

#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

using namespace cv;
using namespace std;
using namespace Pylon;

int exitCode = 0;
Pylon::PylonAutoInitTerm autoInitTerm;
CGrabResultPtr ptrGrabResult;

BallTrackerImpl::BallTrackerImpl(){
	std::cout << "BallTrackerImpl" << std::endl;
	camera = new Camera();
	//startTracking();
	analyseImage();
}


void BallTrackerImpl::setTableController(TableControllerInterface* t){

}

BallTrackerImpl::~BallTrackerImpl(){}




void BallTrackerImpl::analyseImage(){
	cout << "AnalyseImage" << endl;
}

//Datei für Mittelpunkt-Koordinate des Balles
void BallTrackerImpl::startTracking() {

}

//BallStatus* BallTrackerImpl::getBallStatus() {
//	return new BallStatus();
//}


