/**
 * @file TableControllerMock.cpp
 * @brief
 */

#include "TableControllerMock.hpp"
#include <iostream>

TableControllerMock::TableControllerMock() : window(NULL) {

}

TableControllerMock::~TableControllerMock() {

}

void TableControllerMock::run() {

}

void TableControllerMock::stop() {

}

void TableControllerMock::setBallPos(float x, float y) {

}

void TableControllerMock::setKickerWindow(VirtualKickerWindow* p) {
	window = p;
}
