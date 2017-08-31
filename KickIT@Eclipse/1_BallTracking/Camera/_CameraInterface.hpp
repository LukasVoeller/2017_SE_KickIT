#ifndef CameraInterface_HPP
#define CameraInterface_HPP

#include "../../5_DataType/CameraConfig.hpp"
#include <opencv2/core/core.hpp>
#include <pylon/PylonIncludes.h>

#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

using namespace Pylon;

class CameraInterface {
public:
	virtual ~CameraInterface() {}
	virtual cv::Mat* getImage() = 0;
	virtual CameraConfig* threshold() = 0;

protected:
	virtual void calibrate() = 0;
	virtual void getCameraSettings() = 0;
	virtual void setCameraSettings() = 0;
};

#endif //CameraInterface_HPP
