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

using namespace cv;
using namespace std;
using namespace Pylon;

void BallTrackerImpl::setTableController(TableControllerInterface* t){

}

BallTrackerImpl::~BallTrackerImpl(){}

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

//Kameraeinstellungen vornehmen
void BallTrackerImpl::setCameraSettings() {
	char c;			//Eingabewert für I/O
	int i = 0;		//Eingabewert für Höhe, Weite und Paketgröße
	double j = 0;	//Eingabewert für Belichtungszeit
	double y;

	CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
	cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
	camera.Open();

	GenApi::CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
	GenApi::CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
	GenApi::CIntegerPtr packetsize(camera.GetNodeMap().GetNode("GevSCPSPacketSize"));
	GenApi::CFloatPtr exposuretime(camera.GetNodeMap().GetNode("ExposureTimeAbs"));

	cout << "Wollen Sie die Höhe verändern? y/n" << endl;
	cin >> c;
	if(c == 'y'){
		cout << "Geben Sie den Wert für die Höhe ein" << endl;
		cin >> i;
		height->SetValue(i);
	}
	y = 'q';		//Was ist y, und warum wird ihm ein 'q' zugewiesen?

	cout << "Wollen Sie die Weite verändern? y/n" << endl;
	cin >> c;
	if(c == 'y'){
		cout << "Die Werte können nur in 16er Schritten veraendert werden!" << endl;
		cout << "Zum Beispiel 608 , 624 , 640 usw." << endl;
		cout << "Geben Sie den Wert für die Weite ein" << endl;
		cin >> i;
		width->SetValue(i);
	}
	y = 'q';		//Was ist y, und warum wird ihm ein 'q' zugewiesen?

	cout << "Wollen Sie die Packetsize verändern? y/n" << endl;
	cin >> c;
	if(c == 'y'){
		cout << "Die Werte können nur in 4er Schritten veraendert werden!" << endl;
		cout << "Zum Beispiel 996 , 1000 , 1004 usw." << endl;
		cout << "Geben Sie den Wert für die Packetsize ein" << endl;
		cin >> i;
		packetsize->SetValue(i);
	}
	y = 'q';		//Was ist y, und warum wird ihm ein 'q' zugewiesen?

	cout << "Wollen Sie die Belichtungszeit verändern? y/n" << endl;
	cin >> c;
	if(c == 'y'){
		cout << "Geben Sie den Wert für die Belichtungszeit ein" << endl;
		cin >> j;
		exposuretime->SetValue(j);
	}
	y = 'q';		//Was ist y, und warum wird ihm ein 'q' zugewiesen?

	return;
}

//Menupunkt Kameraoperationen
void BallTrackerImpl::camera_settings(){
	int i = 0;

	cout << "Kameraeinstellungen" << endl;
	cout << "Was moechten Sie tun:" << endl;
	cout << "1) Kameraparameter abfragen" << endl;
	cout << "2) Kameraparameter einstellen" << endl;

	cin >> i;
	switch (i) {
		//case 1:
			//BallTrackerImpl::threshold();
		case 1:
			BallTrackerImpl::getCameraSettings();
		break;
		case 2:
			BallTrackerImpl::setCameraSettings();
		break;
		default:
			cout << "Falsche Eingabe erneut versuchen!" << endl;
		break;
	}

	return;
}

//Datei für Mittelpunkt-Koordinate des Balles
void BallTrackerImpl::startTracking() {
	int BlueLow = 234;
	int GreenLow = 206;
	int RedLow = 0;

	int BlueHigh = 255;
	int GreenHigh = 255;
	int RedHigh = 255;

	//Datei für Mittelpunkt-Koordinate des Balles
	double lastx = 0;
	double lasty = 0;
	//double x, y;

	int exitCode = 0;
	Pylon::PylonAutoInitTerm autoInitTerm;
	CGrabResultPtr ptrGrabResult;



		fstream Daten("Daten.txt", ios::out);
		//Eigenschaften für Bildanalyse
		Mat imgThresholded;
		//namedWindow("circles", 1);

		try {
			CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
			cout << "Using device " << camera.GetDeviceInfo().GetModelName()
			<< endl;
			camera.Open();

			GenApi::CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
			GenApi::CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
			Mat cv_img(width->GetValue(), height->GetValue(), CV_8UC3);

			camera.StartGrabbing();
			CPylonImage image;
			CImageFormatConverter fc;
			fc.OutputPixelFormat = PixelType_RGB8packed;
			vector<Vec3f> circles;

			while (1) {
				while (camera.IsGrabbing()) {

					camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);
					if (ptrGrabResult->GrabSucceeded()) {
						fc.Convert(image, ptrGrabResult);

						cv_img = cv::Mat(ptrGrabResult->GetHeight(),
							ptrGrabResult->GetWidth(), CV_8UC3,
							(uint8_t*) image.GetBuffer());
						Point Ballcenter(0, 0);
						Mat imgHSV;
						//cvtColor(cv_img, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

						inRange(cv_img, Scalar(BlueLow, GreenLow,RedLow), Scalar(BlueHigh, GreenHigh, RedHigh),imgThresholded); //Threshold the image
						//morphological opening (remove small objects from the foreground)
						erode(imgThresholded, imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));
						dilate(imgThresholded, imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));

						//morphological closing (fill small holes in the foreground)
						// dilate(imgThresholded, imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
						// erode(imgThresholded, imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));

						vector<Point> nonzero;
						//Mat nonzero;

						//cout << "nonzero:" << nonzero << endl;
						if (countNonZero(imgThresholded) > 0) {
							findNonZero(imgThresholded, nonzero);
							Ballcenter = (nonzero.front() + nonzero.back());
							Ballcenter.x = Ballcenter.x /2;
							Ballcenter.y = Ballcenter.y /2;
							if(abs(Ballcenter.y-lasty) < 2){Ballcenter.y = lasty;}
							if(abs(Ballcenter.x-lastx) < 2){Ballcenter.x = lastx;}
							cout << Ballcenter << endl;
							// draw the circle center
							circle(cv_img, Ballcenter, 3, Scalar(0, 255, 0), -1, 8, 0);
							// draw the circle outline
							circle(cv_img, Ballcenter, 10, Scalar(0, 0, 255), 3, 8, 0);
							lasty = Ballcenter.y;
							lastx = Ballcenter.x;
						}

						//imshow("dif",dif);
						imshow("circles", cv_img);

						waitKey(1);
					}
				}
			}
		} catch (GenICam::GenericException &e) {
			//Error handling.
			cerr << "An exception occurred." << endl << e.GetDescription() << endl;
			exitCode = 1;
		}

		Daten.close();
		return;
}

//BallStatus* BallTrackerImpl::getBallStatus() {
//	return new BallStatus();
//}


