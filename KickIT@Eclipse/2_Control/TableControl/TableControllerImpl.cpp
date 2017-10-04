/**
 * @file TableControllerImpl.cpp
 * @brief
 */

#include "TableControllerImpl.hpp"
#include "../../4_Utilities/Calculator.hpp"
#include "../../2_Control/RowControl/RowControllerDefense.hpp"
#include "../../2_Control/RowControl/RowControllerKeeper.hpp"
#include "../../2_Control/RowControl/RowControllerMidfield.hpp"
#include "../../2_Control/RowControl/RowControllerOffense.hpp"
#include "../../5_DataType/CameraConfig.hpp"
#include <iostream>

TableControllerImpl::TableControllerImpl(VirtualKickerWindow* v):vkw(v) {
	if (tc.isKeeperActive) {
		//initiate connection to the keeper-driver
		keeperControl = new RowControllerKeeper();
	}
	if (tc.isDefenseActive) {
		//initiate connection to the defense-driver
		defenseControl = new RowControllerDefense();
	}
	if (tc.isMidfieldActive) {
		//initiate connection to the midfield-driver
		midfieldControl = new RowControllerMidfield();
	}
	if (tc.isOffenseActive) {
		//initiate connection to the offense-driver
		offenseControl = new RowControllerOffense();
	}
}

void TableControllerImpl::setBallPos(float x, float y) {
	float* positions = new float[4];
	bool* up = new bool[3];
	bool* kick = new bool[3];

	Vec2 v = this->pixelToMM(x, y);
	ballStatus.update(v.x, v.y);		//Ballposition from now on in milimeters

	vkw->newBallStatus(ballStatus);

	//Check if ball is in the right position for some shots
	std::vector<void*> calcParams;
	calcParams.push_back(&ballStatus);
	calcParams.push_back(positions);
	calcParams.push_back(up);
	calcParams.push_back(kick);

	Modules::instance()->execute("calcIfKick", &calcParams);
	if(tc.isDefenseActive && kick[0]) defenseControl->kick(3);
	if(tc.isMidfieldActive && kick[1]) midfieldControl->kick(3);
	if(tc.isOffenseActive && kick[2]) offenseControl->kick(3);

	//Coordinate players
	Modules::instance()->execute("calcPositions", &calcParams);
	if (tc.isKeeperActive) keeperControl->moveTo(positions[0]);
	if (tc.isDefenseActive) defenseControl->moveTo(positions[1]);
	if (tc.isMidfieldActive) midfieldControl->moveTo(positions[2]);
	if (tc.isOffenseActive) offenseControl->moveTo(positions[3]);

	delete(up);
	delete(positions);
	delete(kick);
}

Vec2 TableControllerImpl::pixelToMM(float xPixel, float yPixel) {
	Vec2 result;

	result.x = xPixel * ((float) this->tc.tableWidth / (float) this->cc.width);
	result.y = yPixel * ((float) this->tc.tableHeight / (float) this->cc.height);

	return result;
}
