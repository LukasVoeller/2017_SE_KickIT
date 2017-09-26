/**
 * @file BallTrackerImpl.cpp
 * @brief
 */
#include "../../1_BallTracking/BallTracker/BallTrackerImpl.hpp"
#include "_BallTrackerInterface.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <QThread>

using namespace cv;
using namespace std;
using namespace Pylon;
using namespace GenApi;


BallTrackerImpl::BallTrackerImpl(TableControllerInterface* tci) {
	this->tableController = tci;
	this->camera = new Camera();
	this->threshold = camera->threshold();
}


Vec2 BallTrackerImpl::getBallPosition() {
	Mat* cv_img = camera->getImage();
	Mat imgThresholded;
	Mat imgHSV;
	Point Ballcenter(0, 0);
	vector<Vec3f> circles;
	vector<Point> nonzero;
	int nz;

	inRange(*cv_img,
			Scalar(threshold->blueLow, threshold->greenLow, threshold->redLow),
			Scalar(threshold->blueHigh, threshold->greenHigh,
					threshold->redHigh), imgThresholded);

	erode(imgThresholded, imgThresholded,
			getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));
	dilate(imgThresholded, imgThresholded,
			getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));

	nz = countNonZero(imgThresholded);

	if (nz > 0 && nz < 500) {
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

		if (abs(lastx - Ballcenter.x) > 16 || abs(lasty - Ballcenter.y) > 16) { // only send new position if it is different
			lasty = Ballcenter.y;
			lastx = Ballcenter.x;
			tableController->setBallPos(Ballcenter.x, Ballcenter.y);
			//std::cout << "new" << std::endl;
		}
	}

	delete cv_img;
}


void BallTrackerImpl::startTracking() {
	Mat imgThresholded;
	vector<Vec3f> circles;
	int nz;

	while (1) {
		Mat* cv_img = camera->getImage();
		Point Ballcenter(0, 0);
		Mat imgHSV;

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

		nz = countNonZero(imgThresholded);

		if (nz > 0 && nz < 500) {
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

			if (abs(lastx - Ballcenter.x) > 16
					|| abs(lasty - Ballcenter.y) > 16) { //Only send new position if it is different
				lasty = Ballcenter.y;
				lastx = Ballcenter.x;
				tableController->setBallPos(Ballcenter.x, Ballcenter.y);
			}
		}

		//if (showImage) {
			//imshow("circles", *cv_img);
		//}
		//if (cv::waitKey(30) == 27 && showImage) {
			//cv::destroyWindow("circles");
			//delete cv_img;
			//return;
		//}
	}
}
