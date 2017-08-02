/*
 * Camera.cpp
 *
 *  Created on: Aug 2, 2017
 *      Author: student
 */

#include "Camera.hpp"
#include <thread>

Camera::Camera() {

	std::cout << "camera" << std::endl;
	std::thread c(&Camera::calibrate, this);
	c.join();

}

Camera::~Camera() {

}

void Camera::calibrate(){

	std::cout << "thread" << std::endl;



}
