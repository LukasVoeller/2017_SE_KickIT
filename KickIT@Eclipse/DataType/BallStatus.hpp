/*
 * BallStatus.hpp
 *
 *  Created on: 23.03.2017
 *      Author: student
 */

#ifndef BALLSTATUS_HPP_
#define BALLSTATUS_HPP_
#include "../DataType/Vec2.hpp"

class BallStatus{
public:
    
    Vec2 movement;
    Vec2 position;
    
    BallStatus(float posx, float posy, float movementx, float movementy):movement(movementx, movementy),position(posx, posy){
    }
    
    float getVelocity(){
            return 0.0f; //TODO
    }
};


#endif /* BALLSTATUS_HPP_ */
