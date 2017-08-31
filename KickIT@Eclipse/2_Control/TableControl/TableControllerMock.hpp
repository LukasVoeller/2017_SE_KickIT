#ifndef TABLECONTROLLERMOCK_HPP
#define TABLECONTROLLERMOCK_HPP

#include "../3_VirtualKicker/VirtualKickerWindow.hpp"
#include "../5_DataType/Vec2.hpp"
#include "../2_Control/TableControl/_TableControllerInterface.hpp"

class TableControllerMock: public TableControllerInterface {

public:
	TableControllerMock();
	virtual ~TableControllerMock();

	void run();
	void stop();
	void setBallPos(float x, float y);
	void setKickerWindow(VirtualKickerWindow* p);

protected:
	virtual Vec2 pixelToMM(float xPixel, float yPixel){}
	VirtualKickerWindow* window;
};

#endif //TABLECONTROLLERMOCK_HPP
