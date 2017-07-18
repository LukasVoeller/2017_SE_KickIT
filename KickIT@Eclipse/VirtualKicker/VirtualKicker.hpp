#ifndef VIRTUALKICKER_HPP
#define VIRTUALKICKER_HPP

#include "VirtualKickerWindow.hpp"
#include "TableControllerMock.hpp"

class VirtualKicker{

	private:
		static VirtualKickerWindow* vkw;
		static TableControllerMock* tc;
    
    public:
        static const int WINDOW_SIZE_X = 1024;
        static const int WINDOW_SIZE_Y = 768;

        static void init(){
            vkw = new VirtualKickerWindow();
            tc = new TableControllerMock(true, true, false, false);
            
            tc->setKickerWindow(vkw);
            vkw->setTableController(tc);
            
            vkw->setFixedSize(WINDOW_SIZE_X,WINDOW_SIZE_Y);
            vkw->show();
        }

        static TableControllerMock* getMockTableController(){
            return tc;
        }
};

VirtualKickerWindow* VirtualKicker::vkw;
TableControllerMock* VirtualKicker::tc;

#endif /* VIRTUALKICKER_HPP */

