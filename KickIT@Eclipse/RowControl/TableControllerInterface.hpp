

#ifndef TABLECONTROLLERINTERFACE_HPP
#define TABLECONTROLLERINTERFACE_HPP

#include "../DataType/BallStatus.hpp"
#include "../DataType/Vec2.hpp"

#include <iostream>

class TableControllerInterface{
public:
    virtual void setBallPos(float x, float y) = 0;
    virtual void run() = 0;
    virtual void stop() = 0;
};


#endif /* TABLECONTROLLERINTERFACE_HPP */

