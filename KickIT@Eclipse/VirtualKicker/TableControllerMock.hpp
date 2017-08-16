#ifndef TABLECONTROLLERMOCK_HPP
#define TABLECONTROLLERMOCK_HPP

#include "../RowControl/Interface/TableControllerInterface.hpp"
#include "VirtualKickerWindow.hpp"
#include "../DataType/Vec2.hpp"

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
