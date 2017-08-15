#ifndef ROWCONTROL_CALCULATION_CALCULATOR_HPP_
#define ROWCONTROL_CALCULATION_CALCULATOR_HPP_

#include "../../DataType/Vec2.hpp"
#include "../../DataType/TableConfig.hpp"

class Calculator {

public:
	TableConfig tc;
	Vec2* rowDirectionalVector;
	Vec2* keeperPosition;
	float* positions;
	bool* up;
	bool* kick;

	Calculator() {
		this->rowDirectionalVector = new Vec2(0, 1);
		this->keeperPosition = new Vec2(tc.distGoalToKeeper, 0);

		positions = new float[tc.isKeeperActive ? 1 : 0 + tc.isDefenseActive ? 1 :
								0 + tc.isMidfieldActive ? 1 :
								0 + tc.isOffenseActive ? 1 : 0]();
		up = new bool[tc.isDefenseActive ? 1 : 0 + tc.isMidfieldActive ? 1 :
						0 + tc.isOffenseActive ? 1 : 0]();
		kick = new bool[tc.isDefenseActive ? 1 : 0 + tc.isMidfieldActive ? 1 :
						0 + tc.isOffenseActive ? 1 : 0]();

	}

	~Calculator() {
		delete (up);
		delete (positions);
		delete (kick);
	}

	void calcPositionsSimple(BallStatus* bs, float yOffset = 0) {
		if (tc.isKeeperActive) {
			std::cout << "Directional-X: " << bs->movement.x << std::endl;
			std::cout << "Directional-Y: " << bs->movement.y << std::endl;

			if ( bs->movement.x < 0 ) {
				float m = bs->movement.y / bs->movement.x;
				float pos = bs->position.y + (bs->position.x - tc.distGoalToKeeper) * m;
				positions[0] = pos;
			} else {
				positions[0] = 340;
			}
		}
	}

	void calcIfKick(BallStatus* bs, float yOffset = 0) {
		std::cout << abs(positions[1] + tc.offsetTopSideDefense - bs->position.y)
				<< std::endl;
		std::cout << abs(bs->position.x - tc.distGoalToDefense) << std::endl;
		std::cout
				<< abs(
						positions[1] + tc.offsetTopSideDefense + tc.playerGapDefense
								- bs->position.y) << std::endl;
		std::cout << abs(bs->position.x - tc.distGoalToDefense) << std::endl;

		if ((abs(positions[1] + tc.offsetTopSideDefense - bs->position.y)
				< tc.shotTriggerRange
				&& abs(bs->position.x - tc.distGoalToDefense)
						< tc.shotTriggerRange)
				|| (abs(
						positions[1] + tc.offsetTopSideDefense + tc.playerGapDefense
								- bs->position.y) < tc.shotTriggerRange
						&& abs(bs->position.x - tc.distGoalToDefense)
								< tc.shotTriggerRange)) {

			kick[0] = true;
		}
	}

	void calcIfUp(BallStatus* bs, float yOffset = 0) {
		if (bs->position.x < 155)
			up[0] = true;

	}

	static float* calcPositionsVectorial(BallStatus* b, float yOffset = 0,
			Vec2* keeperPositionalVector = 0, Vec2* defensePositionalVector = 0,
			Vec2* midfieldPositionalVector = 0, Vec2* offensePositionalVector =
					0) {

	}
};

#endif //ROWCONTROL_CALCULATION_CALCULATOR_HPP_
