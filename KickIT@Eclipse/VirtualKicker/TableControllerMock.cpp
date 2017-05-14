
#include "TableControllerMock.hpp"

TableControllerMock::TableControllerMock() {
    
    

}

TableControllerMock::TableControllerMock(VirtualKickerWindow* w){
    this->window = w;
}



TableControllerMock::~TableControllerMock() {
}

void TableControllerMock::setBallSatus(BallStatus* b){
    window->setKeeper(b->position.x);
}

