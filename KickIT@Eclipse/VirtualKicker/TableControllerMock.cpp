
#include "TableControllerMock.hpp"
#include <iostream>

TableControllerMock::TableControllerMock(bool keeper, bool defense, bool midfield, bool offense):window(NULL) {
	keeperActive = keeper;
	defenseActive = defense;
	midfieldActive = midfield;
	offenseActive = offense;
}

TableControllerMock::~TableControllerMock() {
}

void TableControllerMock::setBallPos(float x, float y){

	updateBallStatus(x,y);

    float* positions = calculateRowPositions(window->TABLE_HEIGHT,&ballStatus, keeperActive, defenseActive, midfieldActive, offenseActive,
    		window->TABLE_MARGIN, window->getDDist());
	if(keeperActive) window->setKeeper(positions[0]);
	if(defenseActive) window->setDefense(positions[1]);
    delete positions;

}

void TableControllerMock::setKickerWindow(VirtualKickerWindow* p){
	window = p;
}
