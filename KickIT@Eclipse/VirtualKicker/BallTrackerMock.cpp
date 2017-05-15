/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BallTrackerMock.cpp
 * Author: student
 * 
 * Created on 28. April 2017, 18:11
 */

#include "BallTrackerMock.hpp"
#include <iostream>

BallTrackerMock::BallTrackerMock():s() {
}



BallTrackerMock::~BallTrackerMock() {
}

BallStatus* BallTrackerMock::getBallStatus(){
    return NULL;
}

void BallTrackerMock::receiveMockBallPosition(BallPos* p){
    newBallPosition(p);
}

void BallTrackerMock::setTableController(TableControllerInterface* t){
    this->tableController = t;
}

void BallTrackerMock::newBallPosition(BallPos* p){
	s.position.update(p);
	tableController->setBallStatus(new BallStatus(p->x,p->y,0.0,0.0));
}
