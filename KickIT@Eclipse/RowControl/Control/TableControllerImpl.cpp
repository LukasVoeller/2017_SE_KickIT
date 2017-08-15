#include "../DataType/CameraConfig.hpp"
#include "../Control/RowControllerMidfield.hpp"
#include "../Control/RowControllerDefense.hpp"
#include "../Control/RowControllerOffense.hpp"
#include "../Control/TableControllerImpl.hpp"
#include "../Control/RowControllerKeeper.hpp"
#include "../Calculation/Calculator.hpp"
#include <iostream>

TableControllerImpl::TableControllerImpl(bool keeper, bool defense,
		bool midfield, bool offense) {
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

	this->tableHeight = 680;
	this->tableWidth = 1115;
	this->calc = new Calculator();
}

void TableControllerImpl::setBallPos(float x, float y) {
	Vec2* v = this->pixelToMM(x, y);
	ballStatus.update(v->x, v->y);
	delete (v);

	//Check if pall is in the right position for a shot
	//calc->calcIfKick(&ballStatus);
	//if(isDefenseActive && calc->kick[0]) defenseControl->kick(0);
	//if(isMidfieldActive && calc->kick[1]) midfieldControl->kick(0);
	//if(isOffenseActive && calc->kick[2]) offenseControl->kick(0);

	//Coordinate players
	calc->calcPositionsSimple(&ballStatus);
	if (isKeeperActive) {
		keeperControl->moveTo(calc->positions[0]);
		std::cout << " keeper to : " << calc->positions[0] << std::endl;
	}
	if (isDefenseActive)
		defenseControl->moveTo(calc->positions[1]);
	if (isMidfieldActive)
		midfieldControl->moveTo(calc->positions[2]);
	if (isOffenseActive)
		offenseControl->moveTo(calc->positions[3]);
	//std::cout << "keeper " << positions[0] << " defense " << positions[1] << std::endl;

	//if(up[0]) defenseControl->up();
	//else defenseControl->down();
}

Vec2* TableControllerImpl::pixelToMM(int xPixel, int yPixel) {
	//std::cout << "in pixels: " << " x: " << xPixel << " y: " << yPixel << std::endl;
	Vec2* result = new Vec2();
	CameraConfig cc;

	result->x = (float) xPixel * ((float) this->tableWidth / (float) cc.width);
	result->y = (float) yPixel
			* ((float) this->tableHeight / (float) cc.height);

	//std::cout << "on table: " << " x: " << result->x << " y: " << result->y << std::endl;

	return result;
}

