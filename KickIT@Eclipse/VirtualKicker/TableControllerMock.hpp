/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TableControllerMock.hpp
 * Author: student
 *
 * Created on 28. April 2017, 17:04
 */

#ifndef TABLECONTROLLERMOCK_HPP
#define TABLECONTROLLERMOCK_HPP

#include "../RowControl/InterfaceTableController.hpp"
#include "VirtualKickerWindow.hpp"
#include "../DataType/Vec2.hpp"


class TableControllerMock : public InterfaceTableController{
    private:
        VirtualKickerWindow* window;
    public:
        
        TableControllerMock(bool keeper, bool defense, bool midfield, bool offense);
        
        virtual ~TableControllerMock();
        
        void setBallPos(float x, float y);

        void run(){};
        void stop(){};

        void setKickerWindow(VirtualKickerWindow* p);
};

#endif /* TABLECONTROLLERMOCK_HPP */

