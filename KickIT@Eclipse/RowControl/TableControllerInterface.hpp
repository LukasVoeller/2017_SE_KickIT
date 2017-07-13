

#ifndef TABLECONTROLLERINTERFACE_HPP
#define TABLECONTROLLERINTERFACE_HPP

#include "../DataType/BallStatus.hpp"
#include "../DataType/Vec2.hpp"

#include <iostream>

class TableControllerInterface{
public:
    virtual void setBallStatus(BallStatus* b) = 0;
    virtual void setBallPos(float x, float y){
    	std::cout << "TODO: algorithmus zur berechnung der Stangenpositionen" << std::endl;




    };
    virtual void run() = 0;
    virtual void stop() = 0;
};


#endif /* TABLECONTROLLERINTERFACE_HPP */

