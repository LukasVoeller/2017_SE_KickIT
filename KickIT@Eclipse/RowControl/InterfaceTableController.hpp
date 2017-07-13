#ifndef INTERFACETABLECONTROLLER_HPP
#define INTERFACETABLECONTROLLER_HPP

#include "../DataType/BallStatus.hpp"
#include "../DataType/Vec2.hpp"
#include <iostream>

class InterfaceTableController{
public:
    virtual void setBallPos(float x, float y) = 0;
    virtual void run() = 0;
    virtual void stop() = 0;
};

#endif /* INTERFACETABLECONTROLLER_HPP */

