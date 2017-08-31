#include "../../1_BallTracking/Camera/Camera.hpp"
#include "../../5_DataType/CameraConfig.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

Pylon::PylonAutoInitTerm autoInitTerm;

using namespace std;

Camera::Camera() {
	camera = new CInstantCamera(CTlFactory::GetInstance().CreateFirstDevice());
	camera->Open();
	this->setCameraSettings();
	camera->StartGrabbing();
}

Camera::~Camera() {

}

cv::Mat* Camera::getImage() {
	CPylonImage image;
	CImageFormatConverter fc;
	CGrabResultPtr ptrGrabResult;

	GenApi::CIntegerPtr width(camera->GetNodeMap().GetNode("Width"));
	GenApi::CIntegerPtr height(camera->GetNodeMap().GetNode("Height"));
	cv::Mat* cv_img = new cv::Mat(width->GetValue(), height->GetValue(),
			CV_8UC3);

	fc.OutputPixelFormat = PixelType_RGB8packed;

	if (camera->IsGrabbing()) {
		camera->RetrieveResult(5000, ptrGrabResult,
				TimeoutHandling_ThrowException);

		if (ptrGrabResult->GrabSucceeded()) {
			fc.Convert(image, ptrGrabResult);
			*cv_img = cv::Mat(ptrGrabResult->GetHeight(),
					ptrGrabResult->GetWidth(), CV_8UC3,
					(uint8_t*) image.GetBuffer());
		} else {
			cout << "Grab failed" << endl;
		}
	} else {
		cout << "Camera not grabbing" << endl;
	}

	return cv_img;
}

void Camera::calibrate() {
	PylonAutoInitTerm autoInitTerm;
	CGrabResultPtr ptrGrabResult;
	CImageFormatConverter fc;
	CPylonImage image;
	vector<cv::Vec3f> circles;

	fc.OutputPixelFormat = PixelType_RGB8packed;

	GenApi::CIntegerPtr width(camera->GetNodeMap().GetNode("Width"));
	GenApi::CIntegerPtr height(camera->GetNodeMap().GetNode("Height"));
	cv::Mat cv_img(width->GetValue(), height->GetValue(), CV_8UC3);

	for (int i = 0; i < 5; i++) {
		while (camera->IsGrabbing()) {
			camera->RetrieveResult(5000, ptrGrabResult,
					TimeoutHandling_ThrowException);

			if (ptrGrabResult->GrabSucceeded()) {
				cout << "Grabbing succeeded" << endl;

				fc.Convert(image, ptrGrabResult);
				cv_img = cv::Mat(ptrGrabResult->GetHeight(),
						ptrGrabResult->GetWidth(), CV_8UC3,
						(uint8_t*) image.GetBuffer());
				imshow("circles", cv_img);

				cv::waitKey(1);
			}
		}
	}
}

void Camera::setCameraSettings() {
	cout << "Using device: " << camera->GetDeviceInfo().GetModelName() << endl;
	PylonAutoInitTerm autoInitTerm;
	CGrabResultPtr ptrGrabResult;
	CameraConfig cc;

	GenApi::CIntegerPtr width(camera->GetNodeMap().GetNode("Width"));
	GenApi::CIntegerPtr height(camera->GetNodeMap().GetNode("Height"));
	GenApi::CIntegerPtr packetsize(
			camera->GetNodeMap().GetNode("GevSCPSPacketSize"));
	GenApi::CFloatPtr exposuretime(
			camera->GetNodeMap().GetNode("ExposureTimeAbs"));
	GenApi::CIntegerPtr offsetx(camera->GetNodeMap().GetNode("OffsetX"));
	GenApi::CIntegerPtr offsety(camera->GetNodeMap().GetNode("OffsetY"));

	width->SetValue(cc.width);
	height->SetValue(cc.height);
	packetsize->SetValue(cc.packetsize);
	exposuretime->SetValue(cc.exposureTime);
	offsetx->SetValue(cc.offsetx);
	offsety->SetValue(cc.offsety);
	cout << "Kammeraeinstellungen vorgenommen" << endl;
}

void Camera::getCameraSettings() {
	cout << "Using camera: " << camera->GetDeviceInfo().GetModelName() << endl;

	GenApi::CIntegerPtr width(camera->GetNodeMap().GetNode("Width"));
	GenApi::CIntegerPtr height(camera->GetNodeMap().GetNode("Height"));
	GenApi::CIntegerPtr packetsize(
			camera->GetNodeMap().GetNode("GevSCPSPacketSize"));
	GenApi::CFloatPtr exposuretime(
			camera->GetNodeMap().GetNode("ExposureTimeAbs"));

	cout << "Aktuelle Kameraparameter: " << endl;
	cout << "Höhe: " << width->GetValue() << endl;
	cout << "Weite: " << height->GetValue() << endl;
	cout << "Packetsize: " << packetsize->GetValue() << endl;
	cout << "Belichtungszeit: " << exposuretime->GetValue() << endl << endl;
}

CameraConfig* Camera::threshold() {
	CameraConfig* result = new CameraConfig();
	CGrabResultPtr ptrGrabResult;
	bool movedThresholded = false;
	bool movedOriginal = false;

	cv::namedWindow("Control", CV_WINDOW_NORMAL); //Create a window called "Control"
	cv::moveWindow("Control", 800, 10);

	cvCreateTrackbar("LowB", "Control", &(result->blueLow), 255); //Hue (0 - 179)
	cvCreateTrackbar("HighB", "Control", &(result->blueHigh), 255);

	cvCreateTrackbar("LowG", "Control", &(result->greenLow), 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighG", "Control", &(result->greenHigh), 255);

	cvCreateTrackbar("LowR", "Control", &(result->redLow), 255); //Value (0 - 255)
	cvCreateTrackbar("HighR", "Control", &result->redHigh, 255);

	while (1) {
		cv::Mat* cv_img = this->getImage();
		cv::Mat imgHSV;
		cv::Mat imgThresholded;
		imshow("Original", *cv_img);		//Show the original image

		try {
			cv::inRange(*cv_img,
					cv::Scalar(result->blueLow, result->greenLow,
							result->redLow),
					cv::Scalar(result->blueHigh, result->greenHigh,
							result->redHigh), imgThresholded);
			cv::erode(imgThresholded, imgThresholded,
					cv::getStructuringElement(cv::MORPH_ELLIPSE,
							cv::Size(15, 15)));
			cv::dilate(imgThresholded, imgThresholded,
					cv::getStructuringElement(cv::MORPH_ELLIPSE,
							cv::Size(15, 15)));

		} catch (cv::Exception& e) {
			const char* err_msg = e.what();
			std::cout << "Exception caught: " << err_msg << std::endl;
		}

		//Draw contours
		imshow("Thresholded Image", imgThresholded);//show the thresholded image

		if (!movedOriginal) {
			cv::moveWindow("Original", 100, 100);
			movedOriginal = true;
		}
		if (!movedThresholded) {
			cv::moveWindow("Thresholded Image", 200, 500);
			movedThresholded = true;
		}

		delete (cv_img);

		if (cv::waitKey(30) == 27) {
			cv::destroyWindow("Thresholded Image");
			cv::destroyWindow("Original");
			cv::destroyWindow("Control");
			break;
		}
	}

	result->saveConfig();

	return result;
}
