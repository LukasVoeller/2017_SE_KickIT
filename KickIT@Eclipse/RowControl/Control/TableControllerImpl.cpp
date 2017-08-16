#include "../DataType/CameraConfig.hpp"
#include "../Control/RowControllerMidfield.hpp"
#include "../Control/RowControllerDefense.hpp"
#include "../Control/RowControllerOffense.hpp"
#include "../Control/TableControllerImpl.hpp"
#include "../Control/RowControllerKeeper.hpp"
#include "../Calculation/Calculator.hpp"
#include <iostream>

TableControllerImpl::TableControllerImpl() {

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
	Vec2 v = this->pixelToMM(x, y);
	ballStatus.update(v.x, v.y);		//Ballposition form now on in milimeters

	//Check if ball is in the right position for some shots
	this->calculator.calcIfKick(&ballStatus);
	if(tc.isDefenseActive && this->calculator.kick[0]) defenseControl->kick(3);
	//if(isMidfieldActive && calc->kick[1]) midfieldControl->kick(0);
	//if(isOffenseActive && calc->kick[2]) offenseControl->kick(0);

	//Coordinate players
	this->calculator.calcPositionsSimple(&ballStatus);
	if (tc.isKeeperActive) {
		keeperControl->moveTo(calculator.positions[0]);
		//std::cout << " keeper to : " << calc->positions[0] << std::endl;
	}
	if (tc.isDefenseActive) defenseControl->moveTo(calculator.positions[1]);
	//if (tc.isMidfieldActive) midfieldControl->moveTo(calculator.positions[2]);
	//if (tc.isOffenseActive) offenseControl->moveTo(calculator.positions[3]);
	//std::cout << "keeper " << positions[0] << " defense " << positions[1] << std::endl;

	//else defenseControl->down();
}

Vec2 TableControllerImpl::pixelToMM(float xPixel, float yPixel) {
	/*std::cout << "in pixels: " << " x: " << xPixel << " y: " << yPixel << std::endl;

	std::cout << "tw: " << tc.tableWidth << std::endl;
	std::cout << "th: " << tc.tableHeight << std::endl;
	std::cout << "pw: " << cc.width << std::endl;
	std::cout << "ph: " << cc.height << std::endl;*/


	Vec2 result;

	//Geht fit Daniel?
	result.x = xPixel * ((float) this->tc.tableWidth / (float) this->cc.width);
	result.y = yPixel * ((float) this->tc.tableHeight / (float) this->cc.height);

	//std::cout << "on table: " << " x: " << result.x << " y: " << result.y << std::endl;

	return result;
}

