/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MotorCommunicatorInterface.hpp
 * Author: student
 *
 * Created on 13. April 2017, 15:30
 */

#ifndef MOTORCOMMUNICATORINTERFACE_HPP
#define MOTORCOMMUNICATORINTERFACE_HPP

class MotorCommunicatorInterface{
	public:
	virtual void moveTo(float y) = 0;
	virtual void kick() = 0;

};

#endif /* MOTORCOMMUNICATORINTERFACE_HPP */

