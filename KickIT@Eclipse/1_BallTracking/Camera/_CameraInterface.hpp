/**
 * @file CameraInterface.hpp
 * @brief
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

	/**Mat* getImage function
	 *
	 */
	virtual cv::Mat* getImage() = 0;

	/**threshold
	 *
	 */
	virtual CameraConfig* threshold() = 0;

protected:
	/**calibrate function
	 * wird nicht verwendet
	 *
	 */
	virtual void calibrate() = 0;

	/**getCameraSettings
	 *
	 */
	virtual void getCameraSettings() = 0;

	/**setCameraSettings
	 *
	 */
	virtual void setCameraSettings() = 0;
};

#endif //CameraInterface_HPP
