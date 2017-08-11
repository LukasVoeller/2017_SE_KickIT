#ifndef CameraInterface_HPP_
#define CameraInterface_HPP_

#include <opencv2/core/core.hpp>
#include <pylon/PylonIncludes.h>

#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

using namespace Pylon;

class CameraInterface {
public:
	//virtual CGrabResultPtr* getImage() = 0;
	virtual ~CameraInterface(){}
	virtual cv::Mat* getImage() = 0;
	virtual void threshold() = 0;

protected:
	//Eventuell {} Schreibweise?
	virtual void calibrate() = 0;
	virtual void getCameraSettings() = 0;
	virtual void setCameraSettings() = 0;
	virtual void cameraSettings() = 0;


};

#endif
