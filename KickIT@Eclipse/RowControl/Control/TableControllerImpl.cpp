#include "../Control/TableControllerImpl.hpp"

#include "../Control/RowControllerDefense.hpp"
#include "../Control/RowControllerKeeper.hpp"
#include "../Control/RowControllerMidfield.hpp"
#include "../Control/RowControllerOffense.hpp"
#include "../Calculation/PositionCalculator.hpp"
#include "../../BallTracking/Camera/CameraConfig.hpp"
#include <iostream>

TableControllerImpl::TableControllerImpl(bool keeper, bool defense, bool midfield, bool offense) {

	this->isKeeperActive = keeper;
	this->isDefenseActive = defense;
	this->isMidfieldActive = midfield;
	this->isOffenseActive = offense;

	if (isKeeperActive) {
		//initiate connection to the keeper-driver
		keeperControl = new RowControllerKeeper();
	}
	if (isDefenseActive) {
		//initiate connection to the defense-driver
		defenseControl = new RowControllerDefense();
	}
	if (isMidfieldActive) {
		//initiate connection to the midfield-driver
		midfieldControl = new RowControllerMidfield();
	}
	if (isOffenseActive) {
		//initiate connection to the offense-driver
		offenseControl = new RowControllerOffense();
	}

	this->calc = new PositionCalculator();
	this->calc->isKeeperActive = keeper;
	this->calc->isDefenseActive = defense;
	this->calc->isMidfieldActive = midfield;
	this->calc->isOffenseActive = offense;

	this->tableHeight = 680;
	this->tableWidth = 1115;

	//Calculator Config

	calc->playerGapDefense = 230;
	calc->tableHeight = 680;
	calc->offsetTopSideDefense = 72.72;
	calc->offsetBottomSideDefense = 298.182;
	calc->offsetTopSideKeeper = 327.273;

}

void TableControllerImpl::setBallPos(float x, float y) {

	Vec2* v = this->pixelToMM(x,y);

	ballStatus.position.x = v->x;
	ballStatus.position.y = v->y;
	ballStatus.movement.update(v->x,v->y);
	delete(v);

	float* positions = calc->calcPositionsSimple(&ballStatus);

	//std::cout << "keeper " << positions[0] << " defense " << positions[1] << std::endl;

	keeperControl->moveTo(positions[0]);
	defenseControl->moveTo(positions[1]);

	delete(positions);
}

Vec2* TableControllerImpl::pixelToMM(int xPixel, int yPixel){
	//std::cout << "in pixels: " << " x: " << xPixel << " y: " << yPixel << std::endl;
	Vec2* result = new Vec2();
	CameraConfig cc;

	result->x = (float)xPixel * ((float)this->tableWidth / (float)cc.width);
	result->y = (float)yPixel * ((float)this->tableHeight / (float)cc.height);

	//std::cout << "on table: " << " x: " << result->x << " y: " << result->y << std::endl;

	return result;
}

