/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BallTrackerImpl.hpp
 * Author: student
 *
 * Created on 28. April 2017, 17:15
 */

#ifndef BALLTRACKERIMPL_HPP
#define BALLTRACKERIMPL_HPP

class BallTrackerImpl : public BallTrackerInterface{

	public:

	virtual BallStatus* getBallStatus(){

	}

	virtual void startTracking(){
		//CGrabResultPtr ptrGrabResult;
	}

	virtual void stopTracking(){

	}

	virtual ~BallTrackerImpl(){


	}

};

#endif /* BALLTRACKERIMPL_HPP */

