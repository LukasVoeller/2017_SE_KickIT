#ifndef BALLTRACKING_CAMERA_HPP_
#define BALLTRACKING_CAMERA_HPP_

#include "CameraInterface.hpp"

class Camera: public CameraInterface {
public:
	Camera();
	virtual ~Camera();
	//CGrabResultPtr* getImage(){}

private:
	void calibrate();
	void getCameraSettings();
	void setCameraSettings();
	void cameraSettings();
	void threshold();
};

#endif /* BALLTRACKING_CAMERA_HPP_ */
