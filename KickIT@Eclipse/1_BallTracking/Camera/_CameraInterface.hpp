/**
 * @file CameraInterface.hpp
 *
 */
#ifndef CameraInterface_HPP
#define CameraInterface_HPP

#include "../../5_DataType/CameraConfig.hpp"
#include <opencv2/core/core.hpp>
#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

using namespace Pylon;

/**CameraInterface class
 *
 */
class CameraInterface {
public:
	/**CameraInterface destructor
	 *
	 */
	virtual ~CameraInterface() {}

	/**getImage function
	 *
	 * Function retrieves a picture from the camera
	 *
	 * @return An image is returned
	 *
	 */
	virtual cv::Mat* getImage() = 0;

	/**Funktion threshold
	 *
	 * This function sets the threshold values ​​for the ball detection.
	 * These values ​​are then stored in the CameraConfig.txt
	 *
	 * @return The result of the adjustment is returned
	 */
	virtual CameraConfig* threshold() = 0;

protected:
	/**calibrate function
	 *
	 *
	 */
	virtual void calibrate() = 0;

	/**getCameraSettings
	 *
	 * function prints out the adjusted values of the camera
	 */
	virtual void getCameraSettings() = 0;

	/**setCameraSettings
	 *
	 * Function for initial configuration of the camera.
	 * The settings are fetched from the CameraConfig.txt and passed to the PylonViewerApi
	 *
	 */
	virtual void setCameraSettings() = 0;
};

#endif //CameraInterface_HPP
