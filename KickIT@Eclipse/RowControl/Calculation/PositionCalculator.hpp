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

	float offsetTopSideDefense = 0;
	float offsetBottomSideDefense = 0;

	float offsetTopSideKeeper = 0;

	Vec2 rowDirectionalVector;

	float* calcPositionsSimple(BallStatus* bs, float yOffset = 0) {

		//Calculate how many fields are needed
		float* result = new float[isKeeperActive ? 1 : 0 + isDefenseActive ? 1 :0 + isMidfieldActive ? 1 :0 + isOffenseActive ? 1 : 0];

		if (isKeeperActive) {
			result[0] = bs->position.y - offsetTopSideKeeper;
		}

		if (isDefenseActive) {
			if (bs->position.y <= tableHeight / 2) {
				//std::cout << "kleiner: " << std::endl;
				//std::cout << "original: " << bs->position.y << std::endl;
				result[1] = bs->position.y - offsetTopSideDefense;
				//std::cout << "dann: " << result[1] << std::endl;
			} else if (bs->position.y > tableHeight / 2) {
				//std::cout << "groesser: " << std::endl;
				//std::cout << "original: " << bs->position.y << std::endl;
				result[1] = bs->position.y - offsetBottomSideDefense;
				//std::cout << "dann: " << result[1] << std::endl;
			}
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
