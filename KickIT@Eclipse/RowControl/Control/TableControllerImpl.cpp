#include "../Control/TableControllerImpl.hpp"

#include "../Control/RowControllerDefense.hpp"
#include "../Control/RowControllerKeeper.hpp"
#include "../Control/RowControllerMidfield.hpp"
#include "../Control/RowControllerOffense.hpp"
#include "../Calculation/PositionCalculator.hpp"
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
	//calc->playerGapDefense =

}

void TableControllerImpl::setBallPos(float x, float y) {
	ballStatus.position.x = x;
	ballStatus.position.y = y;
	ballStatus.movement.update(x,y);
	float* positions = calc->calcPositionsSimple(&ballStatus);

	std::cout << "keeper " << positions[0] << " defense " << positions[1] << std::endl;

	//keeperControl->moveTo(positions[0]);
	defenseControl->moveTo(positions[1]);

	delete(positions);
}

void TableControllerImpl::run() {

}

void TableControllerImpl::stop() {

}

