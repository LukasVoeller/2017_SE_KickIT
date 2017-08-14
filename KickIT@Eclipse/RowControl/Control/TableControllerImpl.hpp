#ifndef TABLECONTROLLERIMPL_HPP
#define TABLECONTROLLERIMPL_HPP

#include "../Interface/TableControllerInterface.hpp"

class TableControllerImpl: public TableControllerInterface {

public:
	TableControllerImpl(bool keeper, bool defense, bool midfield, bool offense);
	void setBallPos(float x, float y);
	Vec2* pixelToMM(int xPixel, int yPixel);
};

#endif /* TABLECONTROLLERIMPL_HPP */

