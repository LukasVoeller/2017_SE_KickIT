#include "BallTrackerInterface.hpp"
#include "BallTrackerImpl.hpp"
#include <iostream>


//using namespace cv;
using namespace std;
using namespace Pylon;

//Kameraeinstellungen auslesen
void BallTrackerImpl::getCameraSettings() {
	CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
	cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
	camera.Open();

	GenApi::CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
	GenApi::CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
	GenApi::CIntegerPtr packetsize(camera.GetNodeMap().GetNode("GevSCPSPacketSize"));
	GenApi::CFloatPtr exposuretime(camera.GetNodeMap().GetNode("ExposureTimeAbs"));

	cout << endl << "Aktuelle Kameraparameter:" << endl;
	camera.GetNodeMap().GetNode("Height");
	cout << "Höhe: " << width->GetValue() << endl;
	cout << "Weite: " << height->GetValue() << endl;
	cout << "Packetsize: " << packetsize->GetValue() << endl;
	cout << "Belichtungszeit: " << exposuretime->GetValue() << endl << endl;
}

BallStatus* BallTrackerImpl::getBallStatus() {
	return new BallStatus();
}

void BallTrackerImpl::startTracking() {
	//CGrabResultPtr ptrGrabResult;
}

void BallTrackerImpl::stopTracking() {

}

