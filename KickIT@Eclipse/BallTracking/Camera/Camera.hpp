#ifndef BALLTRACKING_CAMERA_HPP_
#define BALLTRACKING_CAMERA_HPP_

#include "CameraInterface.hpp"

class Camera : public CameraInterface{
public:
	Camera();
	virtual ~Camera();

	CGrabResultPtr* getImage(){}

private:
	void calibrate();

};

#endif /* BALLTRACKING_CAMERA_HPP_ */
