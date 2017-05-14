/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TableControllerInterface.hpp
 * Author: student
 *
 * Created on 13. April 2017, 15:38
 */

#ifndef TABLECONTROLLERINTERFACE_HPP
#define TABLECONTROLLERINTERFACE_HPP

#include "../DataType/BallStatus.hpp"


class TableControllerInterface{
public:
    virtual void setBallStatus(BallStatus* b){};
};


#endif /* TABLECONTROLLERINTERFACE_HPP */

