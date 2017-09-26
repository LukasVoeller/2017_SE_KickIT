/**
 * @file Camera.hpp
 * @brief
 */
#ifndef BALLTRACKING_CAMERA_HPP_
#define BALLTRACKING_CAMERA_HPP_

#include <opencv2/core/core.hpp>
#include "_CameraInterface.hpp"

/**CammeraInterface class
 *
 */
class Camera: public CameraInterface {
public:
	/**Camera constructor
	 *
	 */
	Camera();

	/**Camera destructor
	 *
	 */
	virtual ~Camera();

	cv::Mat* getImage();

	CameraConfig* threshold();

protected:
	void calibrate();
	void getCameraSettings();
	void setCameraSettings();

	CInstantCamera* camera;
};

#endif //BALLTRACKING_CAMERA_HPP_
