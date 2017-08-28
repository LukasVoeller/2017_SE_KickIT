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
	ballStatus.update(v.x, v.y);		//Ballposition from now on in milimeters

	//Check if ball is in the right position for some shots
	std::vector<void*> calcParams;
	calcParams.push_back(&ballStatus);

	m.execute("calcIfKick", &calcParams);
	if(tc.isDefenseActive && Calculator::kick[0]) defenseControl->kick(3);
	if(tc.isMidfieldActive && Calculator::kick[1]) midfieldControl->kick(3);
	if(tc.isOffenseActive && Calculator::kick[2]) offenseControl->kick(3);

	//Coordinate players
	m.execute("calcPositions", &calcParams);
	if (tc.isKeeperActive) keeperControl->moveTo(Calculator::positions[0]);
	if (tc.isDefenseActive) defenseControl->moveTo(Calculator::positions[1]);
	if (tc.isMidfieldActive) midfieldControl->moveTo(Calculator::positions[2]);
	if (tc.isOffenseActive) offenseControl->moveTo(Calculator::positions[3]);


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

