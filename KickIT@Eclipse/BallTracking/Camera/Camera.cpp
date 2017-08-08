#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <pylon/PylonIncludes.h>
#include <thread>

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "Camera.hpp"

#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

// Settings for using  Basler USB cameras.
#include <pylon/usb/BaslerUsbInstantCamera.h>
#define _CRT_SECURE_NO_WARNINGS



using namespace cv;
using namespace std;
using namespace Pylon;
using namespace GenApi;


Camera::Camera() {
	cout << "Camera Constructor" << std::endl;
	//thread c(&Camera::calibrate, this);
	//c.join();

	//calibrate();
	Camera::setCameraSettings();
	Camera::getCameraSettings();
	//Camera::threshold();
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

	CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
	CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));

	Mat cv_img(width->GetValue(), height->GetValue(), CV_8UC3);

	camera.StartGrabbing();

	for (int i = 0; i < 5; i++) {
		cout << i << endl;
		while (camera.IsGrabbing()) {

			camera.RetrieveResult(5000, ptrGrabResult,
					TimeoutHandling_ThrowException);

			if (ptrGrabResult->GrabSucceeded()) {
				cout << "success" << endl;
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
	cout << "Using device: " << camera.GetDeviceInfo().GetModelName() << endl;
	camera.Open();

	//INodeMap* pNodeMap = camera->GetNodeMap();

	CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
	CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
	CIntegerPtr packetsize(camera.GetNodeMap().GetNode("GevSCPSPacketSize"));
	//CFloatPtr exposuretime(camera.GetNodeMap().GetNode("ExposureTimeAbs"));
	CFloatPtr exposuretimeLowerLimit(camera.GetNodeMap().GetNode("AutoExposureTimeAbsLowerLimit"));
	CFloatPtr exposuretimeUpperLimit(camera.GetNodeMap().GetNode("AutoExposureTimeAbsUpperLimit"));
	CIntegerPtr exposuretimeTargetValue(camera.GetNodeMap().GetNode("AutoTargetValue"));
	CIntegerPtr exposuretimeAuto(camera.GetNodeMap().GetNode("ExposureAuto"));
/*
	CEnumerationPtr ptrExposureAuto = nodeMap.GetNode("ExposureAuto");


	CEnumEntryPtr ptrAutoXControlExposureTimePriority = ptrAutoXControlPriority->GetEntryByName(“ExposureTimePriority”);

	camera.AutoExposureTimeLowerLimit.SetValue(camera.AutoExposureTimeLowerLimit.GetMin());
	camera.AutoExposureTimeUpperLimit.SetValue(camera.AutoExposureTimeUpperLimit.GetMax());
	//Set the target average gray value to 60% of the maximum gray value
	camera.AutoTargetBrightness.SetValue(0.6);
	// Enable Exposure Auto by setting the operation mode to Continuous
	camera.ExposureAuto.SetValue(ExposureAuto_Continuous);
*/
	//exposuretime->GetMin();
	//exposuretime->GetMax();
	exposuretimeLowerLimit->SetValue(1000.0);
	exposuretimeUpperLimit->SetValue(1.0E6);
	exposuretimeTargetValue->SetValue(128);
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
	cout << "Using device: " << camera.GetDeviceInfo().GetModelName() << endl;
	camera.Open();

	CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
	CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
	CIntegerPtr packetsize(camera.GetNodeMap().GetNode("GevSCPSPacketSize"));
	CFloatPtr exposuretime(camera.GetNodeMap().GetNode("ExposureTimeAbs"));

	cout << "Aktuelle Kammeraparameter: " << endl;
	camera.GetNodeMap().GetNode("Height");
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
	int exitCode = 0;
	//PylonAutoInitTerm autoInitTerm;
	CGrabResultPtr ptrGrabResult;

	int count = 0;

		namedWindow("Control", CV_WINDOW_AUTOSIZE); //Create a window called "Control"
		int iLowH = 0;		//0
		int iHighH = 255;	//179

		int iLowS = 0;		//0
		int iHighS = 255; 	//255

		int iLowV = 0; 		//0
		int iHighV =  255; 	//255

		//Create trackbars in "Control" window
		cvCreateTrackbar("LowB", "Control", &iLowH, 255); //Hue (0 - 179)
		cvCreateTrackbar("HighB", "Control", &iHighH, 255);

		cvCreateTrackbar("LowG", "Control", &iLowS, 255); //Saturation (0 - 255)
		cvCreateTrackbar("HighG", "Control", &iHighS, 255);

		cvCreateTrackbar("LowR", "Control", &iLowV, 255); //Value (0 - 255)
		cvCreateTrackbar("HighR", "Control", &iHighV, 255);

		try {
			CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
			cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
			camera.Open();

			GenApi::CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
			GenApi::CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
			Mat cv_img(width->GetValue(), height->GetValue(), CV_8UC3);

			camera.StartGrabbing();
			CPylonImage image;
			CImageFormatConverter fc;
			fc.OutputPixelFormat = PixelType_RGB8packed;
			while (1) {
				while (camera.IsGrabbing()) {
					camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

					if (ptrGrabResult->GrabSucceeded()) {
						fc.Convert(image, ptrGrabResult);
						cv_img = Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t*) image.GetBuffer());
						Mat imgHSV;
						Mat imgThresholded;

					   	inRange(cv_img, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
					   	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
					   	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );

					  	//Draw contours
					   	imshow("Thresholded Image", imgThresholded);	//show the thresholded image
					  	imshow("Original", cv_img);		//show the original image
					  	waitKey(1);
						if (waitKey(30) == 27) { 	//wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
							//cout << "esc key is pressed by user" << endl;
							//break;
							camera.StopGrabbing();
						}
					}
				}
			}
		} catch (GenICam::GenericException &e) {
			//Error handling.
			cerr << "An exception occurred." << endl << e.GetDescription() << endl;
			exitCode = 1;
		}
		// Comment the following two lines to disable waiting on exit
		//cerr << endl << "Press Enter to exit." << endl;
		//while( cin.get() != '\n');
}
