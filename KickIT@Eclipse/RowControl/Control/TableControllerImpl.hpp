#ifndef TABLECONTROLLERIMPL_HPP
#define TABLECONTROLLERIMPL_HPP

#include "../Interface/TableControllerInterface.hpp"

class TableControllerImpl: public TableControllerInterface {

public:
	TableControllerImpl();
	void setBallPos(float x, float y);
	Vec2 pixelToMM(float xPixel, float yPixel);
};

#endif //TABLECONTROLLERIMPL_HPP

