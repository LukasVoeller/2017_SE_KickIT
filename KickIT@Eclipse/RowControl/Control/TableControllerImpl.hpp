#ifndef TABLECONTROLLERIMPL_HPP
#define TABLECONTROLLERIMPL_HPP

#include "../Interface/TableControllerInterface.hpp"
#include "../../VirtualKicker/VirtualKickerWindow.hpp"

class TableControllerImpl: public TableControllerInterface {

public:
	TableControllerImpl(VirtualKickerWindow* vkw);
	void setBallPos(float x, float y);
	Vec2 pixelToMM(float xPixel, float yPixel);
protected:
	VirtualKickerWindow* vkw;
};

#endif //TABLECONTROLLERIMPL_HPP

