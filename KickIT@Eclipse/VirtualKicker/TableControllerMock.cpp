
#include "TableControllerMock.hpp"
#include <iostream>

TableControllerMock::TableControllerMock() {
    
    

}

TableControllerMock::TableControllerMock(VirtualKickerWindow* w){
    this->window = w;
}



TableControllerMock::~TableControllerMock() {
}

void TableControllerMock::setBallPos(float x, float y){
	std::cout << "pos update";
    window->setKeeper(y);

}

void TableControllerMock::setKickerWindow(VirtualKickerWindow* p){
	window = p;
}
