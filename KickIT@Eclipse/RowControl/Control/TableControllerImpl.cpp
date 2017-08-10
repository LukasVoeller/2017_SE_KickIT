#include "TableControllerImpl.hpp"
#include "RowControllerKeeper.hpp"
#include "RowControllerDefense.hpp"
#include "RowControllerMidfield.hpp"
#include "RowControllerOffense.hpp"

TableControllerImpl::TableControllerImpl(bool keeper, bool defense,
		bool midfield, bool offense) {

	this->keeperActive = keeper;
	this->defenseActive = defense;
	this->midfieldActive = midfield;
	this->offenseActive = offense;

	if (keeperActive) {
		//initiate connection to the keeper-driver
		keeperControl = new RowControllerKeeper();
	}
	if (defenseActive) {
		//initiate connection to the defense-driver
		defenseControl = new RowControllerDefense();
	}
	if (midfieldActive) {
		//initiate connection to the midfield-driver
		midfieldControl = new RowControllerMidfield();
	}
	if (offenseActive) {
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

