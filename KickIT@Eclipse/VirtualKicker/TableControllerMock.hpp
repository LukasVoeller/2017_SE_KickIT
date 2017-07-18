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

