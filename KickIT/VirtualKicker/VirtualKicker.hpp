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
#include "../BallTracking/BallTrackerInterface.hpp"
#include "../RowControl/TableControllerInterface.hpp"
#include "BallTrackerMock.hpp"

class VirtualKicker{

    
    
    
    public:
        static const int WINDOW_SIZE_X = 1000;
        static const int WINDOW_SIZE_Y = 700;

        static VirtualKickerWindow* vkw;
        static TableControllerInterface* tc;
        static BallTrackerInterface* bt;

        static void init(){
            vkw = new VirtualKickerWindow();
            
            
            vkw->setFixedSize(WINDOW_SIZE_X,WINDOW_SIZE_Y);
            vkw->show();

            //tc = new TableControllerMock(vkw);
            //bt = new BallTrackerMock(vkw);
            
        }

        static TableControllerInterface* getMockTableController(){
            //return tc;
            return NULL;
        }

        static BallTrackerInterface* getMockBallTracker(){
            //return bt;
            return NULL;
        }
    
};

VirtualKickerWindow* VirtualKicker::vkw;
TableControllerInterface* VirtualKicker::tc;
BallTrackerInterface* VirtualKicker::bt;

#endif /* VIRTUALKICKER_HPP */

