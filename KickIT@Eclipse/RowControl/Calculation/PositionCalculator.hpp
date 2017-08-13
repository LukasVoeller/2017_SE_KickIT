#ifndef ROWCONTROL_CALCULATION_POSITIONCALCULATOR_HPP_
#define ROWCONTROL_CALCULATION_POSITIONCALCULATOR_HPP_

#include "../../DataType/Vec2.hpp"

class PositionCalculator {
public:
	static float tableHeight;

	static bool isKeeperActive;
	static bool isDefenseActive;
	static bool isMidfieldActive;
	static bool isOffenseActive;

	static float playerGapDefense;
	static float playerGapMidfield;
	static float playerGapOffense;

	static Vec2 rowDirectionalVector;

	static float* calcPositionsSimple(BallStatus* bs, float yOffset = 0) {
		rowDirectionalVector.normalize();
		bs->movement.normalize();

		//Calculate how many fields are needed
		float* result = new float[isKeeperActive ? 1 : 0 + isDefenseActive ? 1 :
									0 + isMidfieldActive ? 1 :
									0 + isOffenseActive ? 1 : 0];

		if (isKeeperActive) {
			result[0] = bs->position->y;
		}

		if (isDefenseActive) {
			if (bs->position->y <= tableHeight / 2) {
				result[1] = bs->position->y - playerGapDefense / 2;
			} else if (bs->position->y > tableHeight / 2) {
				result[1] = bs->position->y + playerGapDefense / 2;
			}
		}

		return result;
	}

	static float* calcPositionsVectorial(BallStatus* b, float yOffset = 0,
			Vec2* keeperPositionalVector = 0, Vec2* defensePositionalVector = 0,
			Vec2* midfieldPositionalVector = 0, Vec2* offensePositionalVector = 0) {

	}
};

PositionCalculator::rowDirectionalVector(0, -1);

#endif //ROWCONTROL_CALCULATION_POSITIONCALCULATOR_HPP_
