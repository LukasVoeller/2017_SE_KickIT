/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BallTrackerMock.hpp
 * Author: student
 *
 * Created on 28. April 2017, 18:11
 */

#ifndef BALLTRACKERMOCK_HPP
#define BALLTRACKERMOCK_HPP

#include "VirtualKickerWindow.hpp"
#include "../BallTracking/BallTrackerInterface.hpp"

class BallTrackerMock : public BallTrackerInterface{
public:
    BallTrackerMock();
    //BallTrackerMock(VirtualKickerWindow* w);
    
    virtual ~BallTrackerMock();
    
    void startTracking(){}
    void stopTracking(){}
    BallStatus* getBallStatus();
    void mouseMove(QMouseEvent* e);
private:
    //VirtualKickerWindow* window;

};

#endif /* BALLTRACKERMOCK_HPP */

