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

	/**getImage function
	 *Function retrieves a picture from the camera
	 * @return An image is returned
	 *
	 */
	cv::Mat* getImage();

	/**Funktion threshold
	 * This function sets the threshold values ​​for the ball detection.
	 * These values ​​are then stored in the CameraConfig.txt
	 * @return The result of the adjustment is returned with the variable result
	 */
	CameraConfig* threshold();

protected:
	void calibrate();
	/**gerCameraSettings
	 * function gives the adjusted values of the camera
	 */
	void getCameraSettings();
	/**setCameraSettings
	 * Function for initial configuration of the camera
	 * The settings are fetched from the CameraConfig.txt and passed to the PylonViewerApi
	 *
	 */
	void setCameraSettings();

	CInstantCamera* camera;
};

#endif //BALLTRACKING_CAMERA_HPP_
