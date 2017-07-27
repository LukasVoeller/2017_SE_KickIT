#ifndef BALLTRACKERINTERFACE_HPP_
#define BALLTRACKERINTERFACE_HPP_

#include "../DataType/BallStatus.hpp"
#include "../RowControl/InterfaceTableController.hpp"
#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class BallTrackerInterface {
public:
	virtual BallStatus* getBallStatus() = 0;
	virtual void startTracking() = 0;
	virtual void stopTracking() = 0;
	virtual void setTableController(InterfaceTableController* t) = 0;
	virtual ~BallTrackerInterface();
};

#endif /* BALLTRACKER_HPP_ */
