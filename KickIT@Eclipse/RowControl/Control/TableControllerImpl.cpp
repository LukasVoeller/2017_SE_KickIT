#include "../DataType/CameraConfig.hpp"
#include "../Control/RowControllerMidfield.hpp"
#include "../Control/RowControllerDefense.hpp"
#include "../Control/RowControllerOffense.hpp"
#include "../Control/TableControllerImpl.hpp"
#include "../Control/RowControllerKeeper.hpp"
#include "../Calculation/Calculator.hpp"
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

	float* positions = new float[tc.isKeeperActive ? 1 : 0 + tc.isDefenseActive ? 1 : 0 + tc.isMidfieldActive ? 1 : 0 + tc.isOffenseActive ? 1 : 0];
	bool* up = new bool[tc.isDefenseActive ? 1 : 0 + tc.isMidfieldActive ? 1 : 0 + tc.isOffenseActive ? 1 : 0];
	bool* kick = new bool[tc.isDefenseActive ? 1 : 0 + tc.isMidfieldActive ? 1 : 0 + tc.isOffenseActive ? 1 : 0];

	//std::cout << "x: " << x << " y: " << y << std::endl;
	Vec2 v = this->pixelToMM(x, y);
	//std::cout << "after ptm " << "x: " << v.x << " y: " << v.y << std::endl;
	ballStatus.update(v.x, v.y);		//Ballposition from now on in milimeters

	//this->vkw->newBallStatus(ballStatus);

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
	//std::cout << "calculated: " << positions[0] << std::endl;
	if (tc.isKeeperActive) keeperControl->moveTo(positions[0]);
	if (tc.isDefenseActive) defenseControl->moveTo(positions[1]);
	if (tc.isMidfieldActive) midfieldControl->moveTo(positions[2]);
	if (tc.isOffenseActive) offenseControl->moveTo(positions[3]);

	delete(up);
	delete(positions);
	delete(kick);



}

Vec2 TableControllerImpl::pixelToMM(float xPixel, float yPixel) {

	/*std::cout << "in pixels: " << " x: " << xPixel << " y: " << yPixel << std::endl;
	std::cout << "tw: " << tc.tableWidth << std::endl;
	std::cout << "th: " << tc.tableHeight << std::endl;
	std::cout << "pw: " << cc.width << std::endl;
	std::cout << "ph: " << cc.height << std::endl;*/


	Vec2 result;

	result.x = xPixel * ((float) this->tc.tableWidth / (float) this->cc.width);
	result.y = yPixel * ((float) this->tc.tableHeight / (float) this->cc.height);

	//std::cout << "on table: " << " x: " << result.x << " y: " << result.y << std::endl;

	return result;
}

