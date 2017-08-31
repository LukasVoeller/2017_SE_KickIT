#ifndef BALLTRACKING_CAMERA_HPP_
#define BALLTRACKING_CAMERA_HPP_

#include <opencv2/core/core.hpp>

#include "_CameraInterface.hpp"

class Camera: public CameraInterface {
public:
	Camera();
	virtual ~Camera();
	cv::Mat* getImage();
	CameraConfig* threshold();

protected:
	void calibrate();
	void getCameraSettings();
	void setCameraSettings();
	void cameraSettings();

	CInstantCamera* camera;
};

#endif //BALLTRACKING_CAMERA_HPP_
