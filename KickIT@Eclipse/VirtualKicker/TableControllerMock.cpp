#include "TableControllerMock.hpp"
#include <iostream>

TableControllerMock::TableControllerMock(bool keeper, bool defense,
		bool midfield, bool offense) :
		window(NULL) {

	isKeeperActive = keeper;
	isDefenseActive = defense;
	isMidfieldActive = midfield;
	isOffenseActive = offense;
}

TableControllerMock::~TableControllerMock() {

}

void TableControllerMock::run() {

}

void TableControllerMock::stop() {

}

void TableControllerMock::setBallPos(float x, float y) {
	updateBallStatus(x, y);

	float* positions = calculateRowPositions(window->TABLE_HEIGHT, &ballStatus,
			isKeeperActive, isDefenseActive, isMidfieldActive, isOffenseActive,
			window->TABLE_MARGIN, window->getDDist(), 0, 0,
			window->getKeeperPositionalVector());

	if (isKeeperActive) {
		window->setKeeper(positions[0]);
	}

	if (isDefenseActive) {
		window->setDefense(positions[1]);
	}

	delete positions;
}

void TableControllerMock::setKickerWindow(VirtualKickerWindow* p) {
	window = p;
}
