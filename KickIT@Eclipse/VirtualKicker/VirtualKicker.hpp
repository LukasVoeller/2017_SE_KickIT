/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VirtualKicker.hpp
 * Author: student
 *
 * Created on 28. April 2017, 18:21
 */

#ifndef VIRTUALKICKER_HPP
#define VIRTUALKICKER_HPP

#include "VirtualKickerWindow.hpp"
#include "TableControllerMock.hpp"

class VirtualKicker{

	private:
		static VirtualKickerWindow* vkw;
		static TableControllerMock* tc;
    
    
    public:
        static const int WINDOW_SIZE_X = 1000;
        static const int WINDOW_SIZE_Y = 700;



        static void init(){
            
            
            vkw = new VirtualKickerWindow();
            tc = new TableControllerMock();
            
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

//BallTrackerMock* VirtualKicker::bt;

#endif /* VIRTUALKICKER_HPP */

