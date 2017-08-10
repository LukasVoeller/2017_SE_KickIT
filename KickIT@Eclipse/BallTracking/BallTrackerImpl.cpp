#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <pylon/PylonIncludes.h>
#include <iostream>

#include "BallTrackerInterface.hpp"
#include "BallTrackerImpl.hpp"

#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

using namespace cv;
using namespace std;
using namespace Pylon;
using namespace GenApi;

int exitCode = 0;
PylonAutoInitTerm autoInitTerm;
CGrabResultPtr ptrGrabResult;

BallTrackerImpl::BallTrackerImpl() {
	std::cout << "BallTrackerImpl" << std::endl;
	camera = new Camera();
	analyseImage();
	startTracking();
}

void BallTrackerImpl::setTableController(TableControllerInterface* t) {

}

BallTrackerImpl::~BallTrackerImpl() {

}

void BallTrackerImpl::analyseImage() {
	cout << "AnalyseImage" << endl;
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

		fstream Daten("Daten.txt", ios::out);
		//Eigenschaften für Bildanalyse
		Mat imgThresholded;
		//namedWindow("circles", 1);

		try {
			CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
			cout << "Using device " << camera.GetDeviceInfo().GetModelName()
			<< endl;
			camera.Open();

			CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
			CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
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

						cv_img = Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t*) image.GetBuffer());
						Point Ballcenter(0, 0);
						Mat imgHSV;
						//cvtColor(cv_img, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

						inRange(cv_img, Scalar(BlueLow, GreenLow,RedLow), Scalar(BlueHigh, GreenHigh, RedHigh),imgThresholded); //Threshold the image
						erode(imgThresholded, imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));
						dilate(imgThresholded, imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));

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
							//Draw the circle center
							circle(cv_img, Ballcenter, 3, Scalar(0, 255, 0), -1, 8, 0);
							//Draw the circle outline
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
