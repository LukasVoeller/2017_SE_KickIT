#include "../Control/TableControllerImpl.hpp"

#include "../Control/RowControllerDefense.hpp"
#include "../Control/RowControllerKeeper.hpp"
#include "../Control/RowControllerMidfield.hpp"
#include "../Control/RowControllerOffense.hpp"

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

}

void TableControllerImpl::setBallPos(float x, float y) {
	keeperControl->moveTo(y);
	defenseControl->moveTo(y);
}

void TableControllerImpl::run() {

}

void TableControllerImpl::stop() {

}

