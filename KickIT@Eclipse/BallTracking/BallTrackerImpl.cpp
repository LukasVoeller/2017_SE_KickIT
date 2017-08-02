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

	height->SetValue(374);
	width->SetValue(608);
	packetsize->SetValue(1500);

	/*cout << "Wollen Sie die Höhe verändern? y/n" << endl;
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
*/
	return;
}

//Menupunkt Kameraoperationen
void BallTrackerImpl::camera_settings(){
	int i = 0;

	cout << "Kameraeinstellungen" << endl;
	cout << "Was moechten Sie tun:" << endl;
	cout << "1) Schwellwerte eintellen" << endl;
	cout << "2) Kameraparameter abfragen" << endl;
	cout << "3) Kameraparameter einstellen" << endl;
	cout << "4) Start Tracking" << endl;

	cin >> i;
	switch (i) {
		case 1:
			BallTrackerImpl::threshold();
		case 2:
			BallTrackerImpl::getCameraSettings();
		break;
		case 3:
			BallTrackerImpl::setCameraSettings();
		break;
		case 4:
			BallTrackerImpl::startTracking();
		break;
		default:
			cout << "Falsche Eingabe erneut versuchen!" << endl;
		break;
	}

	return;
}


void BallTrackerImpl::threshold(){
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
				camera.RetrieveResult(5000, ptrGrabResult,
				TimeoutHandling_ThrowException);

				if (ptrGrabResult->GrabSucceeded()) {
					fc.Convert(image, ptrGrabResult);

					cv_img = cv::Mat(ptrGrabResult->GetHeight(),
						ptrGrabResult->GetWidth(), CV_8UC3,
						(uint8_t*) image.GetBuffer());
					Mat imgHSV;

				  	// cvtColor(dif, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
					Mat imgThresholded;

				   	inRange(cv_img, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
				  	//morphological opening (remove small objects from the foreground)
				   	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
				   	dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );

				    //morphological closing (fill small holes in the foreground)
					//dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
				 	//erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
				   	Mat canny_output;
				   	vector<vector<Point> > contours;

				   	vector<Vec4i> hierarchy;
				   	int thresh = 100;
				   	int max_thresh = 150;
				   	RNG rng(12345);
				   	Point2f TorwartCenter;

				  	//Detect edges using canny
				 	//Canny( imgThresholded, canny_output, thresh, thresh*2, 3 );
				  	//Find contours
					//findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
				  	//Draw contours
				   	Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
				   	for( int i = 0; i< contours.size(); i++ ){
					  	//cout << contours[i] << endl;
				   		Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
				   		drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
				   	}
				   	float radius = 5;
				 	// minEnclosingCircle(Mat(contours),TorwartCenter,radius);

				  	//Show in a window
				 	//namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
				 	//imshow( "Contours", drawing );

				   	imshow("Thresholded Image", imgThresholded);	//show the thresholded image
				  	imshow("Original", cv_img);		//show the original image
					if (waitKey(30) == 27) { 	//wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
						cout << "esc key is pressed by user" << endl;
						break;
					}
				}

			}
			cout << "test_1" << endl;
		}
	} catch (GenICam::GenericException &e) {
		// Error handling.
		cerr << "An exception occurred." << endl << e.GetDescription() << endl;
		exitCode = 1;
	}
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


