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

#include "../BallTracking/BallTrackerInterface.hpp"
#include <QMouseEvent>

class BallTrackerMock : public BallTrackerInterface{
public:
    BallTrackerMock();
    
    virtual ~BallTrackerMock();
    
    void startTracking(){}
    void stopTracking(){}
    BallStatus* getBallStatus();
    void mouseMove(QMouseEvent* e);
    
    void setTableController(TableControllerInterface* t);
private:
    TableControllerInterface* tableController;

};

#endif /* BALLTRACKERMOCK_HPP */

