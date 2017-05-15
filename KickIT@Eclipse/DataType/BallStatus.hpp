/*
 * BallStatus.hpp
 *
 *  Created on: 23.03.2017
 *      Author: student
 */

#ifndef BALLSTATUS_HPP_
#define BALLSTATUS_HPP_
#include "BallPos.hpp"

class BallStatus{
public:
    
    BallPos movement;
    BallPos position;
    
    BallStatus(float posx, float posy, float movementx, float movementy):movement(movementx, movementy),position(posx, posy){
    }
    
    BallStatus():movement(0.0f,0.0f),position(0.0f,0.0f){

    }

    float getVelocity(){
    	return 0.0f; //TODO
    }
};


#endif /* BALLSTATUS_HPP_ */
