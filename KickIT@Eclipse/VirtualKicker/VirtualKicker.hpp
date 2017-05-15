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
#include "BallTrackerMock.hpp"

class VirtualKicker{

	private:
		static VirtualKickerWindow* vkw;
		static TableControllerMock* tc;
		static BallTrackerMock* bt;
    
    
    public:
        static const int WINDOW_SIZE_X = 1000;
        static const int WINDOW_SIZE_Y = 700;



        static void init(){
            
            
            bt = new BallTrackerMock();
            vkw = new VirtualKickerWindow(bt);
            tc = new TableControllerMock(vkw);
            bt->setTableController(tc);
            
            vkw->setFixedSize(WINDOW_SIZE_X,WINDOW_SIZE_Y);
            vkw->show();

            
            
            
        }

        static TableControllerMock* getMockTableController(){
            return tc;
            
        }

        static BallTrackerMock* getMockBallTracker(){
            return bt;
        }
    
};

VirtualKickerWindow* VirtualKicker::vkw;
TableControllerMock* VirtualKicker::tc;
BallTrackerMock* VirtualKicker::bt;

#endif /* VIRTUALKICKER_HPP */

