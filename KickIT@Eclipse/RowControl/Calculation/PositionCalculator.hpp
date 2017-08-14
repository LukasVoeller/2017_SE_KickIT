#ifndef ROWCONTROL_CALCULATION_POSITIONCALCULATOR_HPP_
#define ROWCONTROL_CALCULATION_POSITIONCALCULATOR_HPP_

#include "../../DataType/Vec2.hpp"

class PositionCalculator {
public:
	float tableHeight;

	bool isKeeperActive = false;
	bool isDefenseActive = false;
	bool isMidfieldActive = false;
	bool isOffenseActive = false;

	float playerGapDefense = 0;
	float playerGapMidfield = 0;
	float playerGapOffense = 0;

	Vec2 rowDirectionalVector;

	float* calcPositionsSimple(BallStatus* bs, float yOffset = 0) {

		//Calculate how many fields are needed
		float* result = new float[isKeeperActive ? 1 : 0 + isDefenseActive ? 1 :
									0 + isMidfieldActive ? 1 :
									0 + isOffenseActive ? 1 : 0];

		if (isKeeperActive) {
			result[0] = bs->position.y;
		}

		if (isDefenseActive) {
			/*if (bs->position.y <= tableHeight / 2) {
				result[1] = bs->position.y - playerGapDefense / 2;

			} else if (bs->position.y > tableHeight / 2) {
				result[1] = bs->position.y + playerGapDefense / 2;
			}*/
			result[1] = bs->position.y;
		}
		return result;
	}

	static float* calcPositionsVectorial(BallStatus* b, float yOffset = 0,
			Vec2* keeperPositionalVector = 0, Vec2* defensePositionalVector = 0,
			Vec2* midfieldPositionalVector = 0, Vec2* offensePositionalVector =
					0) {

	}
};

//PositionCalculator::rowDirectionalVector(0, -1);

#endif //ROWCONTROL_CALCULATION_POSITIONCALCULATOR_HPP_
