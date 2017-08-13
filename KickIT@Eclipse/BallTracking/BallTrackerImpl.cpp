#include <opencv2/opencv.hpp>
#include <iostream>

#include "BallTrackerInterface.hpp"
#include "BallTrackerImpl.hpp"

using namespace cv;
using namespace std;
using namespace Pylon;
using namespace GenApi;

int exitCode = 0;

BallTrackerImpl::BallTrackerImpl() {
	camera = new Camera();
	startTracking();
}

BallTrackerImpl::BallTrackerImpl(TableControllerInterface* tci) {
	this->tableController = tci;
	camera = new Camera();
	startTracking();

}

//void BallTrackerImpl::setTableController(TableControllerInterface* t) {

//}

BallTrackerImpl::~BallTrackerImpl() {

}

//Datei für Mittelpunkt-Koordinate des Balles
void BallTrackerImpl::startTracking() {
	ThresholdRGB* threshold = camera->threshold();

	//Datei für Mittelpunkt-Koordinate des Balles
	double lastx = 0;
	double lasty = 0;

	//Eigenschaften für Bildanalyse
	Mat imgThresholded;
	vector<Vec3f> circles;

	while (1) {
		Mat* cv_img = camera->getImage();
		Point Ballcenter(0, 0);
		Mat imgHSV;
		//cvtColor(cv_img, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		inRange(*cv_img,
				Scalar(threshold->blueLow, threshold->greenLow,
						threshold->redLow),
				Scalar(threshold->blueHigh, threshold->greenHigh,
						threshold->redHigh), imgThresholded);

		erode(imgThresholded, imgThresholded,
				getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));
		dilate(imgThresholded, imgThresholded,
				getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));

		vector<Point> nonzero;
		//Mat nonzero;

		//cout << "nonzero:" << nonzero << endl;
		if (countNonZero(imgThresholded) > 0) {
			findNonZero(imgThresholded, nonzero);
			Ballcenter = (nonzero.front() + nonzero.back());
			Ballcenter.x = Ballcenter.x / 2;
			Ballcenter.y = Ballcenter.y / 2;
			if (abs(Ballcenter.y - lasty) < 2) {
				Ballcenter.y = lasty;
			}
			if (abs(Ballcenter.x - lastx) < 2) {
				Ballcenter.x = lastx;
			}
			//Draw the circle center
			circle(*cv_img, Ballcenter, 3, Scalar(0, 255, 0), -1, 8, 0);
			//Draw the circle outline
			circle(*cv_img, Ballcenter, 10, Scalar(0, 0, 255), 3, 8, 0);
			lasty = Ballcenter.y;
			lastx = Ballcenter.x;
			tableController->setBallPos(Ballcenter.x, Ballcenter.y);
		}

		//imshow("dif",dif);
		imshow("circles", *cv_img);

		if (cv::waitKey(30) == 27) {
			cv::destroyWindow("Circles");
			break;
		}
	}
}

//BallStatus* BallTrackerImpl::getBallStatus() {
//	return new BallStatus();
//}
