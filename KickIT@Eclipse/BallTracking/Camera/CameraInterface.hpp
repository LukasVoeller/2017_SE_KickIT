
#ifndef CameraInterface_HPP_
#define CameraInterface_HPP_

#include <pylon/PylonIncludes.h>


#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

using namespace Pylon;


class CameraInterface {

public:
	//virtual CGrabResultPtr* getImage() = 0;
	virtual ~CameraInterface(){}
private:
	virtual void calibrate() = 0;
	virtual void getCameraSettings() = 0;
	virtual void setCameraSettings() = 0;
	virtual void camera_settings() = 0;
	virtual void threshold() = 0;
};



#endif
