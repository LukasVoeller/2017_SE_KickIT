#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>

#ifdef PYLON_WIN_BUILD
#    include <pylon/PylonGUI.h>
#endif

using namespace cv;
using namespace std;
using namespace Pylon;


 int main( int argc, char** argv )
 {

	 int count = 0;

	 namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	  int iLowH = 0; // 0
	 int iHighH = 255;// 179

	  int iLowS = 0;// 0
	 int iHighS = 255; //255

	  int iLowV = 0; // 0
	 int iHighV =  255; //255

	  //Create trackbars in "Control" window
	 cvCreateTrackbar("LowB", "Control", &iLowH, 255); //Hue (0 - 179)
	 cvCreateTrackbar("HighB", "Control", &iHighH, 255);

	  cvCreateTrackbar("LowG", "Control", &iLowS, 255); //Saturation (0 - 255)
	 cvCreateTrackbar("HighG", "Control", &iHighS, 255);

	  cvCreateTrackbar("LowR", "Control", &iLowV, 255); //Value (0 - 255)
	 cvCreateTrackbar("HighR", "Control", &iHighV, 255);

		int exitCode = 0;
		Pylon::PylonAutoInitTerm autoInitTerm;
		CGrabResultPtr ptrGrabResult;
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

  /// Detect edges using canny
 // Canny( imgThresholded, canny_output, thresh, thresh*2, 3 );
  /// Find contours
//  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
	  //cout << contours[i] << endl;
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }
  float radius = 5;
 // minEnclosingCircle(Mat(contours),TorwartCenter,radius);

  /// Show in a window
 // namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
 // imshow( "Contours", drawing );

   imshow("Thresholded Image", imgThresholded); //show the thresholded image
  imshow("Original", cv_img); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break;
       }
    }
				}
			}
		}
	catch (GenICam::GenericException &e) {
	// Error handling.
	cerr << "An exception occurred." << endl << e.GetDescription() << endl;
	exitCode = 1;
					}
   return 0;

}
