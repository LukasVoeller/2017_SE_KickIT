/*
 * Camera.cpp
 *
 *  Created on: Aug 2, 2017
 *      Author: student
 */

#include "Camera.hpp"
#include <thread>


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


Camera::Camera() {

	std::cout << "camera" << std::endl;
	//std::thread c(&Camera::calibrate, this);
	//c.join();
	calibrate();
}

Camera::~Camera() {

}

void Camera::calibrate(){
	PylonAutoInitTerm autoInitTerm;
	CGrabResultPtr ptrGrabResult;
	CImageFormatConverter fc;
	fc.OutputPixelFormat = PixelType_RGB8packed;
	CPylonImage image;
	vector<Vec3f> circles;
	cout << "thread" << endl;
	CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
	camera.Open();

	GenApi::CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
	GenApi::CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));

	Mat cv_img(width->GetValue(), height->GetValue(), CV_8UC3);

	camera.StartGrabbing();

	for(int i = 0; i < 5 ; i++){
		cout << i << endl;
		while (camera.IsGrabbing()) {

			camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

			if (ptrGrabResult->GrabSucceeded()) {
				cout << "success" << endl;
				fc.Convert(image, ptrGrabResult);
				cv_img = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t*) image.GetBuffer());
				imshow("circles", cv_img);

				waitKey(1);
			}
		}

	}

}

//Kameraeinstellungen auslesen
void Camera::getCameraSettings() {

}

//Kameraeinstellungen vornehmen
void Camera::setCameraSettings() {

}

//Menupunkt Kameraoperationen
void Camera::camera_settings(){

}

void Camera::threshold(){

}
