
#include "TableControllerMock.hpp"

TableControllerMock::TableControllerMock() {
    
    vk = new VirtualKicker();
    
    vk->setFixedSize(WINDOW_SIZE_X,WINDOW_SIZE_Y);
    vk->show();

}



TableControllerMock::~TableControllerMock() {
}

