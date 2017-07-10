

#ifndef TABLECONTROLLERINTERFACE_HPP
#define TABLECONTROLLERINTERFACE_HPP

#include "../DataType/BallStatus.hpp"


class TableControllerInterface{
public:
    virtual void setBallStatus(BallStatus* b) = 0;
};


#endif /* TABLECONTROLLERINTERFACE_HPP */

