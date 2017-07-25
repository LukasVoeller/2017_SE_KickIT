#ifndef INTERFACETABLECONTROLLER_HPP
#define INTERFACETABLECONTROLLER_HPP

#include "../DataType/BallStatus.hpp"
#include "../DataType/Vec2.hpp"
#include <iostream>

class InterfaceTableController {
public:
	//virtual ~InterfaceTableController(); //Warning without destructor
	virtual void setBallPos(float x, float y) = 0;
	virtual void run() = 0;
	virtual void stop() = 0;

protected:
    float* calculateRowPositions(float tableHeight, BallStatus* b,
    		bool keeper, bool defense, bool midfield, bool offense, float yOffset=0, float dDist=0, float mDist = 0, float oDist = 0,
			Vec2* keeperPositionalVector = 0,
			Vec2* defensePositionalVector = 0,
			Vec2* midfieldPositionalVector = 0,
			Vec2* offensePositionalVector = 0){

    	Vec2* rowDirectionalVector = new Vec2(0,1);
    	rowDirectionalVector->normalize();
    	b->movement.normalize();

		unsigned int arraySize = keeper ? 1 : 0 + defense ? 1 :
									0 + midfield ? 1 : 0 + offense ? 1 : 0;
		float* result = new float[arraySize];
		if (keeper) {

    		if(b->movement.cross(*rowDirectionalVector)!=0){
    			float factor = ( (*keeperPositionalVector - b->movement).cross(*rowDirectionalVector) ) / b->movement.cross(*rowDirectionalVector);

				result[0] = (b->position + b->movement * (-factor)).y;

			} else {
				result[0] = b->position.x;
			}
		}
		if (defense) {

			//TODO aehnliche berechnung des schnittpunktes wie beim keeper

			float pos = 0;
			if (b->position.y < (tableHeight / 2 + yOffset))
				pos = b->position.y;
			else
				pos = b->position.y - dDist;
			result[1] = pos;
		}

    	//TODO speicherlecks
    	delete rowDirectionalVector;
    	delete keeperPositionalVector;


		return result;
	}

	bool keeperActive, defenseActive, midfieldActive, offenseActive;
	BallStatus ballStatus;

	void updateBallStatus(float x, float y) {
		ballStatus.movement.x = ballStatus.position.x - x;
		ballStatus.movement.y = ballStatus.position.y - y;
		ballStatus.position.update(x, y);
	}
};

#endif /* INTERFACETABLECONTROLLER_HPP */

