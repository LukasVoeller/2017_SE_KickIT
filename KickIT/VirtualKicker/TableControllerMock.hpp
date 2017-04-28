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

#include "../RowControl/TableControllerInterface.hpp"
#include "VirtualKicker.hpp"

class TableControllerMock : public TableControllerInterface{
    private:
        VirtualKicker* vk;
    public:
        
        static const int WINDOW_SIZE_X = 1000;
        static const int WINDOW_SIZE_Y = 700;
        
        
        TableControllerMock();
        
        virtual ~TableControllerMock();
};

#endif /* TABLECONTROLLERMOCK_HPP */

