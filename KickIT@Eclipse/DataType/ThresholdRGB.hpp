#ifndef THRESHOLDRGB_HPP_
#define THRESHOLDRGB_HPP_

#include "../DataType/CameraConfig.hpp"

class ThresholdRGB {

public:
	int redLow = cc.redLow;
	int redHigh = cc.redHigh;

	int greenLow = cc.greenLow;
	int greenHigh = cc.greenHigh;

	int blueLow = cc.blueLow;
	int blueHigh = cc.blueHigh;

private:
	CameraConfig cc;

};

#endif
