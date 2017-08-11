#ifndef BALLTRACKING_CAMERA_HPP_
#define BALLTRACKING_CAMERA_HPP_

#include "CameraInterface.hpp"
#include <opencv2/core/core.hpp>

class Camera: public CameraInterface {
public:
	Camera();
	virtual ~Camera();
	cv::Mat* getImage();
	void threshold();

protected:
	void calibrate();
	void getCameraSettings();
	void setCameraSettings();
	void cameraSettings();

	CInstantCamera camera;

};

#endif /* BALLTRACKING_CAMERA_HPP_ */
