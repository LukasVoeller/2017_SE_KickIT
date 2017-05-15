/*
 * Vec2.hpp
 *
 *  Created on: 23.03.2017
 *      Author: student
 */

#ifndef VEC2_HPP_
#define VEC2_HPP_

#include <iostream>

class BallPos{
public:
    float x;
    float y;
    BallPos(float _x, float _y):x(_x),y(_y){

    }
    void update(float newx, float newy){
    	x = newx;
    	y = newy;
    }

    void update(BallPos* newp){
    	x = newp->x;
    	y = newp->y;
    	//delete newp;
    }
};


#endif /* VEC2_HPP_ */
