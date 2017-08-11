#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <pylon/usb/BaslerUsbInstantCamera.h>
#include <pylon/PylonIncludes.h>
#include "Camera.hpp"

#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

//#define _CRT_SECURE_NO_WARNINGS
PylonAutoInitTerm autoInitTerm;
CGrabResultPtr ptrGrabResult;

using namespace cv;
using namespace std;
using namespace Pylon;
using namespace GenApi;

Camera::Camera():camera(CTlFactory::GetInstance().CreateFirstDevice()) {
	cout << "Camera Constructor" << std::endl;
	camera.Open();
	camera.StartGrabbing();

	this->setCameraSettings();
	this->getCameraSettings();
	this->threshold();
}

Camera::~Camera() {

}

Mat* Camera::getImage() {
	CPylonImage image;
	CImageFormatConverter fc;
	CGrabResultPtr ptrGrabResult;
	fc.OutputPixelFormat = PixelType_RGB8packed;
	CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
	CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
	Mat* cv_img = new Mat(width->GetValue(), height->GetValue(), CV_8UC3);

	if (camera.IsGrabbing()) {
		camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);
		if (ptrGrabResult->GrabSucceeded()) {
			fc.Convert(image, ptrGrabResult);
			*cv_img = Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t*) image.GetBuffer());
		} else {
			cout << "grab failed" << endl;
		}

	} else {
		cout << "camera not grabbing" << endl;
	}

	return cv_img;
}

void Camera::calibrate() {
	PylonAutoInitTerm autoInitTerm;
	CGrabResultPtr ptrGrabResult;
	CImageFormatConverter fc;
	CPylonImage image;
	vector<Vec3f> circles;

	fc.OutputPixelFormat = PixelType_RGB8packed;


	CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
	CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
	Mat cv_img(width->GetValue(), height->GetValue(), CV_8UC3);



	for (int i = 0; i < 5; i++) {
		while (camera.IsGrabbing()) {

			camera.RetrieveResult(5000, ptrGrabResult,
					TimeoutHandling_ThrowException);

			if (ptrGrabResult->GrabSucceeded()) {
				cout << "Grabbing succeeded" << endl;

				fc.Convert(image, ptrGrabResult);
				cv_img = Mat(ptrGrabResult->GetHeight(),
						ptrGrabResult->GetWidth(), CV_8UC3,
						(uint8_t*) image.GetBuffer());
				imshow("circles", cv_img);

				waitKey(1); // macht evtl probleme
			}
		}

	}

}

//Kameraeinstellungen vornehmen
void Camera::setCameraSettings() {
	PylonAutoInitTerm autoInitTerm;
	CGrabResultPtr ptrGrabResult;
	CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
	Mat* cv_img = getImage();
	cout << "Using device: " << camera.GetDeviceInfo().GetModelName() << endl;
	//camera.Open();

	CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
	CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
	CIntegerPtr packetsize(camera.GetNodeMap().GetNode("GevSCPSPacketSize"));
	CFloatPtr exposuretime(camera.GetNodeMap().GetNode("ExposureTimeAbs"));
	//CFloatPtr exposuretimeLowerLimit(camera.GetNodeMap().GetNode("AutoExposureTimeAbsLowerLimit"));
	//CFloatPtr exposuretimeUpperLimit(camera.GetNodeMap().GetNode("AutoExposureTimeAbsUpperLimit"));
	//CIntegerPtr exposuretimeTargetValue(camera.GetNodeMap().GetNode("AutoTargetValue"));
	//CIntegerPtr exposuretimeAuto(camera.GetNodeMap().GetNode("ExposureAuto"));

	//exposuretime->GetMin();
	//exposuretime->GetMax();
	//exposuretimeLowerLimit->SetValue(1000.0);
	//exposuretimeUpperLimit->SetValue(1.0E6);
	//exposuretimeTargetValue->SetValue(128);
	//exposuretimeAuto->SetValue(ExposureAuto_Continuous);

	height->SetValue(374);
	width->SetValue(608);
	packetsize->SetValue(1500);

	//exposuretime->SetValue(128);
	//exposuretime->GetMin();
	//exposuretime->GetMax();
	cout << "Kammeraeinstellungen vorgenohmen" << endl;
}

//Kameraeinstellungen auslesen
void Camera::getCameraSettings() {
	CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
	cout << "Using camera: " << camera.GetDeviceInfo().GetModelName() << endl;

	camera.Open();

	CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
	CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
	CIntegerPtr packetsize(camera.GetNodeMap().GetNode("GevSCPSPacketSize"));
	CFloatPtr exposuretime(camera.GetNodeMap().GetNode("ExposureTimeAbs"));

	cout << "Aktuelle Kameraparameter: " << endl;
	cout << "Höhe: " << width->GetValue() << endl;
	cout << "Weite: " << height->GetValue() << endl;
	cout << "Packetsize: " << packetsize->GetValue() << endl;
	cout << "Belichtungszeit: " << exposuretime->GetValue() << endl << endl;
}

//Menupunkt Kameraoperationen
void Camera::cameraSettings() {
	//TO DO
}


//Grenzwertebestimmen
void Camera::threshold() {

	CGrabResultPtr ptrGrabResult;

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //Create a window called "Control"
	int iLowH = 0;		//0
	int iHighH = 255;	//179

	int iLowS = 0;		//0
	int iHighS = 255; 	//255

	int iLowV = 0; 		//0
	int iHighV = 255; 	//255

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowB", "Control", &iLowH, 255); //Hue (0 - 179)
	cvCreateTrackbar("HighB", "Control", &iHighH, 255);

	cvCreateTrackbar("LowG", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighG", "Control", &iHighS, 255);

	cvCreateTrackbar("LowR", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighR", "Control", &iHighV, 255);

	//while (1) {

		Mat* cv_img = getImage();
		Mat imgHSV;
		Mat imgThresholded;


		inRange(*cv_img, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));


		//Draw contours
		imshow("Thresholded Image", imgThresholded);//show the thresholded image
		imshow("Original", *cv_img);		//show the original image

		waitKey(1);
		//cout << "t" << endl;

	//}
}
