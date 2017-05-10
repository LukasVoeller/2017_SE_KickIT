/* 
 * File:   TableControllerMock.hpp
 * Author: student
 *
 * Created on 28. April 2017, 17:04
 */

#ifndef TABLECONTROLLERMOCK_HPP
#define TABLECONTROLLERMOCK_HPP

#include "TableControllerInterface.hpp"
#include "VirtualKickerWindow.hpp"

class TableControllerMock: public TableControllerInterface {
private:
	VirtualKickerWindow* window;
public:
	TableControllerMock(VirtualKickerWindow* w);

	TableControllerMock();

	virtual ~TableControllerMock();
};

#endif /* TABLECONTROLLERMOCK_HPP */

