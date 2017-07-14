#ifndef INTERFACETABLECONTROLLER_HPP
#define INTERFACETABLECONTROLLER_HPP

#include "../DataType/BallStatus.hpp"
#include "../DataType/Vec2.hpp"
#include <iostream>

class InterfaceTableController{
public:
    virtual void setBallPos(float x, float y) = 0;
    virtual void run() = 0;
    virtual void stop() = 0;

protected:
    float* calculateRowPositions(float tableHeight, BallStatus* b, bool keeper, bool defense, bool midfield, bool offense, float yOffset=0, float dDist=0,
    		float mDist = 0, float oDist = 0){

    	unsigned int arraySize = keeper ? 1 : 0 + defense ? 1 : 0 + midfield ? 1 : 0 + offense ? 1 : 0;
    	float* result = new float[arraySize];
    	if(keeper){
    		float pos = 0;
    		//TODO schnittpunkt zweier geraden
    		result[0] = b->position.y;
    	}
    	if(defense){
    		float pos = 0;
    		if(b->position.y < (tableHeight/2+yOffset))
    			pos = b->position.y;
    		else
    			pos = b->position.y - dDist;
    		result[1] = pos;
    	}


    	return result;
    }

    bool keeperActive, defenseActive, midfieldActive, offenseActive;
    BallStatus ballStatus;

    void updateBallStatus(float x, float y){

    	ballStatus.movement.x = ballStatus.position.x - x;
    	ballStatus.movement.y = ballStatus.position.y - y;
    	ballStatus.position.update(x,y);

    }
};

#endif /* INTERFACETABLECONTROLLER_HPP */

