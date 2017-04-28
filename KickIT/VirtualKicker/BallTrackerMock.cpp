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

BallTrackerMock::BallTrackerMock() {
}

//BallTrackerMock::BallTrackerMock(VirtualKickerWindow* w) {
    //this->window = w;
//}


BallTrackerMock::~BallTrackerMock() {
}

BallStatus* BallTrackerMock::getBallStatus(){
    return NULL;
}

void BallTrackerMock::mouseMove(QMouseEvent* e){
    
}

