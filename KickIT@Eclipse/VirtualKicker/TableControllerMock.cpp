
#include "TableControllerMock.hpp"

TableControllerMock::TableControllerMock() {
    
    

}

TableControllerMock::TableControllerMock(VirtualKickerWindow* w){
    this->window = w;
}



TableControllerMock::~TableControllerMock() {
}

void TableControllerMock::setBallStatus(BallStatus* b){

    window->setKeeper(b->position.y);

}

void TableControllerMock::setKickerWindow(VirtualKickerWindow* p){
	window = p;
}
